#include <iostream>
#include <fstream>
#include <cstdlib>
#include "enigma.h"
#include "plugboard.h"
#include "errors.h"
#include "helper.h"

using namespace std;

int main(int argc, char** argv){

  char c;

  if(argc < 3) {
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
	}

  Enigma enig (argc, argv);

  if (enig.config(argc, argv) != 0){
    return enig.printErrorMessage(enig.config(argc, argv));
  }

  while(cin >> ws >> c){
    if(c < 'A' || c > 'Z'){
      cerr << c << " is not a valid input character (input characters must be upper case letters A-Z)!";
      return INVALID_INPUT_CHARACTER;
    }
    cout << enig.encode(c);
  }

  return NO_ERROR;

}
