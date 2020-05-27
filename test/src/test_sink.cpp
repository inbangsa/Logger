#ifndef TEST_SINK_CPP
#define TEST_SINK_CPP

#include "sink.hpp"
#include "catch2/catch.hpp"

TEST_CASE("DumpsDatatoFile", "[DefaultSinkWritesToFile]")
{
  logger::DefaultSink default_sink;
  const std::string function_name{ "SampleFunction()" }, msg{ "sample message" }, logger_name{ "sample logger" };
  logger::log_level level = logger::log_level::OFF;
  std::string log_level_string = "OFF";
  const logger::internal::ExtractedLogCredentials log_credentials(__DATE__, __TIME__, __FILE__, function_name, __LINE__);
   
   default_sink.Record( msg,level,logger_name,log_credentials);
   bool status = false;
   std::fstream fout; 
   fout.open("logs.txt");
   if (fout.is_open())
   {
     status = true;
     fout.close();
   }

    REQUIRE(status);

   }
#endif()