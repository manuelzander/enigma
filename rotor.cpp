#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "rotor.h"

using namespace std;


char Rotor::encodeChar(char c){

  //c = c + 1;

  int temp = c - 65;

  c = rotorconfig[temp] + 65;
  return c;

}

char Rotor::encodeCharBack(char c){

  int temp = c - 65;

  for(int i = 0; i < 26; i++){
    if(rotorconfig[i] == temp){
      return i + 65;
    }
  }

  return c;

}

void Rotor::loadRotor(const char* filename){

  ifstream input;
  input.open(filename);

  int i = 0;
  int input_int;

  input >> input_int;

  while (!input.eof()){

    rotorconfig[i] = input_int;
    i++;
    input >> input_int;
	}

  for(int i = 0; i < ROTOR_MAP_SIZE; i++){

    cout << endl << rotorconfig[i] << endl;

  }

  input.close();

}
