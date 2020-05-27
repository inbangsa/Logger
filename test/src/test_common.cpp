#ifndef TEST_COMMON_CPP
#define TEST_COMMON_CPP

#include "catch2/catch.hpp"
#include "common.hpp"

TEST_CASE("All string params should be non empty and line number non zero", "[CheckValidLogCredentials]")
{
  std::string function_name = "CheckValidLogCredentials()";
  logger::internal::ExtractedLogCredentials obj(__DATE__, __TIME__, __FILE__, function_name, __LINE__);
  REQUIRE(obj.CheckValidLogCredentials() == true);
}

TEST_CASE("Empty params are not allowed", "[CheckValidLogCredentials]")
{
  std::string function_name = "CheckValidLogCredentials()";
  logger::internal::ExtractedLogCredentials obj(__DATE__, __TIME__, __FILE__, "", __LINE__);
  REQUIRE(obj.CheckValidLogCredentials() == false);
}

TEST_CASE("line number should not be zero", "[CheckValidLogCredentials]")
{
  std::string function_name = "CheckValidLogCredentials()";
  logger::internal::ExtractedLogCredentials obj(__DATE__, __TIME__, __FILE__, function_name, 0);
  REQUIRE(obj.CheckValidLogCredentials() == false);
}

TEST_CASE("Log level to string", "[Log level to string]")
{
  namespace ns = logger::internal;
  REQUIRE(ns::log_level_to_string.find(logger::log_level::OFF)->second == "OFF");
  REQUIRE(ns::log_level_to_string.find(logger::log_level::FATAL)->second == "FATAL");
  REQUIRE(ns::log_level_to_string.find(logger::log_level::DEBUG)->second == "DEBUG");
  REQUIRE(ns::log_level_to_string.find(logger::log_level::WARN)->second == "WARN");
  REQUIRE(ns::log_level_to_string.find(logger::log_level::ERROR)->second == "ERROR");
  REQUIRE(ns::log_level_to_string.find(logger::log_level::TRACE)->second == "TRACE");
}
#endif()