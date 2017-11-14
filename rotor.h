#ifndef rotor_H
#define rotor_H

#include <iostream>
#include <string>
#include "helper.h"

using namespace std;

class Rotor {
private:
  int rotorconfig[ROTOR_MAP_SIZE];
  int notchconfig[MAX_NOTCHES];
  int number_notches;
  int rotation;

public:
  Rotor(){
    for (int i = 0; i < ROTOR_MAP_SIZE; i++){
      rotorconfig[i] = 0;
    }
    for (int i = 0; i < MAX_NOTCHES; i++){
      notchconfig[i] = 0;
    }

    rotation = 0;
    number_notches = 0;
  }
	int checkRotorConfig(const char* filename);
  int checkRotorPositionsConfig(const char* filename);
  void loadRotor(const char* filename);
  int loadRotorPosition(const char* filename, int rotor_id, int number_rotors);
  char encodeChar(char c);
  char encodeCharBack(char c);
  void turn();
  bool testForNotch();
};

#endif
