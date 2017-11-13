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

  for(int i=0; i<input.length(); i++){
    encoded_message += enig.encode(input.at(i));
  }

  cout << endl << "Test Output: " << encoded_message;

  cout << endl << endl  << "END of main function." << endl;

  return NO_ERROR;

}

string get_input_message() {

	string input;

  //char c;

  cout  << endl << "Please type your message:" << endl
        << "Only upper case letters are allowed and" << endl
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

  int counter = 0;
  char c;

  while((cin >> ws >> c) && counter < MAX_MESSAGE_LEGTH){

    if(c >= 'A' && c <= 'Z'){
      input += c;
      counter++;
    }

  }

	return input;
}
