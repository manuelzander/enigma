#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"

using namespace std;

class Enigma {
private:
  int numRotor;
  string input;
  string output;
  Plugboard plugboard;
  //Rotor** rotor_array;
  vector<Rotor> rotor_vector;
  Rotor rotor;
  Reflector reflector;

public:
  Enigma(int argc, char** argv){ //Constructor
    if (argc == 3) //No rotor at all
      numRotor = 0;
    else if (argc >= 5){ //At least one rotor
      numRotor = argc - 4;
    }

    plugboard.checkPlugboardConfig(argv[1]);
    plugboard.loadPlugboard(argv[1]);
    reflector.loadReflector(argv[2]);
  }

  string encode(string message);
  char runRotorProcess(char c);
  char runRotors(char c);
  char runRotorsBack(char c);
};

#endif
