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
 *@brief Sets the log severity level.
 *@param level  desired log severity level
 *@retval None
 */
void set_severity_level(logger::LEVEL level);

/*
 *@brief Sets the user defined sink.
 *@param any_sink_ptr user defined sink
 *@retval None
 */
void set_sink(std::shared_ptr<ISink> any_sink_ptr);

/*
 *@brief Sets the logger name.
 *@param logger_name desired logger name
 *@retval None
 */
void set_logger_name(std::string logger_name);

/*
 *@brief Method to check the if parameters passed are not empty or non zero.
 *@param date  date at which message is logged
 *@param time  time at which message is logged
 *@param line_number line_number from where message is logged
 *@param file_name file name from where message is logged
 *@param function_name  function name from where message is logged
 *@retval bool
 */
bool check_empty_log_credentials(std::string date,
  std::string time,
  int line_number,
  std::string file,
  std::string function);

/**
 * @brief To log message at a given level with extracted parameters such as date, time etc.
 * @param level log level
 *@param message message
 * @param date date at which message is logged
 * @param time time at which message is logged
 * @param line_number  line number from where message is logged
 * @param file_name  file name from where message is logged
 * @param function_name function name from where message is logged
 * @retval bool
 */
void log(logger::LEVEL level,
  std::string message,
  std::string date,
  std::string time,
  int line_number,
  std::string file_name,
  std::string function_name);

/*
 *@brief Logs the message at given level .
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
   *@retval void
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

  /*
   *@brief Method set logger name.
   *@param logger_name logger name
   *@retval void
   */
  void SetLoggerName(std::string logger_name);

  /*
   *@brief Method to set the log credentails , to be used if  message is to be logged along with extracted data
   *available such as time, date etc.
   *@param date  date at which message is logged
   *@param time  time at which message is logged
   *@param line_number line_number  from where message is logged
   *@param file_name file name  where messag is logged
   *@param function_name  function name from where message is logged
   *@retval None
   */
  void SetLogCredentials(std::string date,
    std::string time,
    int line_number,
    std::string file_name,
    std::string function_name);

  /*
   *@brief Method to get the log credentials , prefably user may not use it.
   *@param None
   *@retval std::shared_ptr<logger::ExtractedLogCredentials>
   */
  std::shared_ptr<logger::ExtractedLogCredentials> GetLogCredentials();

  /*
   *@brief Method to set the user defined sink;
   *@param any_sink_ptr user defined sink
   *@retval None
   */
  void SetSink(std::shared_ptr<logger::ISink> any_sink_ptr);

private:
  /*
   *@brief  Check if  the  test string  is empty or not.
   *@param any_string  test string
   *@retval bool
   */
  bool check_empty_string(std::string any_string);

  /*
   *@brief Object to store logger name and desired log level.
   */
  logger::LogSettings log_setting;

  /*
   *@brief A Pointer to the class sink interface for accessing recording data.
   */
  std::shared_ptr<logger::ISink> sink_ptr;

  /*
   *@brief A Pointer to the struct ExtractedLogCredentials for storing the extracted log data such as date ,time,
   *filename etc.
   */
  std::shared_ptr<logger::ExtractedLogCredentials> log_credentials;
};

/*
 *@brief A Logger class object to be used internally to do various operations for macros.
 */
Logger internal_object;

// Definitions for Macro associated functions.
void logger::set_severity_level(logger::LEVEL level) { internal_object.SetLogLevel(level); }

void logger::set_sink(std::shared_ptr<ISink> any_sink_ptr) { internal_object.SetSink(any_sink_ptr); }

void logger::set_logger_name(std::string logger_name) { internal_object.SetLoggerName(logger_name); }

bool logger::check_empty_log_credentials(std::string date,
  std::string time,
  int line_number,
  std::string file_name,
  std::string function_name)
{
  std::vector<std::string> test_string{ date, time, file_name, function_name };
  for (auto x : test_string) {

    if (x.empty()) { throw logger::error_handling::LoggerException(logger::error_handling::LOG_CREDENTIALS_EMPTY); }
  }
  if (line_number == 0) { throw logger::error_handling::LoggerException(logger::error_handling::EXTRACTED_LINE_ZERO); }
  return true;
}

void logger::log(logger::LEVEL level,
  std::string message,
  std::string date,
  std::string time,
  int line_number,
  std::string file_name,
  std::string function_name)
{
  check_empty_log_credentials(date, time, line_number, file_name, function_name);
  internal_object.SetLogCredentials(date, time, line_number, file_name, function_name);
  internal_object.Log(level, message);
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
  check_empty_string(message);
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

void Logger::SetLoggerName(std::string logger_name) { log_setting.logger_name = logger_name; }

void Logger::SetLogCredentials(std::string date,
  std::string time,
  int line_number,
  std::string file_name,
  std::string function_name)
{

  this->log_credentials = std::make_shared<logger::ExtractedLogCredentials>();
  log_credentials->date = date;
  log_credentials->time = time;
  log_credentials->line_number = line_number;
  log_credentials->function_name = function_name;
  log_credentials->file_name = file_name;
}

std::shared_ptr<logger::ExtractedLogCredentials> logger::Logger::GetLogCredentials() { return log_credentials; }

void logger::Logger::SetSink(std::shared_ptr<logger::ISink> any_sink_ptr) { sink_ptr = any_sink_ptr; }

bool logger::Logger::check_empty_string(std::string any_string)
{
  if (any_string.empty()) { throw logger::error_handling::LoggerException(logger::error_handling::DATA_EMPTY); }
  return true;
}
};// namespace logger
#endif() #endif()
