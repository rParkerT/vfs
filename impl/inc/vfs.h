#pragma once

#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

namespace vfs {

/**
 * Returns time and date when file or directory was created
 *
 * @return time and date
 */
std::string return_current_time_and_date();

/**
 * Implementation of the VirtualFileSystem class.
 *
 * Class VirtualFileSystem is a collection of directories and files. It is used
 * with basic implemented commands, class Commands. Once the program is
 * terminated, there is no saved file or directory, hence virtual in class name.
 *
 */
class VirtualFileSystem {

private:
  /**
   * Implementation of the File class.
   *
   * @param fileName name of the file
   * @param timeCreated current time and date when the file was created
   */
  struct File {
    std::string fileName;
    std::string timeCreated = return_current_time_and_date();

    /**
     * Constructor of File
     *
     * @param name name of the file
     */
    File(std::string name) : fileName(std::move(name)) {}
  };

  /**
   * Implementation of the Directory class.
   *
   * Directoy can contain sub directories and files.
   *
   * @param directoryName name of the directory
   * @param timeCreated current time and date when the directory was created
   * @param subDirectories directory can contain subdirectories
   * @param parentDirectory pointer to directory above current directory, in vfs
   * structure
   * @param files vector of files that are part of current directory
   */
  struct Directory {
    std::string directoryName;
    std::string timeCreated = return_current_time_and_date();
    std::vector<Directory *> subDirectories{};
    Directory *parentDirectory = nullptr;
    std::vector<File *> files{};

    /**
     * Constructor of Directory
     *
     * Name of the directory is set, while pointers to vector of subDirectories
     * and files is set to nullptr, as well as parentDirectory
     *
     * @param name name of the directory
     */
    Directory(std::string name)
        : directoryName(std::move(name)), subDirectories(0, nullptr),
          parentDirectory(nullptr), files(0, nullptr) {}
  };

  /**
   * Delete all directories
   *
   * Function that recursivly calls itself and deletes all directories in vfs
   * structure.
   *
   * @param directory ptr to directory
   */
  void deleteDirectory(Directory *directory);

public:
  /**
   * Constructor of VirtualFileSystem
   *
   * Directory home is created, that represents top of the directory in vfs
   */
  VirtualFileSystem();

  /**
   * Destructor of VirtualFileSystem
   *
   * All files and subdirectories are removed from vfs, calling deleteDirectory
   * function
   */
  ~VirtualFileSystem();

  /// Disabling construction of VirtualFileSystem object using copy constructor
  VirtualFileSystem(const VirtualFileSystem &rhs) = delete;

  /// Disabling construction of VirtualFileSystem object using copy assignment
  VirtualFileSystem &operator=(const VirtualFileSystem &rhs) = delete;

  /**
   * Ptr to directory that tracks directory above current directory.
   */
  Directory *head = nullptr;

  /**
   * Ptr to directory that tracks current directory.
   */
  Directory *currentDirectory = nullptr;

  /**
   * Creates directory
   *
   * Creates directory with nameDirectory name and sets it parentDirectory to
   * currentDirectory, while currentDirectory is pointing to subDirectoris that
   * has newly created directory
   *
   * @param nameDirectory name of the directory
   */
  void makeDirectory(const std::string &nameDirectory);

  /**
   * Change directory
   *
   * Change directory, which moves pointer to currentDirectory. If no
   * nameDirectory is given, currentDirectory points to head directory, which is
   * Home directory. If nameDirectory is .. , currentDirectory points to
   * parentDirectory. If other name is given, directory is checked for
   * subdirectoris and if nameDirectory matches the name of one of the
   * subDirectoris, currentDirectory is set to that subdirectory, if no such
   * subdirectory exist, "No such directory" is printed. One other option is if
   * nameDirectory is .., when currentDirectory is head, that is Home directory,
   * that has no parentDirectory, then "No parent directory" is printed. If
   * nameDirectory is not defined in above discription, "Invalid command" is
   * printed.
   *
   * @param nameDirectory name of the directory
   */
  void changeDirectory(const std::string &nameDirectory);

  /**
   * List in directory
   *
   * List all subdirectoris and files in currentDirectory. Subdirectoris have
   * d------ extension, while files f------, after which timeCreated and
   * names of direcories and files are written.
   *
   */
  void list() const;

  /**
   * Remove in directory
   *
   * Checks if the name is the same as some subdirectory or file, if yes,
   * then this subdirectory or file is erased.
   *
   * @param name name of the directory/file that is to be erased
   */
  void remove(const std::string &name);

  /**
   * Creates file
   *
   * Creates file with nameFile name and sets it currentDirectory.
   *
   * @param nameFile name of the file
   */
  void makeFile(const std::string &nameFile);
};
} // namespace vfs
