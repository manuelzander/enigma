#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "rotor.h"

using namespace std;


char Rotor::encodeChar(char c){

  cout << endl << "Rotation: " << rotation << endl;
  return rotorconfig[(c + rotation) % ALPHABET_SIZE];

}

char Rotor::encodeCharBack(char c){

  for(int i = 0; i < 26; i++){
    if(rotorconfig[i] == c){
      return ((i - rotation + ALPHABET_SIZE) % ALPHABET_SIZE);
    }
  }

}

void Rotor::loadRotor(const char* filename){

  ifstream input;
  input.open(filename);

  int i = 0; //Couter for rotorconfig-array
  //int number_notches = 0; //Couter for notchconfig-array
  int input_int;

  input >> input_int;

  while (!input.eof()){

    rotorconfig[i] = input_int;

    //Reading in of notches
    if(i >= 26){
      notchconfig[number_notches] = input_int;
      number_notches++;
    }

    i++;
    input >> input_int;
	}

  cout << endl << "Rotorconfig:" << i << endl;
  for(int i = 0; i < ROTOR_MAP_SIZE; i++){

    cout << endl << rotorconfig[i] << endl;

  }

  cout << endl << "Notchconfig:" << number_notches<< endl;
  for(int i = 0; i < number_notches; i++){

    cout << endl << notchconfig[i] << endl;

  }

  input.close();

}

void Rotor::loadRotorPosition(const char* filename, int rotor_id, int number_rotors){

  cout << endl << "Loading rotor positions for rotor " << rotor_id << "..."<< endl;

  ifstream input;
  input.open(filename);

  int input_int;

  input >> input_int;

  //Rotor id = 2

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
