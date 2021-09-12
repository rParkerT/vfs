#pragma once

#include "commandsIf.h"

namespace vfs {

/**
 * Implementation of the Commands class.
 *
 * Class Commands publicly inherits CommandsIf.
 *
 */
class Commands : public CommandsIf {
public:
  VirtualFileSystem vfs;

  /**
   * Constructor of Commands
   *
   * Instantiation of VirtualFileSystem class too
   */
  Commands();

  /**
   * Destructor of Commands
   *
   * Default implementation
   */
  ~Commands() = default;

  /**
   * Implementation of command function, inherited from CommandsIf. It
   * asks for user input of commands, until user inserts q, that quits
   * program. Available commands are mkdir, cd, ls, rm, mkfile.
   *
   */
  void command() override;

  /**
   * Implementation of mkdir command function, that calls for makeDirectory in
   * VirtualFileSystem class.
   *
   * @param nameDirectory name of directory
   */
  void makeDirectory(const std::string &nameDirectory);

  // calls changeDirectory in VirtualFileSystem

  /**
   * Implementation of cd command function, that calls for changeDirectory in
   * VirtualFileSystem class.
   *
   * @param nameDirectory name of directory
   */
  void changeDirectory(const std::string &nameDirectory);

  /**
   * Implementation of ls command function, that calls for list in
   * VirtualFileSystem class.
   *
   */
  void list();

  /**
   * Implementation of rm command function, that calls for remove in
   * VirtualFileSystem class.
   *
   * @param name name of directory/file
   */
  void remove(const std::string &name);

  /**
   * Implementation of mkfile command function, that calls for makeFile in
   * VirtualFileSystem class.
   *
   * @param nameFile name of file
   */
  void makeFile(const std::string &nameFile);

  /**
   * Implementation of function that parse input string, calls for
   * splitString(const std::string &stringToSplit, char delimiter)
   *
   * @param inputCommand user command
   */
  void parseInput(const std::string &inputCommand);

private:
  /// Implemented shell commands
  std::vector<std::string> shellCommands{"mkdir", "cd", "ls", "rm", "mkfile"};

  /**
   * Implementation of split command input string, ex. "mkdir some", with
   * delimiter " " you split string and fetch "some" easily
   *
   * @param stringToSplit input string that is split
   * @param delimiter char that is used as point where to split string, for now
   * is one space char
   */
  std::string splitString(const std::string &stringToSplit, char delimiter);
};
} // namespace vfs
