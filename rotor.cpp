#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "rotor.h"

using namespace std;


char Rotor::encodeChar(char c){

  c = c + 1;

  return c;

}

char Rotor::encodeCharBack(char c){

  c = c - 1;

  return c;

}

void Rotor::loadRotor(const char* filename){

  //cout << endl << "Loading config..." << endl;

  ifstream input;
  input.open(filename);

  int i = 0;
  int input_int;

  input >> input_int;

  while (!input.eof()){
    rotorconfig[i] = 65 + input_int;
    i++;
    input >> input_int;
	}

  input.close();

}
