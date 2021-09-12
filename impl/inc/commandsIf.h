#pragma once

#include "vfs.h"

namespace vfs {

/**
 * Commands interface class.
 *
 */
class CommandsIf {
public:
  /**
   * Pure virtual command function
   */
  virtual void command() = 0;

  /**
   * Constructor of CommandsIf
   *
   * Default constructor
   */
  CommandsIf() = default;

  /**
   * Destructor of CommandsIf
   *
   * Default destructor, virtual due to inheritance.
   */
  virtual ~CommandsIf() = default;
};
} // namespace vfs
