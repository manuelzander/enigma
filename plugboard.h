#ifndef Enigma_Plugboard
#define Enigma_Plugboard

#include <iostream>
#include <string>
#include "helper.h"

using namespace std;

class Plugboard {
private:
  string input;
  string output;
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
