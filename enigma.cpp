#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "enigma.h"

using namespace std;

char Enigma::runRotors(char c){

  /*for(int i = 0; i < numRotors; i++){
    c = rotors[numRotors - i].encodeChar(c);
    }
  }
  */

  c = rotor.encodeChar(c);

  return c;
}

char Enigma::runRotorsBack(char c){

  //Do some fancy stuff

  c = rotor.encodeCharBack(c);

  return c;
}

char Enigma::runRotorProcess(char c){

  // Forward rotor encryption
  if (numRotor != 0)
    c = runRotors(c);

  // Reflector encryption
	//c = reflector.runReflector(c);

  // Backwards rotor encryption
	if (numRotor != 0)
    c = runRotorsBack(c);

  return c;
}

string Enigma::encode(string message){

  cout << endl << "Number of rotors: " << numRotor << endl;
  string encoded_message = "";

  // 1. run of plugboard
  cout << "Plugboard1-Test before: " << message << endl;
  message = plugboard.runPlugboard(message);
  cout << "Plugboard1-Test after: " << message << endl << endl;

  // Run the rotor process & reflector
  cout << "Rotor-Test before: " << message << endl;

  for(int i=0; i<message.length(); i++){
    encoded_message += runRotorProcess(message.at(i));
  }

  cout << "Rotor-Test after: " << encoded_message << endl << endl;

  // 2. run of plugboard
  cout << "Plugboard2-Test before: " << encoded_message << endl;
  encoded_message = plugboard.runPlugboard(encoded_message);
  cout << "Plugboard2-Test after: " << encoded_message << endl << endl;

  return encoded_message;

}
