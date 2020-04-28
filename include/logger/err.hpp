#ifndef ERROR_HPP
#define ERROR_HPP
#include <string>
#include <map>

/*
 *@brief namespace for logger lib .
 */
namespace logger {

/*
 *@brief namespace for error code .
 */
namespace error_code {

  const std::string ERROR_101{ "[Error 101] : Data found to be empty." };
  const std::string ERROR_102{ "[Error 102] : Nullpointer Error." };
};// namespace error_code
};// namespace logger


#endif