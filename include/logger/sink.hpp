#ifndef SINK_HPP
#define SINK_HPP

#include "formatter.hpp"
#include <fstream>
#include <exception>

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
  ISink(const std::shared_ptr<logger::IFormatter> &formatter_ptr);

  /**
   * @brief To access the record method.
   * @param msg log message
   * @param log_level log log_level
   * @param logger_name logger name
   * @param log_credentials extracted log credentials
   * @retval None
   */
  void Record(const std::string &msg,
    const logger::log_level &log_level,
    const std::string &logger_name,
    const std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials);

protected:
  /**
   * @brief Pointer to fomatter class.
   */
  std::shared_ptr<logger::IFormatter> formatter_ptr;

private:
  /**
   * @brief To record the data to a dedicated sink.
   * @param msg log message
   * @param log_level log log_level
   * @param logger_name logger name
   * @param log_credentials extracted log credentials
   * @retval None
   */
  virtual void record(const std::string &msg,
    const logger::log_level &log_level,
    const std::string &logger_name,
    const std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials) = 0;
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
  DefaultSink(const std::shared_ptr<logger::IFormatter> &formatter = std::make_shared<logger::DefaultFormatter>(),
    const std::string &log_file_name = "logs.txt");

  /**
   * @brief Sets destination file name where the logs are to be recorded.
   * @param file_name destination file name where the logs are to be recorded
   * @retval None
   */
  void SetLogFileName(const std::string &log_file_name);

private:
  /**
   * @brief To record the data to a dedicated sink.
   * @param msg log message
   * @param log_level log log_level
   * @param logger_name logger name
   * @param log_credentials extracted log credentials
   * @retval None
   */
  void record(const std::string &msg,
    const logger::log_level &log_level,
    const std::string &logger_name,
    const std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials) override;

  /**
   * @brief Writes the formatted data to the file.
   * @param formatted_data formatted data
   * @retval None
   */
  void writeToFile(const std::string &formatted_data);

  /**
   * @brief Variable to store log file name.
   */
  std::string log_file_name;
};

// Definitions of class ISink methods.
ISink::ISink(const std::shared_ptr<logger::IFormatter> &formatter_ptr) : formatter_ptr(formatter_ptr) {}

void logger::ISink::Record(const std::string &msg,
  const logger::log_level &log_level,
  const std::string &logger_name,
  const std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials)
{
  this->record(msg, log_level, logger_name, log_credentials);
}

// Definitions of class DefaultSink methods.
logger::DefaultSink::DefaultSink(const std::shared_ptr<logger::IFormatter> &formatter, const std::string &log_file_name)
  : ISink(formatter), log_file_name(log_file_name)
{}

void logger::DefaultSink::SetLogFileName(const std::string &log_file_name) { this->log_file_name = log_file_name; }

void logger::DefaultSink::writeToFile(const std::string &formatted_data)
{
  std::fstream fout;
  fout.open(log_file_name, std::ios::app);
  if (fout.is_open()) {
    fout << formatted_data << std::endl;
    fout.close();
     } else {
    throw std::exception("File cannot be opened !!");
  }
}

void logger::DefaultSink::record(const std::string &msg,
  const logger::log_level &log_level,
  const std::string &logger_name,
  const std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials)
{
  auto formatted_data = formatter_ptr->FormatData(msg, log_level, logger_name, log_credentials);
  this->writeToFile(formatted_data);
}
};// namespace logger
#endif()