#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "enigma.h"

using namespace std;

void Enigma::turnRotors(){

  cout << endl << "Turn rotor 0" << endl;
  rotor_array[0].turn();

  for(int i = 0; i < number_rotors; i++) {
		if(rotor_array[i].testForNotch() == true && number_rotors > i+1) {
      cout << endl << "Notch hit, turn rotor " << i + 1 << endl;
			rotor_array[i+1].turn();
		} else{
      break;
    }
	}

}

char Enigma::runRotors(char c){

  for(int i = 0; i < number_rotors; i++){
    c = rotor_array[i].encodeChar(c);
  }

  return c;
}

char Enigma::runRotorsBack(char c){

  for(int i = number_rotors-1; i >= 0; i--){
    c = rotor_array[i].encodeCharBack(c);
  }

  return c;
}

char Enigma::encode(char c){

  c = c - 65; //Convert from ASCII to 0 based alphabet

  // 1. run of plugboard
  c = plugboard.runPlugboard(c);

  //Forward rotor encryption
  if (number_rotors != 0)
    this->turnRotors();
    c = this->runRotors(c);

  // Reflector encryption
	c = reflector.runReflector(c);

  // Backwards rotor encryption
  if (number_rotors != 0)
    c = this->runRotorsBack(c);

  // 2. run of plugboard
  c = plugboard.runPlugboard(c);

  return c + 65; //Convert from 0 based alphabet to ASCII
}

int Enigma::checkRotorPositionsConfig(const char* filename){

  cout << "Checking rotor positions config..." << endl;

  ifstream input;
  input.open(filename);

  int input_int;
  int count = 0;

  input >> input_int;

  while (!input.eof()){

    //Checking for INVALID_INDEX
    if(input_int < 0 || input_int > 25){
      cerr << "You provided an invalid index! (3)" << endl;
      return INVALID_INDEX;
    }

    //Checking for NON_NUMERIC_CHARACTER
    if (!input.good() && !input.eof()){
      cerr << "You provided a non-numeric rotor position parameter! (4)" << endl;
      return NON_NUMERIC_CHARACTER;
    }

    count++;
    input >> input_int;

  }

  if (count < number_rotors){
    cerr << "Not enough starting positions specified! (8)" << endl;
    //exit(NO_ROTOR_STARTING_POSITION);
    return NO_ROTOR_STARTING_POSITION;
  }

  cout << "Rotor positions config correct!" << endl;
  input.close();
  return NO_ERROR;

}
