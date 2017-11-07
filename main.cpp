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
    cout << "You provided an insufficient number of parameters! (1)" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    exit(1);
	}

  /*Read in a string to encrypt/decrypt
  string input = get_raw_text();
  cout << input;*/

  Plugboard plugboard1;

  string test_message = "HALLO";
  string encoded_message = "";

  cout << endl << "Test Input: " << test_message << endl;

  if (plugboard1.checkPlugboardConfig(argv[1]) == NO_ERROR){

    //plugboard1.loadPlugboard(argv[1]);

  }

  Rotors rotors1;

  Enigma enig (argc, plugboard1, rotors1);

  cout << endl << "Test Output: " << enig.encode(test_message);

  /*for(int i=0; i<test_message.length(); i++){
    encoded_message += rotorsystem1.runRotors(message.at(i));
  }

  encoded_message = plug1.runPlugboard(encoded_message);*/

  cout << endl << endl  << "END of main function." << endl;

  return NO_ERROR;

}

/*string get_raw_text() {
	string raw_text, line;
	while(std::cin >> line) {
		raw_text.append(line);
	}

	return raw_text;
}*/
