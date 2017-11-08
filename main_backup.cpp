#include <iostream>
#include <fstream>
#include <cstdlib>
#include "enigma.h"
#include "plugboard.h"
#include "errors.h"
#include "helper.h"

using namespace std;


int main(int argc, char** argv){

  //int numRotors = argc - 3;

  // Check for INSUFFICIENT_NUMBER_OF_PARAMETERS
  if(argc == 1) {
    cout << "You provided an insufficient number of parameters! (1)" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    exit(1);
	}

  /*Read in a string to encrypt/decrypt
  string input = get_raw_text();
  cout << input;*/

  //Plugboard* plug1 = new Plugboard;
  Plugboard plug1;
  Enigma enig;

  string test_message = "HALLO BIBI";
  string encoded_message = "";

  cout << endl << "Test Input: " << endl << test_message << endl;

  if (plug1.checkPlugboardConfig(argv[1]) == NO_ERROR){

    plug1.loadPlugboard(argv[1]);
    test_message = plug1.runPlugboard(test_message);
    cout << endl << test_message << endl;

  }

  /*for(int i=0; i<test_message.length(); i++){
    encoded_message += rotorsystem1.runRotors(message.at(i));
  }

  encoded_message = plug1.runPlugboard(encoded_message);*/

  cout << endl  << "End of program." << endl;

  return NO_ERROR;

}

/*string get_raw_text() {
	string raw_text, line;
	while(std::cin >> line) {
		raw_text.append(line);
	}

	return raw_text;
}*/
