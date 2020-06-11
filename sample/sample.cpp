#ifndef SAMPLE_CPP
#define SAMPLE_CPP

#include <iostream>
#include "logger/logger_lib.hpp"

bool Divide(int number_1, int number_2) 
{ 
  if (number_2 == 0) {
    throw std::exception("Divisor cannot be zero.");
     } else
    return number_1 / number_2;
}

int main()
{
  try {
    Divide(10, 0);  
  } catch (std::exception ex) {
    logger::FATAL("Divisor is zero.");
      std::cout << ex.what();
  }
  return 0;
}
#endif()