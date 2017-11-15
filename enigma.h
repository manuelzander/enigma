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
  Enigma(int argc, char** argv){ //Constructor --> Move into enigma.cpp
    if (argc == 3){ //No rotor at all
      number_rotors = 0;
    }
    else if (argc >= 5){ //At least one rotor

      number_rotors = argc - 4;
      //cout << endl << "Number of rotors: " << number_rotors << endl;

      //Creating dynamic array for the rotors
      this->rotor_array = new Rotor[number_rotors];

      //Loading rotor objects into the dynamic array
      for (int i = 0; i < number_rotors; i++){
        rotor_array[i] = Rotor();
      }

    }
  }

  ~Enigma(){
    delete [] rotor_array; //Free memory
  }

  int checkPlugboardConfig(const char* filename);
  int checkReflectorConfig(const char* filename);
  int checkRotorPositionsConfig(const char* filename);
  int checkRotorConfig(const char* filename);
  int config(int argc, char** argv);
  char encode(char c);
  char runRotors(char c);
  char runRotorsBack(char c);
  void turnRotors();
};

#endif
