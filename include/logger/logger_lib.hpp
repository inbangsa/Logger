#ifndef LOGGER_LIB_HPP
#define LOGGER_LIB_HPP

#include "sink.hpp"

/**
 * @brief Macro FLAG_ON() extracts the log data such as date, time, line number,file name,function name from where it is being
 called.Note to use this it has to be passed as function argument explicitly and works inside a function  only. * @param format_pattern pattern that will be used to format  the data 
 */
#define FLAG_ON() logger::extract_log_data(__DATE__, __TIME__, __FILE__, __LINE__, __FUNCTION__)

 /**
 * @brief  Macro FLAG_OFF() extracts the log date only date and time .
 */
#define FLAG_OFF() logger::extract_log_data(__DATE__, __TIME__)

namespace logger {

using LogPtr = std::shared_ptr<logger::ExtractedLogCredentials>;

/**
 * @brief Extracts the log credentials such as date, time, file name,line number,function name. 
 * @param date Date ,when the function is called 
 * @param time Time ,when the function is called 
 * @param file_name File name,from where the function is called 
 * @param line_number Line Number at which the function is being called
 * @param function_name  Name of the function from where it is called .
 * @retval LogPtr
 */
LogPtr extract_log_data(std::string date,
  std::string time,
  std::string file_name,
  int line_number,
  std::string function_name)
{
  auto ptr = std::make_shared<logger::ExtractedLogCredentials>();
  ptr->date = date;
  ptr->time = time;
  ptr->file_name = file_name;
  ptr->line_number = line_number;
  ptr->function_name = function_name;

  return ptr;
}

/**
 * @brief Extracts the log credentials only  date, time.
 * @param date Date ,when the function is called
 * @param time Time ,when the function is called
 * @retval LogPtr
 */
LogPtr extract_log_data(std::string date,
  std::string time,...)
{
  auto ptr = std::make_shared<logger::ExtractedLogCredentials>();
  ptr->date = date;
  ptr->time = time;
  
  return ptr;
}

}

#endif()
