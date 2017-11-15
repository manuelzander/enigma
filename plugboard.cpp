#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "plugboard.h"

using namespace std;

char Plugboard::runPlugboard(char c){

  for(int i = 0; i < number_count; i = i+2){
    if(plugboardconfig[i] == c){
      c = plugboardconfig[i+1];
    }
    else if(plugboardconfig[i+1] == c){
      c = plugboardconfig[i];
    }
  }

  return c;

}

void Plugboard::loadPlugboard(const char* filename){

  cout << endl << "Loading plugboard config..." << endl;

  ifstream input;
  input.open(filename);

  int input_int;

  input >> input_int;

  while (!input.eof()){
    plugboardconfig[number_count] = input_int;
    number_count++;
    input >> input_int;
	}

  input.close();

}

int Plugboard::checkPlugboardConfig(const char* filename){

  cout << "Checking plugboard config..." << endl;

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
    cout << temp_storage[i] << endl; //Print array
  }

  //Checking for IMPOSSIBLE_PLUGBOARD_CONFIGURATION
  for(int i = 0; i < count; i++){
    for(int j = i+1; j < count-1; j++){
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

  cout << "Plugboard config correct!" << endl;
  return NO_ERROR;

}
