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
   * @brief Sets format pattern.
   * @param pattern formatting pattern
   * @retval std::string
   */
  void i_set_format_pattern(std::string format_pattern);

  /**
   * @brief Returns formatting pattern.
   * @param None
   * @retval std::string
   */
  std::string i_get_format_pattern() const;

   /**
   * @brief Interface for accessing format function.
   * @param msg log message
   * @param level log level
   * @param logger_name default name is root
   * @param log_credentials extracted log credentials
   * @retval std::string
   */
  std::string i_format_data(std::string msg,
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

private:
  std::string format_pattern;
};

void logger::IFormatter::i_set_format_pattern(std::string format_pattern) { this->format_pattern = format_pattern; }

std::string logger::IFormatter::i_get_format_pattern() const { return format_pattern; }

std::string logger::IFormatter::i_format_data(std::string msg,
  logger::LEVEL level,
  std::string &logger_name,
  std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials)
{
  return this->format(msg, level, logger_name, log_credentials);
}
};// namespace logger
#endif()