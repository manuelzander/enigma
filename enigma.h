#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <string>
#include "helper.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"

using namespace std;

class Enigma {
private:
  int number_rotors;
  Plugboard plugboard;
  Rotor *rotor_array;
  Reflector reflector;

public:
  Enigma(int argc, char** argv);
  ~Enigma();
  int config(int argc, char** argv);
  int checkPlugboardConfig(const char* filename);
  int checkReflectorConfig(const char* filename);
  int checkRotorPositionsConfig(const char* filename);
  int checkRotorConfig(const char* filename);
  int printErrorMessage(int code);
  char encode(char c);
  char runRotors(char c);
  char runRotorsBack(char c);
  void turnRotors();
};

#endif
