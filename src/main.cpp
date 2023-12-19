#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>

#include "application.hpp"

int main(int argc, char** argv)
{
  srand(time(NULL));
    
  application_t app;

  app.run();
  
  return 0;
} 