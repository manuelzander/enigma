#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "reflector.h"

using namespace std;

Reflector::Reflector(){
  for (int i = 0; i < ALPHABET_SIZE; i++){
    reflectorconfig[i] = 0;
  }
}

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
