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
  //Mapping of character (before reflector)
  char encodeChar(char c);
  //Mapping of character (after reflector)
  char encodeCharBack(char c);
  //Change the position (rotation) of rotor
  void turn();
  //Test if notch specified for given position
  bool testForNotch();
};

#endif
