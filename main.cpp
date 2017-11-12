#include <iostream>
#include <fstream>
#include <cstdlib>
#include "enigma.h"
#include "plugboard.h"
#include "errors.h"
#include "helper.h"

using namespace std;

string get_input_message();

int main(int argc, char** argv){

  // Check for INSUFFICIENT_NUMBER_OF_PARAMETERS
  if(argc < 3) {
    cout << "You provided an insufficient number of parameters! (1)" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    exit(1);
	}

  //Read in a string to encode
  //string input = get_input_message();
  //cout << input;

  string test_message = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

  string encoded_message = "";

  cout << endl << "Test Input: " << test_message << endl;

  Enigma enig (argc, argv);

  cout << endl << "Test Output: " << enig.encode(test_message);

  cout << endl << endl  << "END of main function." << endl;

  return NO_ERROR;

}

string get_input_message() {
	string input;

  char c;

  for(int i = 0; i < MAX_MESSAGE_LEGTH; i++){
    cin >> c;
    if(c >= 'A' && c <= 'Z'){
      input += c;
    }

	}

	return input;
}
