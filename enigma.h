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
  //Checking and loading of config files
  int config(int argc, char** argv);
  //Checking of plugboard config files
  int checkPlugboardConfig(const char* filename);
  //Checking of reflector config files
  int checkReflectorConfig(const char* filename);
  //Checking of rotor positions config files
  int checkRotorPositionsConfig(const char* filename);
  //Checking of rotor mapping config files
  int checkRotorConfig(const char* filename);
  //Print appropriate message to standart error stream
  int printErrorMessage(int code);
  //Main function for the whole process (takes input char and returns output char)
  char encode(char c);
  //Function to manage the rotor process (before reflector)
  char runRotors(char c);
  //Function to manage the rotor process (after reflector)
  char runRotorsBack(char c);
  //Function to call test and manage the turns for all rotors if appropriate
  void turnRotors();
};

#endif
