#ifndef SINK_HPP
#define SINK_HPP

#include "formatter.hpp"
#include <fstream>

namespace logger {
/**
 * @brief Interface for writing the formatted data/log details to a sink such as file, database, webserver etc.
 */
class ISink
{
public:
  /**
   * @brief Ctor that assigns the pointer to the formatter class.
   * @param formatter_ptr used to format the data
   * @retval None
   */
  ISink(std::shared_ptr<logger::IFormatter> &formatter_ptr);

  /**
   * @brief To access the record method.
   * @param msg log message
   * @param level log level
   * @param logger_name logger name
   * @param log_credentials extracted log credentials
   * @retval bool
   */
  bool Record(std::string msg,
    logger::LEVEL level,
    std::string &logger_name,
    std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials);

  /**
   * @brief  A getter to access formatter_ptr.
   * @param None
   * @retval std::shared_ptr<logger::IFormatter>
   */
  std::shared_ptr<logger::IFormatter> GetFormatterPtr();

private:
  /**
   * @brief To record the data to a dedicated sink.
   * @param msg log message
   * @param level log level
   * @param logger_name logger name
   * @param log_credentials extracted log credentials
   * @retval bool
   */
  virtual bool record(std::string msg,
    logger::LEVEL level,
    std::string &logger_name,
    std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials) = 0;

  /**
   * @brief Pointer to fomatter class.
   */
  std::shared_ptr<logger::IFormatter> formatter_ptr;
};

/**
 * @brief Writes the log message and relevant information to default sink.
 */
class DefaultSink : public logger::ISink
{
public:
  /**
   * @brief Ctor for Default Sink ,to initialize userdefined formatter and log file name.
   * @param formatter pointer to interface format class used to format data
   * @param file_name  destination file name where the logs are to be recorded
   * @retval None
   */
  DefaultSink(std::shared_ptr<logger::IFormatter> formatter = std::make_shared<logger::DefaultFormatter>(),
    std::string log_file_name = "logs.txt");

  /**
   * @brief Sets destination file name where the logs are to be recorded.
   * @param file_name destination file name where the logs are to be recorded
   * @retval None
   */
  void set_log_file_name(std::string log_file_name);

private:
  /**
   * @brief To record the data to a dedicated sink.
   * @param msg log message
   * @param level log level
   * @param logger_name logger name
   * @param log_credentials extracted log credentials
   * @retval bool
   */
  bool record(std::string msg,
    logger::LEVEL level,
    std::string &logger_name,
    std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials) override;

/**
   * @brief Variable to store log file name.
*/
  std::string log_file_name;
};

// Definitions of class ISink methods.
ISink::ISink(std::shared_ptr<logger::IFormatter> &formatter_ptr) : formatter_ptr(formatter_ptr) {}

bool logger::ISink::Record(std::string msg,
  logger::LEVEL level,
  std::string &logger_name,
  std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials)
{
  return this->record(msg, level, logger_name, log_credentials);
}

std::shared_ptr<logger::IFormatter> logger::ISink::GetFormatterPtr() { return this->formatter_ptr; }

// Definitions of class DefaultSink methods.
logger::DefaultSink::DefaultSink(std::shared_ptr<logger::IFormatter> formatter, std::string log_file_name)
  : ISink(formatter), log_file_name(log_file_name)
{}

void logger::DefaultSink::set_log_file_name(std::string log_file_name) { log_file_name = log_file_name; }

bool logger::DefaultSink::record(std::string msg,
  logger::LEVEL level,
  std::string &logger_name,
  std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials)
{
  std::ofstream out;
  out.open(log_file_name, std::ios::app);
  auto formatter_ptr = GetFormatterPtr(); 
  auto formatted_string= formatter_ptr->FormatData(msg, level, logger_name, log_credentials);
  out << formatted_string;
  out.close();
  return out.bad() == true ? false : true;
}
};// namespace logger

#endif()