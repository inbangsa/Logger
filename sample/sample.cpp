#ifndef SAMPLE_CPP
#define SAMPLE_CPP

#include <iostream>
#include "logger/logger_lib.hpp"


void CreateLoggerObject()
{
logger::Logger logging_obj ;
logging_obj.Log(logger::log_level::DEBUG, "sample message");
}

void SetSomeFeaturesUsingObject() 
{
  auto logging_obj = logger::Logger();
   logging_obj.SetLoggerName("new logger");
   logging_obj.SetLogLevel(logger::log_level::WARN);
   logging_obj.Log(logger::log_level::DEBUG, "sample message");
}

void LogDirectlyUsingMacro()
{ logger::OFF("sample message"); }


void SetSomeFeaturesUsingMacro() {
logger::SET_LOG_LEVEL(logger::log_level::WARN);
logger::SET_LOGGER_NAME("new logger");
logger::LOG(logger::log_level::DEBUG, "sample message");
}

bool SampleDivideFunction(int number_1, int number_2) 
{ 
  if (number_2 == 0) {
    throw std::exception("Divisor cannot be zero.");
     } else
    return number_1 / number_2;
}

int main()
{
  try {
    CreateLoggerObject();
    SetSomeFeaturesUsingObject();
    LogDirectlyUsingMacro();
    SetSomeFeaturesUsingMacro();
    SampleDivideFunction(10, 0);
  } catch (std::exception ex) {
    logger::FATAL(ex.what());
      std::cout << ex.what();
  }
  return 0;
}
#endif()