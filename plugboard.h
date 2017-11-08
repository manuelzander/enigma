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
  Plugboard(){ //Constructor
    for (int i = 0; i < ALPHABET_SIZE; i++)
      plugboardconfig[i] = 0;

  }

	int checkPlugboardConfig(const char* filename);
  void loadPlugboard(const char* filename);
  string runPlugboard(string input);
};

#endif
