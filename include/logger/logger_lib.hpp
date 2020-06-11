#ifndef LOGGER_LIB_HPP
#define LOGGER_LIB_HPP

#include "sink.hpp"
#include <vector>

namespace logger {
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
    const std::string& logger_name = "default_logger",
    logger::log_level log_level = logger::log_level::TRACE)
  {
    this->sink_ptr = sink_ptr;
    log_setting.logger_name = logger_name;
    log_setting.desired_level = log_level;
  }

  // Copy and Copy Assignment Operator set to default.
  Logger(const Logger&) = default;
  Logger& operator=(const Logger&) = default;

  // Move and Move Assignment Operator set to default.
  Logger(Logger&&) = default;
  Logger& operator=(Logger&&) = default;

  /*
   *@brief Method to Log the  message at specified level.
   *@param level desired log level
   *@param message log message
   *@retval void
   */
  void Log(logger::log_level level, const std::string& message)
  {
    if (level <= log_setting.desired_level) {
      auto log_credentials = logger::internal::ExtractedLogCredentials();
      sink_ptr->Record(message, level, log_setting.logger_name, log_credentials);
    }
  }

  /**
   * @brief Method to Log the  message at specified level with details such as date time etc.
   * @param level log level at which message is to be logged
   * @param message log message
   * @param date  date at which message was logged
   * @param time  time at which message was logged
   * @param file_name  file name where message was logged
   * @param function_name  function name at which message was logged
   * @param line_number  line number of  the logged message
   * @retval None
   */
  void Log(logger::log_level level,
    const std::string& message,
    const std::string& date,
    const std::string& time,
    const std::string& file_name,
    const std::string& function_name,
    const int& line_number)
  {
    if (level <= log_setting.desired_level) {
      auto log_credentials =
        logger::internal::ExtractedLogCredentials(date, time, file_name, function_name, line_number);
      sink_ptr->Record(message, level, log_setting.logger_name, log_credentials);
    }
  }

  /*
   *@brief Method to log message to TRACE level directly.
   *@param message log message
   *@retval void
   */
  void Trace(const std::string& message) { Log(logger::log_level::TRACE, message); }

  /*
   *@brief Method to log message to WARN level directly.
   *@param message log message
   *@retval void
   */
  void Warn(const std::string& message) { Log(logger::log_level::WARN, message); }

  /*
   *@brief Method to log message to ERROR level directly.
   *@param message log message
   *@retval void
   */
  void Error(const std::string& message) { Log(logger::log_level::ERROR, message); }

  /*
   *@brief Method to log message to Debug level directly.
   *@param message log message
   *@retval  void
   */
  void Debug(const std::string& message) { Log(logger::log_level::DEBUG, message); }

  /*
   *@brief Method to log message to FATAL level directly.
   *@param message log message
   *@retval  void
   */
  void Fatal(const std::string& message) { Log(logger::log_level::FATAL, message); }

  /*
   *@brief Method to log message to OFF level directly.
   *@param message log message
   *@retval  void
   */
  void Off(const std::string& message) { Log(logger::log_level::OFF, message); }

  /*
   *@brief Method to set the desired log level.
   *@param level desired log level
   *@retval  void
   */
  void SetLogLevel(logger::log_level level) { log_setting.desired_level = level; }

  /*
   *@brief Method set logger name.
   *@param logger_name logger name
   *@retval void
   */
  void SetLoggerName(const std::string& logger_name) { log_setting.logger_name = logger_name; }

  /*
   *@brief Method to set the user defined sink;
   *@param any_sink_ptr user defined sink
   *@retval None
   */
  void SetSink(std::shared_ptr<logger::ISink> any_sink_ptr) { sink_ptr = any_sink_ptr; }

private:
  /*
   *@brief Object to store logger name and desired log level.
   */
  logger::internal::LogSettings log_setting;

  /*
   *@brief A Pointer to the class sink interface for accessing recording data.
   */
  std::shared_ptr<logger::ISink> sink_ptr;
};

/*
 *@brief Namespace for internal  operations.
 */
namespace internal {
  static Logger internal_obj;
};

// Macro based logging feature.
/*
 *@brief Macro-Log logs the data at the specified level.
 *@param level log level
 *@param message logging message
 */
#define LOG(level, message) internal::internal_obj.Log(level, message, __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__)
 
/*
 *@brief Macro-TRACE logs the data at the trace level.
 *@param message logging message
 */
#define TRACE(message) internal::internal_obj.Log(logger::log_level::TRACE, message, __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__)

/*
 *@brief Macro-DEBUG logs the data at the debug level.
 *@param message logging message
 */
#define DEBUG(message) internal::internal_obj.Log(logger::log_level::DEBUG, message, __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__)

/*
 *@brief Macro-WARN logs the data at the warn level.
 *@param message logging message
 */
#define WARN(message) internal::internal_obj.Log(logger::log_level::WARN, message, __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__)

/*
 *@brief Macro-ERROR logs the data at the error level.
 *@param message logging message
 */
#define ERROR(message) internal::internal_obj.Log(logger::log_level::ERROR, message, __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__)

/*
 *@brief Macro-FATAL logs the data at the fatal level.
 *@param message logging message
 */
#define FATAL(message) internal::internal_obj.Log(logger::log_level::FATAL, message, __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__)

/*
 *@brief Macro-OFF logs the data at the off level.
 *@param message logging message
 */
#define OFF(message) internal::internal_obj.Log(logger::log_level::OFF, message, __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__)

/*
 *@brief Sets the user defined sink.
 *@param sink_ptr pointer to user defined sink
 */
#define SET_SINK(sink_ptr) internal::internal_obj.SetSink(sink_ptr)

/*
 *@brief Set the log severity level.
 *@param level desired severity level
 */
#define SET_LOG_LEVEL(level) internal::internal_obj.SetLogLevel(level)

/*
 *@brief Sets the logger name.
 *@param logger_name logger name
 */
#define SET_LOGGER_NAME(logger_name) internal::internal_obj.SetLoggerName(logger_name)
};// namespace logger
#endif()