#ifndef TEST_FORMATTER_CPP
#define TEST_FORMATTER_CPP

#include "catch2/catch.hpp"
#include "formatter.hpp"

TEST_CASE("Formatter formats given data based on ExtractLogCredentialas Parameters", "[FormatData]")
{
  logger::DefaultFormatter default_formatter;
  const std::string function_name{ "SampleFunction()" }, msg{ "sample message" }, logger_name{ "sample logger" } ;
  logger::log_level level = logger::log_level::OFF;
  auto log_level_string=logger::internal::log_level_to_string.find(level)->second;

  SECTION( "Format with all params of ExtractLogCredentials are present","[FormatDataWithAllParams]") 
 {
   const logger::internal::ExtractedLogCredentials log_credentials(__DATE__, __TIME__, __FILE__, function_name, __LINE__);
   const std::string desired_result = "[" + log_credentials.date + "]" + " [" + log_credentials.time + "]" + " [" + log_credentials.file_name + "]"
      + " [" + std::to_string(log_credentials.line_number) + "]" + " [" + log_credentials.function_name + "]" + " ["
      + logger_name + "]" + " [" + log_level_string + "]" + " [" + msg + "]";
   
	REQUIRE(default_formatter.FormatData(msg, level, logger_name,log_credentials)==desired_result);
  }

  SECTION("Format data to string logger name and level when any params of ExtractLogCredentials are empty or zero", "[FormatDataWithSomeParams]")
  {
    const logger::internal::ExtractedLogCredentials log_credentials("", __TIME__, __FILE__, function_name,0);
    const std::string desired_result ="["+ logger_name + "]" + " [" + log_level_string + "]" + " [" + msg + "]";
    REQUIRE(default_formatter.FormatData(msg, level, logger_name, log_credentials) == desired_result);
  }
}
#endif()