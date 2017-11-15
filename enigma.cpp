#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "enigma.h"

using namespace std;

void Enigma::turnRotors(){

  //cout << endl << "Turn rotor 0" << endl;
  rotor_array[0].turn();

  for(int i = 0; i < number_rotors; i++) {
		if(rotor_array[i].testForNotch() == true && number_rotors > i+1) {
      //cout << endl << "Notch hit, turn rotor " << i + 1 << endl;
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

int Enigma::config(int argc, char** argv){

  if (checkPlugboardConfig(argv[1]) != 0){
    return checkPlugboardConfig(argv[1]);
  }
  if(checkReflectorConfig(argv[2]) != 0){
    return checkReflectorConfig(argv[2]);
  }

  for (int i = 3; i < argc-1; i++){
    if(checkRotorConfig(argv[i]) != 0){
      return checkRotorConfig(argv[i]);
    }
  }
  if(checkRotorPositionsConfig(argv[argc - 1]) != 0){
    return checkRotorPositionsConfig(argv[argc - 1]);
  }

  plugboard.loadPlugboard(argv[1]);
  reflector.loadReflector(argv[2]);

  int argc_temp = argc - 2;
  // Load the rotor config in each rotor
  for (int i = 0; i < number_rotors; i++){
    //cout << endl << "Loading config for rotor " << i << " with argc " << argc_temp << endl;
    rotor_array[i].loadRotor(argv[argc_temp]);
    argc_temp--;
  }

  // Load the rotor poitions in each rotor
  for (int i = number_rotors-1; i >= 0; i--){
    rotor_array[i].loadRotorPosition(argv[argc - 1], i, number_rotors);
  }

  return NO_ERROR;
}

int Enigma::checkPlugboardConfig(const char* filename){

  //cout << "Checking plugboard config..." << endl;

  ifstream input;
  input.open(filename);

  int input_int;
  int count = 0;
  int temp_storage[ALPHABET_SIZE];

  input >> input_int;

  while (!input.eof()){
    temp_storage[count] = input_int;
    count++;
    input >> input_int;

    //Checking for NON_NUMERIC_CHARACTER
    if (!input.good() && !input.eof()){
      cerr << "You provided a non-numeric plugboard parameter! (4)" << endl;
      return NON_NUMERIC_CHARACTER;
    }
	}

  input.close();

  for(int i = 0; i < count; i++){
    //cout << temp_storage[i] << endl; //Print array
  }

  //Checking for IMPOSSIBLE_PLUGBOARD_CONFIGURATION
  for(int i = 0; i < count; i++){
    for(int j = i+1; j < count; j++){
      if (temp_storage[i] == temp_storage[j]){
        cerr << "You provided an invalid plugboard configuration! (5)" << endl;
        return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }
  }

  //Checking for INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
  if (count%2 != 0){
    cerr << "You provided an incorrect number of plugboard parameters! (6)" << endl;
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }

  //Checking for INVALID_INDEX
  for(int i = 0; i < count; i++){
    if(temp_storage[i] < 0 || temp_storage[i] > 25){
      cerr << "You provided an invalid index! (3)" << endl;
      return INVALID_INDEX;
    }
  }

  //cout << "Plugboard config correct!" << endl;
  return NO_ERROR;

}

int Enigma::checkReflectorConfig(const char* filename){

  //cout << "Checking reflector config..." << endl;

  ifstream input;
  input.open(filename);

  int input_int;
  int count = 0;
  int temp_storage[ALPHABET_SIZE];

  input >> input_int;

  while (!input.eof()){
    temp_storage[count] = input_int;
    count++;
    input >> input_int;

    //Checking for NON_NUMERIC_CHARACTER
    if (!input.good() && !input.eof()){
      cerr << "You provided a non-numeric reflector parameter! (4)" << endl;
      return NON_NUMERIC_CHARACTER;
    }
	}

  input.close();

  for(int i = 0; i < ALPHABET_SIZE; i++){
    //cout << temp_storage[i] << endl; //Print array
  }

  //Checking for INVALID_REFLECTOR_MAPPING
  for(int i = 0; i < count; i++){
    for(int j = i+1; j < count; j++){
      if (temp_storage[i] == temp_storage[j]){
        cerr << "You provided an invalid reflector configuration! (9)" << endl;
        return INVALID_REFLECTOR_MAPPING;
      }
    }
  }

  //Checking for INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS
  if (count/2 != 13){
    cerr << "You provided an incorrect number of reflector parameter pairs! (10)" << endl;
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }

  //Checking for INVALID_INDEX
  for(int i = 0; i < count; i++){
    if(temp_storage[i] < 0 || temp_storage[i] > 25){
      cerr << "You provided an invalid index! (3)" << endl;
      return INVALID_INDEX;
    }
  }

  //cout << "Reflector config correct!" << endl;
  return NO_ERROR;

}

int Enigma::checkRotorPositionsConfig(const char* filename){

  //cout << "Checking rotor positions config..." << endl;

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

  //cout << "Rotor positions config correct!" << endl;
  input.close();
  return NO_ERROR;

}

int Enigma::checkRotorConfig(const char* filename){

  //cout << "Checking rotor config..." << endl;

  ifstream input;
  input.open(filename);

  int input_int;
  int count = 0;
  int temp_storage[ROTOR_MAP_SIZE + MAX_NOTCHES];

  input >> input_int;

  while (!input.eof()){
    temp_storage[count] = input_int;
    count++;
    input >> input_int;

    //Checking for NON_NUMERIC_CHARACTER
    if (!input.good() && !input.eof()){
      cerr << "You provided a non-numeric rotor parameter! (4)" << endl;
      return NON_NUMERIC_CHARACTER;
    }
	}

  input.close();

  for(int i = 0; i < count; i++){
    //cout << temp_storage[i] << endl; //Print array
  }

  //Checking for INVALID_ROTOR_MAPPING
  for(int i = 0; i < ROTOR_MAP_SIZE; i++){
    for(int j = i+1; j < ROTOR_MAP_SIZE; j++){
      if (temp_storage[i] == temp_storage[j]){
        cerr << "You provided an invalid rotor mapping! (7)" << endl;
        return INVALID_ROTOR_MAPPING;
      }
    }
  }

  //Checking for INVALID_INDEX
  for(int i = 0; i < count; i++){
    if(temp_storage[i] < 0 || temp_storage[i] > 25){
      cerr << "You provided an invalid index! (3)" << endl;
      return INVALID_INDEX;
    }
  }

  //cout << "Rotor config correct!" << endl;
  return NO_ERROR;
}
