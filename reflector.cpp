#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "reflector.h"

using namespace std;

char Reflector::runReflector(char c){

  for(int i = 0; i < ALPHABET_SIZE; i = i+2){
    if(reflectorconfig[i] == c){
      c = reflectorconfig[i+1];
    }
    else if(reflectorconfig[i+1] == c){
      c = reflectorconfig[i];
    }
  }

  return c;
}

void Reflector::loadReflector(const char* filename){

  cout << endl << "Loading reflector config..." << endl;

  ifstream input;
  input.open(filename);

  int i = 0;
  int input_int;

  input >> input_int;

  while (!input.eof()){
    reflectorconfig[i] = input_int;
    i++;
    input >> input_int;
	}

  input.close();
}

int Reflector::checkReflectorConfig(const char* filename){

  cout << "Checking reflector config..." << endl;

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
    cout << temp_storage[i] << endl; //Print array
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

  cout << "Reflector config correct!" << endl;
  return NO_ERROR;

}
