#ifndef rotor_H
#define rotor_H

#include <iostream>
#include <string>
#include "helper.h"

using namespace std;

class Rotor {
private:
  int rotorconfig[ROTOR_MAP_SIZE];
  int reverse_rotorconfig[ROTOR_MAP_SIZE];


public:
  Rotor(){ //Constructor



  }
	int checkRotorConfig(const char* filename);
  void loadRotor(const char* filename);
  char encodeChar(char c);
  char encodeCharBack(char c);

};

#endif
