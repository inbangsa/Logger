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

/**
 * @brief DefaultFormatter Formats the data in a default format style,square brackets.
 */
class DefaultFormatter : public logger::IFormatter
{
private:
  /**
   * @brief Formats the data in a default format style,square brackets.
   * @param msg log message
   * @param level log level
   * @param logger_name logger name
   * @param log_credentials extracted log credentials
   * @retval std::string
   */
  std::string squareBracketStyleFormatMsg(std::string msg,
    logger::LEVEL level,
    std::string &logger_name,
    std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials);

  /**
   * @brief Functions gives call to one of the default type format function like square bracket or printf style format.
   * @param msg log message
   * @param level log level
   * @param logger_name logger name
   * @param log_credentials extracted log credentials
   * @retval std::string
   */
  std::string format(std::string msg,
    logger::LEVEL level,
    std::string &logger_name,
    std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials) override;
};
};// namespace logger

// Definitions of class IFormatter
void logger::IFormatter::SetFormatPattern(std::string format_pattern) { this->format_pattern = format_pattern; }

std::string logger::IFormatter::GetFormatPattern() const { return format_pattern; }

std::string logger::IFormatter::FormatData(std::string msg,
  logger::LEVEL level,
  std::string &logger_name,
  std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials)
{
  return this->format(msg, level, logger_name, log_credentials);
}

// Definitions of class DefaultFormatter.
std::string logger::DefaultFormatter::squareBracketStyleFormatMsg(std::string msg,
  logger::LEVEL level,
  std::string &logger_name,
  std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials)
{
  std::string formatted_string; 
  if (CheckValidLogCredentials(log_credentials)) {
  formatted_string = "[" + log_credentials->date + "]" + " [" + log_credentials->time + "]" + " ["
                       + log_credentials->file_name + "]" + " [" + std::to_string(log_credentials->line_number) + "]"
                       + " [" + log_credentials->function_name+"]"+" [" + logger_name + "]" + " [" + LevelToString(level) + "]" + " [" + msg + "]";
  } else {
    formatted_string += "[" + logger_name + "]" + " [" + LevelToString(level) + "]" + " [" + msg + "]";
  }
  return formatted_string;
}

std::string logger::DefaultFormatter::format(std::string msg,
  logger::LEVEL level,
  std::string &logger_name,
  std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials)
{
  return squareBracketStyleFormatMsg(msg, level, logger_name, log_credentials);
}

#endif()