#ifndef COMMON_HPP
#define COMMON_HPP

#include <memory>
#include <string>
#include <map>
#include <vector>

namespace logger {
/**
 * @brief  Log Levels with their severity order , 0 =>high priority , 5=> least priority.
 */
enum class log_level : int { OFF = 0, FATAL = 1, ERROR = 2, WARN = 3, DEBUG = 4, TRACE = 5 };

/**
 *@brief Utility map to store log_levels as key and corresponding value as its equivalent string.
 */
const std::map<logger::log_level, const std::string> log_level_to_string{ { logger::log_level::OFF, "OFF" },
  { logger::log_level::FATAL, "FATAL" },
  { logger::log_level::ERROR, "ERROR" },
  { logger::log_level::WARN, "WARN" },
  { logger::log_level::DEBUG, "DEBUG" },
  { logger::log_level::TRACE, "TRACE" } };

/**
 * @brief  To deal with extracted log data like file name , function name etc.
 */
class ExtractedLogCredentials
{
public:
  /**
   * @brief Ctor to initialize various log credentials variables.
   * @param date  date at which message was logged
   * @param time  time at which message was logged
   * @param file_name  file name where message was logged
   * @param function_name  function name at which message was logged
   * @param line_number  line number of  the logged message    *
   * @retval None
   */
  ExtractedLogCredentials(const std::string& date,
    const std::string& time,
    const std::string& file_name,
    const std::string& function_name,
    const int& line_number);

  /**
   * @brief Method to check whether all the data like date, time etc are captured or not.
   * @retval bool
   */
  bool CheckValidLogCredentials();

  /**
   * @brief Variable to store date, time, function name and file name related to logging of message.
   */
  const std::string date, time, file_name, function_name;

  /**
   * @brief Variable to store line number related to logging of message.
   */
  const int line_number = 0;
};

// Definitions of methods of class ExtractLogCredentials.
ExtractedLogCredentials::ExtractedLogCredentials(const std::string& date,
  const std::string& time,
  const std::string& file_name,
  const std::string& function_name,
  const int& line_number)
  : date(date), time(time), file_name(file_name), function_name(function_name), line_number(line_number)
{}

bool ExtractedLogCredentials::CheckValidLogCredentials()
{
  bool result = true;

  // Checking for line number not be zero.
  if (line_number == 0 ){ return false; }

  // Checking for strings to be empty.
  if (date.empty()) { return false; }
  else if (time.empty()) {
    return false;
  } else if (function_name.empty()) {
    return false;
  } else if (file_name.empty()) {
    return false;
  }
  return result;
}
};// namespace logger
#endif()
