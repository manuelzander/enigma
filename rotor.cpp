#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "rotor.h"

using namespace std;

Rotor::Rotor(){
  for (int i = 0; i < ROTOR_MAP_SIZE; i++){
    rotorconfig[i] = 0;
  }
  for (int i = 0; i < MAX_NOTCHES; i++){
    notchconfig[i] = 0;
  }

  rotation = 0;
  number_notches = 0;
}

char Rotor::encodeChar(char c){
  return (rotorconfig[(c + rotation) % ALPHABET_SIZE] - rotation + ALPHABET_SIZE) % ALPHABET_SIZE;
}

char Rotor::encodeCharBack(char c){

  c = (c + rotation) % ALPHABET_SIZE;
  for(int i = 0; i < ALPHABET_SIZE; i++){
    if(rotorconfig[i] == c){
      return (i - rotation + ALPHABET_SIZE) % ALPHABET_SIZE;
    }
  }

  return c;
}

void Rotor::loadRotor(const char* filename){

  ifstream input;
  input.open(filename);

  int i = 0; //Couter for rotorconfig-array
  int input_int;

  input >> input_int;

  while (!input.eof()){
    if (i < 26){
      rotorconfig[i] = input_int;
    }
    else{ //Reading in of notches

      //Only add another notch, if notch not in array yet
      if (number_notches > 0){
        bool found = false;
        for(int i = 0; i <= number_notches; i++){
          if (notchconfig[i] == input_int){
            found = true;
            break;
          }
        }

        if(found != true){
          notchconfig[number_notches] = input_int;
          number_notches++;
      }

      }else {
        notchconfig[number_notches] = input_int;
        number_notches++;
      }

    }
    i++;
    input >> input_int;
	}

  input.close();
}

void Rotor::loadRotorPosition(const char* filename, int rotor_id, int number_rotors){

  ifstream input;
  input.open(filename);
  int input_int;
  input >> input_int;

  for (int i = number_rotors-1; !input.eof(); i--){
    if (i == rotor_id){
      rotation = input_int;
    }
    input >> input_int;
  }

  input.close();
}

void Rotor::turn(){
  rotation = (rotation + 1) % ALPHABET_SIZE;
}

bool Rotor::testForNotch(){
  for(int i = 0; i < number_notches; i++){
    if (notchconfig[i] == rotation)
      return true;
  }
  return false;
}
