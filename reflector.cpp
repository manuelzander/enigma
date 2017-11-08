#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "reflector.h"

using namespace std;

char Reflector::runReflector(char c){

  /*string afterreflector = "";

  for(int i = 0; i < beforereflector.length(); i++){
      for(int j = 0; j < ALPHABET_SIZE; j = j+2){
          if(reflectorconfig[j] == beforereflector.at(i)){
              afterreflector += reflectorconfig[j+1];
          } else if(reflectorconfig[j+1] == beforereflector.at(i)){
              afterreflector += reflectorconfig[j];
          }
      }
  }

  return afterreflector;*/
}

void Reflector::loadReflector(const char* filename){

  cout << endl << "Loading reflector config..." << endl;

  ifstream input;
  input.open(filename);

  int i = 0;
  int input_int;

  input >> input_int;

  while (!input.eof()){
    reflectorconfig[i] = 65 + input_int;
    i++;
    input >> input_int;
	}

  input.close();

}
