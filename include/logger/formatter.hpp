#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <string>
#include <memory>

namespace logger {
/**
 *@ brief  For specifying various severity levels.
 */
extern enum class LEVEL;

/**
 *@ brief  Data Structure for storing various extracted data  like function name , file name etc for a log .
 */
extern struct ExtractedLogCredentials;

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
  void set_format_pattern(std::string format_pattern);

  /**
   * @brief Returns formatting pattern.
   * @param None
   * @retval std::string
   */
  std::string get_format_pattern() const;

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

void logger::IFormatter::set_format_pattern(std::string format_pattern) { this->format_pattern = format_pattern; }

void logger::IFormatter::get_format_pattern() const { return format_pattern; }
};// namespace logger
#endif()