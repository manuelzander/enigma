#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <string>
#include "helper.h"
#include "plugboard.h"
#include "rotors.h"
#include "reflector.h"

using namespace std;

class Enigma {
private:
  int numRotors;
  string input;
  string output;
  Plugboard plugboard;
  Rotors rotors;

public:
  Enigma(int _i, Plugboard _p, Rotors _r){ //Constructor

    if (_i == 3) //No rotors at all
      numRotors = 0;
    else if (_i >= 5){ //At least one rotor
      numRotors = _i - 4;
    }

    plugboard = _p;
    rotors = _r;

  }

  string encode(string message);
};

#endif
