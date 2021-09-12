#include "vfs.h"

namespace vfs {

VirtualFileSystem::VirtualFileSystem() {
  // creating home directory in ctor
  head = new Directory("home");
  currentDirectory = head;
  head->parentDirectory = nullptr;
}

VirtualFileSystem::~VirtualFileSystem() {
  currentDirectory = head;
  deleteDirectory(currentDirectory);
  currentDirectory = nullptr;
  delete currentDirectory;
}

void VirtualFileSystem::deleteDirectory(Directory *directory) {
  if (directory == nullptr)
    return;

  for (auto &dir : directory->subDirectories) {

    if (dir->files.size() > 0) {
      for (auto &file : dir->files) {
        delete file;
        file = nullptr;
      }
      dir->files.erase(
          std::remove(dir->files.begin(), dir->files.end(), nullptr),
          dir->files.end());
    }
    deleteDirectory(dir);
  }
  delete directory;
}

void VirtualFileSystem::makeDirectory(const std::string &nameDirectory) {
  Directory *temp = new Directory(nameDirectory);
  temp->parentDirectory = currentDirectory;
  currentDirectory->subDirectories.push_back(temp);
}

void VirtualFileSystem::changeDirectory(const std::string &nameDirectory) {
  if ((nameDirectory.empty() && currentDirectory == head) ||
      (nameDirectory == ".." && currentDirectory == head) ||
      (nameDirectory.empty() &&
       currentDirectory != head)) { // cd  - goes to home directory
    currentDirectory = head;
  } else if (nameDirectory == ".." &&
             currentDirectory->parentDirectory !=
                 nullptr) { // cd ..  - goes to parent directory
    currentDirectory = currentDirectory->parentDirectory;
  } else if (!nameDirectory.empty()) { // cd someDirectory - goes to
                                       // subDirectory, if exists
    if (currentDirectory->subDirectories.size() != 0) {
      bool match = false;
      auto matchDirectory = currentDirectory;
      for (const auto &dir : currentDirectory->subDirectories) {
        if (dir->directoryName == nameDirectory) {
          match = true;
          matchDirectory = dir;
        }
      }
      if (match) {
        currentDirectory = matchDirectory;
      } else {
        std::cout << "No such directory"
                  << std::endl; // if subDirectory doesn't exist
      }
    } else {
      std::cout << "No such directory"
                << std::endl; // if subDirectory doesn't exist
    }

  } else {
    std::cout << "Invalid command" << std::endl;
  }
}

void VirtualFileSystem::list() const {
  if (currentDirectory->subDirectories.size() == 0 &&
      currentDirectory->files.size() == 0)
    std::cout << "Empty directory " << std::endl;
  if (currentDirectory->subDirectories.size() > 0 &&
      currentDirectory->subDirectories.at(0) != nullptr) {
    for (const auto &dir : currentDirectory->subDirectories) {
      std::cout << "d------ " << dir->timeCreated << " " << dir->directoryName
                << std::endl; // list directories
    }
  }
  if (currentDirectory->files.size() > 0 &&
      currentDirectory->files.at(0) != nullptr) { // list files
    for (const auto &file : currentDirectory->files) {
      std::cout << "f------ " << file->timeCreated << " " << file->fileName
                << std::endl;
    }
  }
}

void VirtualFileSystem::remove(const std::string &name) {
  if (currentDirectory->subDirectories.size() > 0) { // remove directory
    for (auto &dir : currentDirectory->subDirectories) {
      if (dir->directoryName == name) {
        // remove all files in directory, before erasing directory
        for (auto &file : dir->files) {
          delete file;
          file = nullptr;
        }
        dir->files.erase(
            std::remove(dir->files.begin(), dir->files.end(), nullptr),
            dir->files.end());

        delete dir;
        dir = nullptr;
      }
    }
    currentDirectory->subDirectories.erase(
        std::remove(currentDirectory->subDirectories.begin(),
                    currentDirectory->subDirectories.end(), nullptr),
        currentDirectory->subDirectories.end());
  }

  if (currentDirectory->files.size() > 0) { // remove files
    for (auto &file : currentDirectory->files) {
      if (file->fileName == name) {
        delete file;
        file = nullptr;
      }
    }
    currentDirectory->files.erase(std::remove(currentDirectory->files.begin(),
                                              currentDirectory->files.end(),
                                              nullptr),
                                  currentDirectory->files.end());
  }
}

void VirtualFileSystem::makeFile(const std::string &nameFile) {
  currentDirectory->files.push_back(new File(nameFile));
}

std::string return_current_time_and_date() {
  time_t now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

  std::string s(30, '\0');
  std::strftime(
      &s[0], s.size(), "%Y-%m-%d %H:%M:%S",
      localtime(&now)); // prints time and date when file/directory was created
  return s;
}
} // namespace vfs
