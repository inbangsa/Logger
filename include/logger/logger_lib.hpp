#ifndef LOGGER_LIB_HPP
#define LOGGER_LIB_HPP

#include "err.hpp"
#include "sink.hpp"
#include <vector>
#include <exception>

/*
 *@brief Macro-Log logs the data at the specified level.
 *@param level log level
 *@param message logging message
 */
#define LOG(level, message) logger::log(level, message, __DATE__, __TIME__, __LINE__, __FILE__, __FUNCTION__)

/*
 *@brief Macro-TRACE logs the data at the trace level.
 *@param message logging message
 */
#define TRACE(message) logger::log(logger::LEVEL::TRACE, message, __DATE__, __TIME__, __LINE__, __FILE__, __FUNCTION__)

/*
 *@brief Macro-DEBUG logs the data at the debug level.
 *@param message logging message
 */
#define DEBUG(message) logger::log(logger::LEVEL::DEBUG, message, __DATE__, __TIME__, __LINE__, __FILE__, __FUNCTION__)

/*
 *@brief Macro-WARN logs the data at the warn level.
 *@param message logging message
 */
#define WARN(message) logger::log(logger::LEVEL::WARN, message, __DATE__, __TIME__, __LINE__, __FILE__, __FUNCTION__)

/*
 *@brief Macro-ERROR logs the data at the error level.
 *@param message logging message
 */
#define ERROR(message) logger::log(logger::LEVEL::ERROR, message, __DATE__, __TIME__, __LINE__, __FILE__, __FUNCTION__)

/*
 *@brief Macro-FATAL logs the data at the fatal level.
 *@param message logging message
 */
#define FATAL(message) logger::log(logger::LEVEL::FATAL, message, __DATE__, __TIME__, __LINE__, __FILE__, __FUNCTION__)

/*
 *@brief Macro-OFF logs the data at the off level.
 *@param message logging message
 */
#define OFF(message) logger::log(logger::LEVEL::OFF, message, __DATE__, __TIME__, __LINE__, __FILE__, __FUNCTION__)
/*
 *@brief Sets the user defined sink.
 *@param sink_ptr pointer to user defined sink
 */
#define SET_SINK(sink_ptr) logger::set_sink(sink_ptr)

/*
 *@brief Set the log severity level.
 *@param level desired severity level
 */
#define SET_SEVERITY_LEVEL(level) logger::set_severity_level(level)

/*
 *@brief Sets the logger name.
 *@param logger_name logger name
 */
#define SET_LOGGER_NAME(logger_name) logger::set_logger_name(logger_name)

namespace logger {

/*
 *@brief To store logger name and desired severity level.
 */
auto log_settings = std::make_shared<logger::LogSettings>();

/*
 *@brief To record the data to assiged sink.
 */
std::shared_ptr<logger::ISink> sink_ptr = std::make_shared<logger::DefaultSink>();

/*
 *@brief Sets the log severity level.
 *@param level   desired log severity level
 */
void set_severity_level(logger::LEVEL level);

/*
 *@brief Sets the user defined sink.
 *@param any_sink_ptr
 */
void set_sink(std::shared_ptr<ISink> any_sink_ptr);

/*
 *@brief Sets the logger name.
 *@param logger_name desired logger name
 */
void set_logger_name(std::string logger_name);

/*
 *@brief Method to check the if parameters passed are not empty.
 *@param logger_name desired logger name
 *@retval bool
 */
bool check_empty(std::string message, std::string date, std::string time, std::string file, std::string function);

/**
 * @brief To log message at a given level with extracted parameters such as date, time etc.
 * @param level log level
 * @param date date at which message is logged
 * @param time time at which message is logged
 * @param line  line number from where message is logged
 * @param file  file name from where message is logged
 * @param function function function name from where message is logged
 * @retval bool
 */
void log(logger::LEVEL level,
  std::string message,
  std::string date,
  std::string time,
  int line,
  std::string file,
  std::string function);

/*
 *@brief Logs the message at given level with no extacted data such as time , date etc.
 */
class Logger
{
public:
  /*
   *@brief Ctor for the Logger class.
   *@param sink_ptr  pointer to sink interface
   *@param logger_name  desired name of the logger
   *@param log_level  desired log level
   *@retval bool
   */
  Logger(std::shared_ptr<logger::ISink> sink_ptr = std::make_shared<logger::DefaultSink>(),
    std::string logger_name = "runtime_default_logger",
    logger::LEVEL log_level = logger::LEVEL::TRACE);

  /*
   *@brief Method to Log the  message at specified level.
   *@param level desired log level
   *@param message log message
   *@retval void
   */
  void Log(logger::LEVEL level, std::string message);

  /*
   *@brief Method to log message to TRACE level directly.
   *@param message log message
   *@retval  void
   */
  void Trace(std::string message);

  /*
   *@brief Method to log message to WARN level directly.
   *@param message log message
   *@retval  void
   */
  void Warn(std::string message);

  /*
   *@brief Method to log message to ERROR level directly.
   *@param message log message
   *@retval  void
   */
  void Error(std::string message);

  /*
   *@brief Method to log message to Debug level directly.
   *@param message log message
   *@retval  void
   */
  void Debug(std::string message);

  /*
   *@brief Method to log message to FATAL level directly.
   *@param message log message
   *@retval  void
   */
  void Fatal(std::string message);

  /*
   *@brief Method to log message to OFF level directly.
   *@param message log message
   *@retval  void
   */
  void Off(std::string message);

  /*
   *@brief Method to set the desired log level.
   *@param level desired log level
   *@retval  void
   */
  void SetLogLevel(logger::LEVEL level);

private:
  /*
   *@brief  Check if  the input parameter is empty or not.
   *@param message log message
   *@retval bool
   */
  bool check_empty(std::string message);

  /*
   *@brief Object to store logger name and desired log level.
   */
  logger::LogSettings log_setting;

  /*
   *@brief A Pointer to the class sink interface for accessing recording data.
   */
  std::shared_ptr<logger::ISink> sink_ptr;
};

// Definitions for Macro associated functions.
void logger::set_severity_level(logger::LEVEL level) { log_settings->desired_level = level; }

void logger::set_sink(std::shared_ptr<ISink> any_sink_ptr) { sink_ptr = any_sink_ptr; }

void logger::set_logger_name(std::string logger_name) { log_settings->logger_name = logger_name; }

bool logger::check_empty(std::string message,
  std::string date,
  std::string time,
  std::string file,
  std::string function)
{
  std::vector<std::string> test_string{ message, date, time, file, function };
  for (auto x : test_string) {
    if (x.empty()) { throw std::exception(logger::error_code::ERROR_101.c_str()); }
  }

  return true;
}

void logger::log(logger::LEVEL level,
  std::string message,
  std::string date,
  std::string time,
  int line,
  std::string file,
  std::string function)
{
  logger::check_empty(message, date, time, file, function);

  auto log_credentials = std::make_shared<logger::ExtractedLogCredentials>();
  log_credentials->date = date;
  log_credentials->time = time;
  log_credentials->line_number = line;
  log_credentials->file_name = file;
  log_credentials->function_name = function;

  if (level <= log_settings->desired_level) {
    auto logger_name = log_settings->logger_name;
    sink_ptr->Record(message, level, logger_name, log_credentials);
  }
}

// Defintions for the class Logger.
logger::Logger::Logger(std::shared_ptr<logger::ISink> sink_ptr, std::string logger_name, logger::LEVEL log_level)
{
  this->sink_ptr = sink_ptr;
  log_setting.logger_name = logger_name;
  log_setting.desired_level = log_level;
}

void logger::Logger::Log(logger::LEVEL level, std::string message)
{

  auto log_credentials = std::make_shared<logger::ExtractedLogCredentials>();
  check_empty(message);

  if (level <= log_setting.desired_level) {
    std::string logger_name = log_setting.logger_name;
    sink_ptr->Record(message, level, logger_name, log_credentials);
  }
}

void logger::Logger::Trace(std::string message) { Log(logger::LEVEL::TRACE, message); }

void logger::Logger::Warn(std::string message) { Log(logger::LEVEL::TRACE, message); }

void logger::Logger::Error(std::string message) { Log(logger::LEVEL::TRACE, message); }

void logger::Logger::Debug(std::string message) { Log(logger::LEVEL::TRACE, message); }

void logger::Logger::Fatal(std::string message) { Log(logger::LEVEL::TRACE, message); }

void logger::Logger::Off(std::string message) { Log(logger::LEVEL::TRACE, message); }

void logger::Logger::SetLogLevel(logger::LEVEL level) { log_setting.desired_level = level; }

bool logger::Logger::check_empty(std::string message)
{
  if (message.empty()) { throw std::exception(logger::error_code::ERROR_101.c_str()); }
  return true;
}

};// namespace logger
#endif()
