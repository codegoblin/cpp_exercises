//
//  main.cpp
//  test
//
//  Created by Cody Johnston on 9/18/11.
//

#include <iostream>

int main (int argc, const char * argv[])
{
  int iterations = 0;
  
  do {
    std::cout << ( iterations + 1 )<< " ";
    std::cout << "Hello, World!\n";
    iterations++;
  } while (iterations < 10);
  return 0;
}