#include <iostream>
#include <fstream>
#include <cstdlib>
#include "enigma.h"
#include "plugboard.h"
#include "errors.h"
#include "helper.h"

using namespace std;

int main(int argc, char** argv){

  // Check for INSUFFICIENT_NUMBER_OF_PARAMETERS
  if(argc < 3) {
    cerr << "You provided an insufficient number of parameters! (1)" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
	}

  cout  << endl << "Please type your message:" << endl
        << "Only upper case letters are allowed and" << endl
        << "white-space characters will be ignored!" << endl;

  string input;
  //int counter = 0;
  //char c;

  /*while((cin >> ws >> c) && counter < MAX_MESSAGE_LEGTH){
    if(c < 'A' || c > 'Z'){
      cerr << "You input an invalid input character! (2)" << endl;
      exit(INVALID_INPUT_CHARACTER);
      return INVALID_INPUT_CHARACTER;
    } else if(c >= 'A' && c <= 'Z'){
      input += c;
      counter++;
    }
  }*/

  //input = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
  string encoded_message = "";
  cout << endl << "Test Input: " << input << endl;

  //Create global checking functions
  //Do the checking here, not it in the Constructor for Enigma class
  // If return value x > 0, return x, otherwise create the Enigma machine an run encryption

  Enigma enig (argc, argv);

  /*while((cin >> ws >> c) && counter < MAX_MESSAGE_LEGTH){
    if(c < 'A' || c > 'Z'){
      cerr << "You input an invalid input character! (2)" << endl;
      return INVALID_INPUT_CHARACTER;
    } else if(c >= 'A' && c <= 'Z'){
      cout << endl << enig.encode(c) << endl << endl;
      counter++;
    }
  }*/

  while(cin >> ws >> input){

    for(int i=0; i<input.length(); i++){
      if(input.at(i) < 'A' || input.at(i) > 'Z'){
        cerr << "You input an invalid input character! (2)" << endl;
        return INVALID_INPUT_CHARACTER;
      }
    }

    for(int i=0; i<input.length(); i++){
      encoded_message += enig.encode(input.at(i));
    }

    cout << endl << "Test Output: " << encoded_message << endl << endl << "Another input:" << endl << endl;
    input = "";
    encoded_message = "";
  }

  for(int i=0; i<input.length(); i++){
    encoded_message += enig.encode(input.at(i));
  }

  cout << endl << "Test Output: " << encoded_message;

  cout << endl << endl  << "END of main function." << endl;

  return NO_ERROR;

}
