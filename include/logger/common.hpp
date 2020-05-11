#ifndef COMMON_HPP
#define COMMON_HPP

#include <memory>
#include <string>
#include <vector>

namespace logger {
/**
 * @brief  Log level with their severity order , 0 =>high priority , 5=> least priority.
 */
enum class LEVEL : int { OFF = 0, FATAL = 1, ERROR = 2, WARN = 3, DEBUG = 4, TRACE = 5 };

/**
 * @brief  Interface for the extracted log data like file name , function name etc , one may extend for more
 * parameters such as number of argumnets __VA_ARGS__.
 */
struct ExtractedLogCredentials
{
  std::string date = "";
  std::string time = "";
  std::string file_name = "";
  std::string function_name = "";
  int line_number = 0;
};

/**
 * @brief Utiltiy function to check whether all the data like date, time etc are captured or not.
 * @param log_ptr data to be tested
 * @retval bool
 */
bool CheckValidLogCredentials(std::shared_ptr<logger::ExtractedLogCredentials> log_ptr)
{
  bool result = true;

  // Checking for line number not be zero.
  if (log_ptr->line_number == 0) {return false; }

  // Checking for strings to be empty.
  std::vector<std::string> test_string = { log_ptr->date, log_ptr->time, log_ptr->file_name, log_ptr->function_name };

  for (auto str : test_string) {
    if (str.empty()) {
      return false;
    }
  }
  return result;
}

/**
 *@brief Utility function to convert log levels to string.
 *@param level log level
 *@retval string
 */
std::string LevelToString(logger::LEVEL level)
{
  switch (level) {
  case logger::LEVEL::OFF:
    return std::string{ "OFF" };
  case logger::LEVEL::FATAL:
    return std::string{ "FATAL" };
  case logger::LEVEL::ERROR:
    return std ::string{ "ERROR" };
  case logger::LEVEL::DEBUG:
    return std::string{ "DEBUG" };
  case logger::LEVEL::WARN:
    return std::string{ "WARN" };
  case logger::LEVEL::TRACE:
  default:
    return std::string{ "TRACE" };
  }
}
};// namespace logger
// namespace logger
#endif()
