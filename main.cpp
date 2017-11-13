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
    cerr << "You provided an insufficient number of parameters! (1)" << endl;
    exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
	}

  //Read in a string to encode
  //string input = get_input_message();

  //Test
  string input = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

  string encoded_message = "";

  cout << endl << "Test Input: " << input << endl;

  Enigma enig (argc, argv);

  cout << endl << "Test Output: " << enig.encode(input);

  cout << endl << endl  << "END of main function." << endl;

  return NO_ERROR;

}

string get_input_message() {
	string input;

  //char c;

  cout << "Please type your message! Only upper case letters are allowed" << endl
        << "white-space characters will be ignored!" << endl;

  /*for(int i = 0; i < MAX_MESSAGE_LEGTH; i++){
    cin >> c;
    if(c >= 'A' && c <= 'Z'){
      input += c;
    }
    else if (!isspace(c)){
      cerr << "You provided an invalid input character! (2)" << endl;
      exit(INVALID_INPUT_CHARACTER);
		}
	}*/

  /*cin >> c;

  while(cin.good()){

    cin >> c;

    if(cin.fail()){
      break;
    }

    if(c >= 'A' && c <= 'Z'){
      input += c;
    }

  }*/

	return input;
}
