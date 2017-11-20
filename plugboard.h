#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <iostream>
#include <string>
#include "helper.h"

using namespace std;

class Plugboard {
private:
  int number_count;
  int plugboardconfig[ALPHABET_SIZE];

public:
  Plugboard();
  //Mapping of character
  char runPlugboard(char c);
  void loadPlugboard(const char* filename);
};

#endif
