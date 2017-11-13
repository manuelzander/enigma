#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "plugboard.h"

using namespace std;

char Plugboard::runPlugboard(char c){

  for(int i = 0; i < ALPHABET_SIZE; i = i+2){
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

  ifstream input;
  input.open(filename);

  int input_int;
  int count = 0;

  input >> input_int;

  while (!input.eof()){

    if(input_int < 0 || input_int > 25){
      cerr << "You provided an invalid index! (3)" << endl;
      input.close();
      exit(INVALID_INDEX);
    }


    if (!input.good() && !input.eof()){
      cerr << "You provided a non-numeric plugboard parameter! (4)" << endl;
      input.close();
      exit(NON_NUMERIC_CHARACTER);
    }

    count++;

    input >> input_int;

	}

  //Checking for INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
  if (count%2 != 0){
    cout << "You provided an incorrect number of plugboard parameters! (6)" << endl;
    input.close();
    exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
  }

  input.close();

  cout << endl << "Number pairs: " << count/2 << endl;
  cout << "Plugboard config correct!" << endl;

  return NO_ERROR;

}
