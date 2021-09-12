#include "commands.h"
#include "commandsIf.h"

int main() {
  vfs::CommandsIf *commands = new vfs::Commands();
  commands->command();
  delete commands;
  return 0;
}
