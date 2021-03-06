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
  void SetFormatPattern(const std::string& format_pattern) { this->format_pattern = format_pattern; }

  /**
   * @brief Returns formatting pattern.
   * @param None
   * @retval std::string
   */
  std::string GetFormatPattern() const { return format_pattern; }

  /**
   * @brief Interface for accessing format function.
   * @param msg log message
   * @param log_level log log_level
   * @param logger_name default name is root
   * @param log_credentials extracted log credentials
   * @retval std::string
   */
  std::string FormatData(const std::string& msg,
    const logger::log_level& log_level,
    const std::string& logger_name,
    const logger::internal::ExtractedLogCredentials& log_credentials)
  {
    return this->format(msg, log_level, logger_name, log_credentials);
  }

private:
  /**
   * @brief Formats the given data.
   * @param msg log message
   * @param log_level log log_level
   * @param logger_name default name is root
   * @param log_credentials extracted log credentials
   * @retval std::string
   */
  virtual std::string format(const std::string& msg,
    const logger::log_level& log_level,
    const std::string& logger_name,
    const logger::internal::ExtractedLogCredentials& log_credentials) = 0;

  /**
   * @brief User can set the format pattern depending upon which the data will be formatted.
   */
  std::string format_pattern;
};

/**
 * @brief DefaultFormatter Formats the data in a default format style,square brackets.
 */
class DefaultFormatter : public logger::IFormatter
{
private:
  /**
   * @brief Formats the data in a default format style,square brackets.
   * @param msg log message
   * @param log_level log log_level
   * @param logger_name logger name
   * @param log_credentials extracted log credentials
   * @retval std::string
   */
  std::string squareBracketStyleFormatMsg(const std::string& msg,
    const logger::log_level& log_level,
    const std::string& logger_name,
    const logger::internal::ExtractedLogCredentials& log_credentials)
  {
    const auto log_level_string = logger::internal::log_level_to_string.find(log_level)->second;
    std::string formatted_string;
    if (log_credentials.IsCheckValidLogCredentials()) {
      formatted_string = "[" + log_credentials.date + "]" + " [" + log_credentials.time + "]" + " ["
                         + log_credentials.file_name + "]" + " [" + std::to_string(log_credentials.line_number) + "]"
                         + " [" + log_credentials.function_name + "]" + " [" + logger_name + "]" + " ["
                         + log_level_string + "]" + " [" + msg + "]";
    } else {
      formatted_string += "[" + logger_name + "]" + " [" + log_level_string + "]" + " [" + msg + "]";
    }
    return formatted_string;
  }

  /**
   * @brief Functions gives call to one of the default type format function like square bracket or printf style format.
   * @param msg log message
   * @param log_level log log_level
   * @param logger_name logger name
   * @param log_credentials extracted log credentials
   * @retval std::string
   */
  std::string format(const std::string& msg,
    const logger::log_level& log_level,
    const std::string& logger_name,
    const logger::internal::ExtractedLogCredentials& log_credentials) override
  {
    return squareBracketStyleFormatMsg(msg, log_level, logger_name, log_credentials);
  }
};
};// namespace logger
#endif()