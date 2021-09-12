#include "commands.h"
#include "commandsIf.h"
#include "vfs.h"
#include <catch.hpp>

// User input commands
TEST_CASE("UserInputCommands") {
  vfs::CommandsIf *commands = new vfs::Commands();
  commands->command();
  delete commands;
}

// Parse input commands in Commands
TEST_CASE("ParseInputCommand") {
  vfs::Commands commands;
  commands.parseInput("mkdir one two three");
  REQUIRE(commands.vfs.currentDirectory->directoryName == "home");
  // one subdirectory added to home
  REQUIRE(commands.vfs.currentDirectory->subDirectories.size() == 1);
  // check names of added subdirectories
  REQUIRE(commands.vfs.currentDirectory->subDirectories.at(0)->directoryName ==
          "one");
  // cd to one
  commands.parseInput("cd one");
  REQUIRE(commands.vfs.currentDirectory->directoryName == "one");
  // cd to two, that is not created
  commands.parseInput("cd two");
  REQUIRE(commands.vfs.currentDirectory->directoryName == "one");

  // make file
  commands.parseInput("mkfile file file1");
  REQUIRE(commands.vfs.currentDirectory->files.size() == 1);
  REQUIRE(commands.vfs.currentDirectory->files.at(0)->fileName == "file");

  // rm file
  commands.parseInput("rm file");
  REQUIRE(commands.vfs.currentDirectory->files.size() == 0);

  // cd ..
  commands.parseInput("cd ..");
  REQUIRE(commands.vfs.currentDirectory->directoryName == "home");

  // cd
  commands.parseInput("cd");
  REQUIRE(commands.vfs.currentDirectory->directoryName == "home");
}

// Test methods in VirtualFileSystem
TEST_CASE("TestCdFromHome") {
  vfs::VirtualFileSystem virtualFileSystem;

  std::string emptyString;
  std::string toHome = "..";

  // check that cd works from top, home directory
  virtualFileSystem.changeDirectory(emptyString);
  REQUIRE(virtualFileSystem.currentDirectory->directoryName == "home");

  // check that cd .. works from top, home directory
  virtualFileSystem.changeDirectory(toHome);
  REQUIRE(virtualFileSystem.currentDirectory->directoryName == "home");
}

TEST_CASE("TestMkdir") {
  vfs::VirtualFileSystem virtualFileSystem;

  std::string one = "one";
  std::string two = "two";

  // check that mkdir works
  virtualFileSystem.makeDirectory(one);
  virtualFileSystem.makeDirectory(two);
  // still in home directory
  REQUIRE(virtualFileSystem.currentDirectory->directoryName == "home");
  // two subdirectories added to home
  REQUIRE(virtualFileSystem.currentDirectory->subDirectories.size() == 2);
  // check names of added subdirectories
  REQUIRE(
      virtualFileSystem.currentDirectory->subDirectories.at(0)->directoryName ==
      "one");
  REQUIRE(
      virtualFileSystem.currentDirectory->subDirectories.at(1)->directoryName ==
      "two");
}

TEST_CASE("TestMkdirMkfile") {
  vfs::VirtualFileSystem virtualFileSystem;

  std::string one = "one";
  std::string two = "two";
  std::string file1 = "file1";
  std::string file2 = "file2";

  // check that mkdir+mkfile works
  virtualFileSystem.makeDirectory(one);
  virtualFileSystem.makeDirectory(two);
  virtualFileSystem.makeFile(file1);
  virtualFileSystem.makeFile(file2);
  // still in home directory
  REQUIRE(virtualFileSystem.currentDirectory->directoryName == "home");
  // two subdirectories added to home
  REQUIRE(virtualFileSystem.currentDirectory->subDirectories.size() == 2);
  // check names of added subdirectories
  REQUIRE(
      virtualFileSystem.currentDirectory->subDirectories.at(0)->directoryName ==
      "one");
  REQUIRE(
      virtualFileSystem.currentDirectory->subDirectories.at(1)->directoryName ==
      "two");
  // check files
  REQUIRE(virtualFileSystem.currentDirectory->files.size() == 2);
  // check names of added files
  REQUIRE(virtualFileSystem.currentDirectory->files.at(0)->fileName == "file1");
  REQUIRE(virtualFileSystem.currentDirectory->files.at(1)->fileName == "file2");
}

TEST_CASE("TestRemove") {
  vfs::VirtualFileSystem virtualFileSystem;

  std::string one = "one";
  std::string two = "two";
  std::string file1 = "file1";
  std::string file2 = "file2";

  // check that mkdir+mkfile works
  virtualFileSystem.makeDirectory(one);
  virtualFileSystem.makeDirectory(two);
  virtualFileSystem.makeFile(file1);
  virtualFileSystem.makeFile(file2);
  // still in home directory
  REQUIRE(virtualFileSystem.currentDirectory->directoryName == "home");
  // two subdirectories added to home
  REQUIRE(virtualFileSystem.currentDirectory->subDirectories.size() == 2);
  // check names of added subdirectories
  REQUIRE(
      virtualFileSystem.currentDirectory->subDirectories.at(0)->directoryName ==
      "one");
  REQUIRE(
      virtualFileSystem.currentDirectory->subDirectories.at(1)->directoryName ==
      "two");
  // check files
  REQUIRE(virtualFileSystem.currentDirectory->files.size() == 2);
  // check names of added files
  REQUIRE(virtualFileSystem.currentDirectory->files.at(0)->fileName == "file1");
  REQUIRE(virtualFileSystem.currentDirectory->files.at(1)->fileName == "file2");

  // remove directory one
  virtualFileSystem.remove(one);
  // two subdirectories added to home
  REQUIRE(virtualFileSystem.currentDirectory->subDirectories.size() == 1);
  // check names of added subdirectories
  REQUIRE(
      virtualFileSystem.currentDirectory->subDirectories.at(0)->directoryName ==
      "two");

  // remove directory one
  virtualFileSystem.remove(file1);
  // check files
  REQUIRE(virtualFileSystem.currentDirectory->files.size() == 1);
  // check names of added files
  REQUIRE(virtualFileSystem.currentDirectory->files.at(0)->fileName == "file2");
}

TEST_CASE("TestAll") {
  vfs::VirtualFileSystem virtualFileSystem;

  std::string one = "one";
  std::string two = "two";
  std::string three = "three";
  std::string four = "four";
  std::string five = "five";
  std::string file1 = "file1";

  // check that mkdir+mkfile works
  virtualFileSystem.makeDirectory(one);
  virtualFileSystem.makeDirectory(two);
  virtualFileSystem.makeFile(file1);

  // change directory to one
  virtualFileSystem.changeDirectory(one);
  virtualFileSystem.makeDirectory(three);
  virtualFileSystem.makeFile(file1);

  REQUIRE(virtualFileSystem.currentDirectory->directoryName == "one");
  // one subdirectory added to one
  REQUIRE(virtualFileSystem.currentDirectory->subDirectories.size() == 1);
  // check names of added subdirectories
  REQUIRE(
      virtualFileSystem.currentDirectory->subDirectories.at(0)->directoryName ==
      "three");
  // check files
  REQUIRE(virtualFileSystem.currentDirectory->files.size() == 1);
  // check names of added files
  REQUIRE(virtualFileSystem.currentDirectory->files.at(0)->fileName == "file1");

  // change directory to home
  std::string toHome = "..";
  virtualFileSystem.changeDirectory(toHome);
  REQUIRE(virtualFileSystem.currentDirectory->directoryName == "home");
  // two subdirectoties added to home
  REQUIRE(virtualFileSystem.currentDirectory->subDirectories.size() == 2);
  // check names of added subdirectories
  REQUIRE(
      virtualFileSystem.currentDirectory->subDirectories.at(0)->directoryName ==
      "one");
  REQUIRE(
      virtualFileSystem.currentDirectory->subDirectories.at(1)->directoryName ==
      "two");
  // check files
  REQUIRE(virtualFileSystem.currentDirectory->files.size() == 1);
  // check names of added files
  REQUIRE(virtualFileSystem.currentDirectory->files.at(0)->fileName == "file1");

  // change directory to two
  virtualFileSystem.changeDirectory(two);
  virtualFileSystem.makeDirectory(four);

  REQUIRE(virtualFileSystem.currentDirectory->directoryName == "two");
  // one subdirectory added to two
  REQUIRE(virtualFileSystem.currentDirectory->subDirectories.size() == 1);
  // check names of added subdirectories
  REQUIRE(
      virtualFileSystem.currentDirectory->subDirectories.at(0)->directoryName ==
      "four");

  // change directory to four
  virtualFileSystem.changeDirectory(four);

  // change directory to five that is not created
  virtualFileSystem.changeDirectory(five);

  REQUIRE(virtualFileSystem.currentDirectory->directoryName == "four");
  // no subdirectories added to four
  REQUIRE(virtualFileSystem.currentDirectory->subDirectories.size() == 0);

  // change directory to one above
  std::string toAbove = "..";
  virtualFileSystem.changeDirectory(toAbove);
  REQUIRE(virtualFileSystem.currentDirectory->directoryName == "two");
  // one subdirectory added
  REQUIRE(virtualFileSystem.currentDirectory->subDirectories.size() == 1);
  // check names of added subdirectories
  REQUIRE(
      virtualFileSystem.currentDirectory->subDirectories.at(0)->directoryName ==
      "four");

  // change directory to one above, home
  virtualFileSystem.changeDirectory(toAbove);
  REQUIRE(virtualFileSystem.currentDirectory->directoryName == "home");
}
