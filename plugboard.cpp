#include <iostream>
#include <fstream>
#include "errors.h"
#include "helper.h"
#include "plugboard.h"

using namespace std;

Plugboard::Plugboard(): number_count(0) {
  for (int i = 0; i < ALPHABET_SIZE; i++){
    plugboardconfig[i] = 0;
  }
}

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
