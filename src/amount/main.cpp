#include <iostream>
#include "amount.h"

int main() {
  Amount three_fiddy = Amount(USD, 3.5);
  std::cout << three_fiddy.to_string() << std::endl;
  
  three_fiddy.convert(DKK, 6.93);
  std::cout << three_fiddy.to_string() << std::endl;

  three_fiddy.add(DKK, 100);
  std::cout << three_fiddy.to_string() << std::endl;

  three_fiddy.add(USD, -10);
  std::cout << three_fiddy.to_string() << std::endl;
  
  return 0;

}