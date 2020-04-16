#ifndef COMPARE_LEVELS_HPP
#define COMPARE_LEVELS_HPP

#include "common.hpp"

namespace logger {
/**
 * @brief  Interface for comparing log levels.
 */
class ICompareLevels
{
public:
  /**
   * @brief Sets the preferred_severity_level.
   * @param preferred_severity_level  A log level for decision making/further actions.
   * @retval None
   */
  void i_set_preferred_severity_level(logger::LEVEL preferred_severity_level);

  /**
   * @brief Returns the preferred severity level.
   * @param None
   * @retval logger::LEVEL
   */
  logger::LEVEL i_get_preferred_severity_level();

  /**
   * @brief Invokes the compare_levels method with given arguments.
   * @param level_1 Test parameter1
   * @param level_2 Test parameter2
   * @retval bool
   */
  bool i_compare_levels(logger::LEVEL level_1, logger::LEVEL level_2);

private:
  /**
   * @brief Compares two log levels.
   * @param level_1 Test parameter1
   * @param level_2 Test parameter2
   * @retval bool
   */
  virtual bool compare_levels(logger::LEVEL level_1, logger::LEVEL level_2) = 0;

  /**
   * @brief Variable to store desired severity level.
   */
  logger::LEVEL preferred_severity_level;
};

void logger::ICompareLevels::i_set_preferred_severity_level(logger::LEVEL preferred_severity_level)
{
  this->preferred_severity_level = preferred_severity_level;
}

logger::LEVEL logger::ICompareLevels::i_get_preferred_severity_level() { return this->preferred_severity_level; }

bool logger::ICompareLevels::i_compare_levels(logger::LEVEL level_1, logger::LEVEL level_2)
{
  return this->compare_levels(level_1, level_2);
}
};// namespace logger
#endif// ! COMPARE_LEVELS_HPP
