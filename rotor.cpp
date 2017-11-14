#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "rotor.h"

using namespace std;


char Rotor::encodeChar(char c){

  cout << endl << "Rotation: " << rotation << endl;
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

int Rotor::loadRotorPosition(const char* filename, int rotor_id, int number_rotors){

  cout << endl << "Loading rotor positions for rotor " << rotor_id << "..."<< endl;

  ifstream input;
  input.open(filename);
  int input_int, counter;
  counter = 0;
  input >> input_int;

  for (int i = number_rotors-1; !input.eof(); i--){
    if (i == rotor_id){
      rotation = input_int;
    }
    input >> input_int;
    counter ++;
  }

if (counter < number_rotors){
  cerr << "Not enough starting positions specified! (8)" << endl;
  //exit(NO_ROTOR_STARTING_POSITION);
  return NO_ROTOR_STARTING_POSITION;
}

  input.close();

  return NO_ERROR;

}

int Rotor::checkRotorConfig(const char* filename){

  cout << "Checking rotor config..." << endl;

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
    cout << temp_storage[i] << endl; //Print array
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

  cout << "Rotor config correct!" << endl;

  return NO_ERROR;

}

int Rotor::checkRotorPositionsConfig(const char* filename){

  cout << "Checking rotor positions config..." << endl;

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
    cout << temp_storage[i] << endl; //Print array
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

  cout << "Rotor positions config correct!" << endl;

  return NO_ERROR;

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
