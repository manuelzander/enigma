#include <iostream>
#include <fstream>
#include "enigma.h"
#include "plugboard.h"
#include "errors.h"
#include "helper.h"

using namespace std;

int main(int argc, char** argv){

  int error_code;
  char c;

  if(argc < 3 || argc == 4) {
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
	}

  Enigma enig (argc, argv);

  //Check files for errors, output errors to cerr if appropriate
  error_code = enig.config(argc, argv);
  if (error_code > 0){
    return enig.printErrorMessage(error_code);
  }

  while(cin >> ws >> c){
    if(c < 'A' || c > 'Z'){
      cerr << c << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
      return INVALID_INPUT_CHARACTER;
    }
    cout << enig.encode(c);
  }

  return NO_ERROR;
}
