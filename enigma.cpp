#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "enigma.h"

using namespace std;

Enigma::Enigma(int argc, char** argv): number_rotors(0), rotor_array(NULL) {

  if (argc >= 5){ //At least one rotor
    number_rotors = argc - 4;

    //Creating dynamic array for the rotors
    rotor_array = new Rotor[number_rotors];
  }
}

Enigma::~Enigma(){
  delete [] rotor_array; //Free memory
}

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

  c = plugboard.runPlugboard(c); // 1. run of plugboard

  if (number_rotors != 0) //Forward rotor encryption
    turnRotors();
    c = runRotors(c);

	c = reflector.runReflector(c); // Reflector encryption

  if (number_rotors != 0) // Backwards rotor encryption
    c = runRotorsBack(c);

  c = plugboard.runPlugboard(c); // 2. run of plugboard

  return c + 65; //Convert from 0 based alphabet to ASCII
}

int Enigma::config(int argc, char** argv){

  //Checking all files
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

  //If error checks do not fail, load the configurations
  plugboard.loadPlugboard(argv[1]);
  reflector.loadReflector(argv[2]);
  int argc_temp = argc - 2;
  for (int i = 0; i < number_rotors; i++){
    rotor_array[i].loadRotor(argv[argc_temp]);
    argc_temp--;
  }
  for (int i = number_rotors-1; i >= 0; i--){
    rotor_array[i].loadRotorPosition(argv[argc - 1], i, number_rotors);
  }

  return NO_ERROR;
}

int Enigma::checkPlugboardConfig(const char* filename){

  ifstream input;
  input.open(filename);
  if (input.fail()){
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  int input_int;
  int count = 0;
  int temp_storage[ALPHABET_SIZE];

  input >> input_int;

  while (!input.eof()){

    temp_storage[count] = input_int;

    //Checking for NON_NUMERIC_CHARACTER
    if (!input.good() && !input.eof()){
      input.close();
      return NON_NUMERIC_CHARACTER_PLUGBOARD;
    }

    //Checking for IMPOSSIBLE_PLUGBOARD_CONFIGURATION
    if (count > 0){
      for(int i = 0; i < count; i++){
        if (temp_storage[i] == input_int){
          input.close();
          return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
        }
      }
    }

    //Checking for INVALID_INDEX
    if(input_int < 0 || input_int > 25){
      input.close();
      return INVALID_INDEX;
    }

    count++;
    input >> input_int;
	}

  input.close();

  //Checking for INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS_ODD
  if (count > 26 && count%2 != 0){
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS_ODD;
  }

  //Checking for INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
  if (count%2 != 0){
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }

  return NO_ERROR;
}

int Enigma::checkReflectorConfig(const char* filename){

  ifstream input;
  input.open(filename);
  if (input.fail()){
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  int input_int;
  int count = 0;
  int temp_storage[ALPHABET_SIZE];

  input >> input_int;

  while (!input.eof()){

    temp_storage[count] = input_int;

    //Checking for NON_NUMERIC_CHARACTER
    if (!input.good() && !input.eof()){
      input.close();
      return NON_NUMERIC_CHARACTER_REFLECTOR;
    }

    //Checking for INVALID_REFLECTOR_MAPPING
    if (count > 0){
      for(int i = 0; i < count; i++){
        if (temp_storage[i] == input_int){
          input.close();
          return INVALID_REFLECTOR_MAPPING;
        }
      }
    }

    //Checking for INVALID_INDEX
    if(input_int < 0 || input_int > 25){
      input.close();
      return INVALID_INDEX;
    }

    count++;
    input >> input_int;
	}

  input.close();

  //Checking for INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS_ODD
  if (static_cast<double>(count)/2 != 13 && count%2 != 0){
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS_ODD;
  }

  //Checking for INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS
  if (count/2 != 13){
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }

  return NO_ERROR;
}

int Enigma::checkRotorPositionsConfig(const char* filename){

  ifstream input;
  input.open(filename);
  if (input.fail()){
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  int input_int;
  int count = 0;

  input >> input_int;

  while (!input.eof()){

    //Checking for NON_NUMERIC_CHARACTER
    if (!input.good() && !input.eof()){
      input.close();
      return NON_NUMERIC_CHARACTER_POSITIONS;
    }

    //Checking for INVALID_INDEX
    if(input_int < 0 || input_int > 25){
      input.close();
      return INVALID_INDEX;
    }

    count++;
    input >> input_int;

  }

  //Checking for NO_ROTOR_STARTING_POSITION
  if (count < number_rotors){
    return NO_ROTOR_STARTING_POSITION;
  }

  input.close();
  return NO_ERROR;
}

int Enigma::checkRotorConfig(const char* filename){

  ifstream input;
  input.open(filename);
  if (input.fail()){
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  int input_int;
  int count = 0;
  int temp_storage[ROTOR_MAP_SIZE + MAX_NOTCHES];

  input >> input_int;

  while (!input.eof()){

    temp_storage[count] = input_int;

    //Checking for NON_NUMERIC_CHARACTER
    if (!input.good() && !input.eof()){
      input.close();
      return NON_NUMERIC_CHARACTER_ROTOR;
    }

    //Checking for INVALID_ROTOR_MAPPING
    if (count > 0 && count < ALPHABET_SIZE){
      for(int i = 0; i < count; i++){
        if (temp_storage[i] == input_int){
          input.close();
          return INVALID_ROTOR_MAPPING;
        }
      }
    }

    //Checking for INVALID_INDEX
    if(input_int < 0 || input_int > 25){
      input.close();
      return INVALID_INDEX;
    }

    if (count > (ROTOR_MAP_SIZE + MAX_NOTCHES)){
      input.close();
      return INVALID_ROTOR_MAPPING;
    }

    count++;
    input >> input_int;
	}

  input.close();

  if (count < ROTOR_MAP_SIZE){
    return INVALID_ROTOR_MAPPING_NOT_ENOUGH_PARAMETERS;
  }

  return NO_ERROR;
}

int Enigma::printErrorMessage(int code){

  switch(code) {

  	case INVALID_INDEX:
      cerr << "Provided an invalid index (< 0 or >25)" << endl;
      return INVALID_INDEX;

  	case IMPOSSIBLE_PLUGBOARD_CONFIGURATION:
      cerr << "Invalid plugboard configuration" << endl;
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;

  	case INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS:
      cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;

    case INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS_ODD:
      cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;

  	case INVALID_ROTOR_MAPPING:
      cerr << "Invalid mapping of input" << endl;
      return INVALID_ROTOR_MAPPING;

  	case NO_ROTOR_STARTING_POSITION:
      cerr << "No starting position for rotor 0 in rotor position file: rotor.pos" << endl;
      return NO_ROTOR_STARTING_POSITION;

    case INVALID_REFLECTOR_MAPPING:
      cerr << "Invalid mapping of reflector" << endl;
      return INVALID_REFLECTOR_MAPPING;

  	case INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS:
      cerr << "Insufficient number of mappings in reflector file: reflector.rf" << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;

    case INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS_ODD:
      cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;

  	case ERROR_OPENING_CONFIGURATION_FILE:
      cerr << "Error while opening configuration file" << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;

    case NON_NUMERIC_CHARACTER_PLUGBOARD:
      cerr << "Non-numeric character in plugboard file plugboard.pb" << endl;
      return NON_NUMERIC_CHARACTER;

    case NON_NUMERIC_CHARACTER_REFLECTOR:
      cerr << "Non-numeric character in reflector file reflector.rf" << endl;
      return NON_NUMERIC_CHARACTER;

    case NON_NUMERIC_CHARACTER_ROTOR:
      cerr << "Non-numeric character for mapping in rotor file rotor.rot" << endl;
      return NON_NUMERIC_CHARACTER;

    case NON_NUMERIC_CHARACTER_POSITIONS:
      cerr << "Non-numeric character in rotor positions file rotor.pos" << endl;
      return NON_NUMERIC_CHARACTER;

    case INVALID_ROTOR_MAPPING_NOT_ENOUGH_PARAMETERS:
      cerr << "Not all inputs mapped in rotor file: rotor.rot" << endl;
      return INVALID_ROTOR_MAPPING;
  	}

    return NO_ERROR;
}
