#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include "common.hpp"

namespace logger {
/**
 * @brief  Interface for formatting the given data.
 */
class IFormatter
{
public:
  /**
   * @brief Sets format pattern according to which formatting will be done.
   * @param format_pattern pattern that will be used to format  the data
   * @retval std::string
   */
  void SetFormatPattern(std::string format_pattern);

  /**
   * @brief Returns formatting pattern.
   * @param None
   * @retval std::string
   */
  std::string GetFormatPattern() const;

   /**
   * @brief Interface for accessing format function.
   * @param msg log message
   * @param level log level
   * @param logger_name default name is root
   * @param log_credentials extracted log credentials
   * @retval std::string
   */
  std::string FormatData(std::string msg,
    logger::LEVEL level,
    std::string &logger_name,
    std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials);

private:
  /**
   * @brief Formats the given data.
   * @param msg log message
   * @param level log level
   * @param logger_name default name is root
   * @param log_credentials extracted log credentials
   * @retval std::string
   */
  virtual std::string format(std::string msg,
    logger::LEVEL level,
    std::string &logger_name,
    std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials) = 0;

  /**
   * @brief User can set the format pattern depending upon which the data will be formatted.
 */
  std::string format_pattern;
};

void logger::IFormatter::SetFormatPattern(std::string format_pattern) { this->format_pattern = format_pattern; }

std::string logger::IFormatter::GetFormatPattern() const { return format_pattern; }

std::string logger::IFormatter::FormatData(std::string msg,
  logger::LEVEL level,
  std::string &logger_name,
  std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials)
{
  return this->format(msg, level, logger_name, log_credentials);
}
};// namespace logger
#endif()