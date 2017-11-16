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
  Rotor();
  void loadRotor(const char* filename);
  void loadRotorPosition(const char* filename, int rotor_id, int number_rotors);
  char encodeChar(char c);
  char encodeCharBack(char c);
  void turn();
  bool testForNotch();
};

#endif
