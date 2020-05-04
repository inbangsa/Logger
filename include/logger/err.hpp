#ifndef ERROR_HPP
#define ERROR_HPP

#include <exception>

/*
 *@brief Namespace for logger lib .
 */
namespace logger {

/*
 *@brief Namespace for error code .
 */
namespace error_handling {

  /*
   *@brief Error codes.
   */
  const int DATA_EMPTY = 101;
  const int LOG_CREDENTIALS_EMPTY = 102;
  const int EXTRACTED_LINE_ZERO = 103;

  /*
   *@brief Gives error message for particular error type.
   *@param error_code error code
   *@retval const char*
   */
  const char *GetErrorMessage(const int error_code)
  {
    switch (error_code) {

    case DATA_EMPTY:
      return " Data found to be empty.";
    case LOG_CREDENTIALS_EMPTY:
      return "Log credentials found to be empty.";
    case EXTRACTED_LINE_ZERO:
      return "Extracted line number found to be zero.";
    default:
      return "Undefined Error.";
    }
  }

  /*
   *@brief LoggerException is defined to faciliate the error handling related to logger lib.
   */
  class LoggerException : public std::exception
  {
  public:
    /*
     *@brief Ctor to initialize the error code and std::exception ctor.
     *@param error_code error code
     *@retval None
     */
    LoggerException(int error_code);

    /*
     *@brief Gives the error message whenever error is catched.
     *@param None
     *@retval const char*
     */
    virtual const char *what() const noexcept;

    /*
     *@brief Method to get the error code.
     *@param None
     *retval int
     */
    int get_errro_code() const noexcept;

  private:
    /*
     *@brief Variable to store error code.
     */
    int error_code;
  };

};// namespace error_handling

logger::error_handling::LoggerException::LoggerException(int error_code) : std::exception(), error_code(error_code) {}
const char *error_handling::LoggerException::what() const noexcept { return GetErrorMessage(this->get_errro_code()); }
int error_handling::LoggerException::get_errro_code() const noexcept { return this->error_code; }
};// namespace logger


#endif