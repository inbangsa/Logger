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

protected:
  /**
   * @brief Pointer to fomatter class.
   */
  std::shared_ptr<logger::IFormatter> formatter_ptr;

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
  void SetLogFileName(std::string log_file_name);

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
   * @brief Writes the formatted data to the file.
   * @param formatted_data formatted data
   * @retval bool
   */
  bool writeToFile(std::string formatted_data);

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

// Definitions of class DefaultSink methods.
logger::DefaultSink::DefaultSink(std::shared_ptr<logger::IFormatter> formatter, std::string log_file_name)
  : ISink(formatter), log_file_name(log_file_name)
{}

void logger::DefaultSink::SetLogFileName(std::string log_file_name) { log_file_name = log_file_name; }

bool logger::DefaultSink::writeToFile(std::string formatted_data)
{
  std::fstream fout;
  fout.open(log_file_name, std::ios::app);
  if (fout.is_open()) 
  {
	//considering corner case.if file is empty append from begining , else append from next line.
    fout.seekg(0, std::ios::end);
    auto length = fout.tellg();
    if (length != 0) {fout << "\n";}
    fout << formatted_data;
    fout.close();
  } 
  return true;
}
bool logger::DefaultSink::record(std::string msg,
  logger::LEVEL level,
  std::string &logger_name,
  std::shared_ptr<logger::ExtractedLogCredentials> &log_credentials)
{
  auto formatted_data = formatter_ptr->FormatData(msg, level, logger_name, log_credentials);
  return writeToFile(formatted_data);
}
};// namespace logger

#endif()