#include "commands.h"
#include <sstream>

namespace vfs {

Commands::Commands() : vfs() {}

void Commands::command() {
  std::string input{};
  std::cout << "To exit enter q" << std::endl;
  std::cout << "Available commands: ";
  for (const auto &command : shellCommands)
    std::cout << command << " ";
  std::cout << std::endl;
  std::cout << "Enter command" << std::endl;
  do {
    std::cout << "> ";
    getline(std::cin, input);
    parseInput(input);
  } while (input != "q" && input != "Q");
}

void Commands::parseInput(const std::string &inputCommand) {
  if (inputCommand.find(shellCommands.at(0)) != std::string::npos) { // mkdir
    std::string nameDirectory = splitString(inputCommand, ' ');
    if (nameDirectory.empty()) {
      std::cout << "Invalid command" << std::endl;
    }
    makeDirectory(nameDirectory);
  } else if (inputCommand.find(shellCommands.at(1)) !=
             std::string::npos) { // cd
    std::string nameDirectory = splitString(inputCommand, ' ');
    changeDirectory(nameDirectory);
  } else if (inputCommand.find(shellCommands.at(2)) !=
             std::string::npos) { // ls
    if (inputCommand.length() < 3) {
      list();
    } else {
      std::cout << "Invalid command" << std::endl;
    }
  } else if (inputCommand.find(shellCommands.at(3)) !=
             std::string::npos) { // rm
    std::string nameDirectory = splitString(inputCommand, ' ');
    if (nameDirectory.empty()) {
      std::cout << "Invalid command" << std::endl;
    }
    remove(nameDirectory);
  } else if (inputCommand.find(shellCommands.at(4)) !=
             std::string::npos) { // mkfile
    std::string nameFile = splitString(inputCommand, ' ');
    if (nameFile.empty()) {
      std::cout << "Invalid command" << std::endl;
    }
    makeFile(nameFile);
  }
}

void Commands::makeDirectory(const std::string &nameDirectory) {
  vfs.makeDirectory(nameDirectory);
}

void Commands::changeDirectory(const std::string &nameDirectory) {
  vfs.changeDirectory(nameDirectory);
}

void Commands::list() { vfs.list(); }

void Commands::remove(const std::string &name) { vfs.remove(name); }

void Commands::makeFile(const std::string &nameFile) { vfs.makeFile(nameFile); }

std::string Commands::splitString(const std::string &stringToSplit,
                                  char delimiter) {
  std::string item;
  std::stringstream ss(stringToSplit);
  std::vector<std::string> splitItems;

  while (getline(ss, item, delimiter)) {
    splitItems.push_back(item);
  }
  if (splitItems.size() == 1)
    return std::string();  // no directory name after command
  return splitItems.at(1); // return file or directory name
}
} // namespace vfs
