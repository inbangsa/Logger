#ifndef SINK_HPP
#define SINK_HPP

#include "formatter.hpp"

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

ISink::ISink(std::shared_ptr<logger::IFormatter> &formatter_ptr) : formatter_ptr(formatter_ptr) {}

bool logger::ISink::Record(std::string msg,
  logger::LEVEL level,
  std::string &logger_name,
  std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials)
{
  return this->record(msg, level, logger_name, log_credentials);
}

std::shared_ptr<logger::IFormatter> logger::ISink::GetFormatterPtr() { return this->formatter_ptr; }

};// namespace logger

#endif()