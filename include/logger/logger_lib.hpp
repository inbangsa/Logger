#ifndef LOGGER_LIB_HPP
#define LOGGER_LIB_HPP

#include "formatter.hpp"
namespace logger {
/**
 * @brief  Log level with their severity order , 0 =>high priority , 5=> least priority.
 */
enum class LEVEL : { OFF = 0, FATAL = 1, ERROR = 2, WARN = 3, DEBUG = 4, TRACE = 5 };

/**
 * @brief  Interface for the extracted log data like file name , function name etc , one may extend for more parameters
 * such as number of argumnets __VA_ARGS__.
 */
struct ExtractedLogCredentials
{
  std::string file_name = "";
  std::string function_name = "";
  int line_number = 0;
};
};// namespace logger
#endif()
