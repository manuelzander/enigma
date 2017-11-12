#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "enigma.h"

using namespace std;

void Enigma::turnRotors(){

  rotor_array[0].turn();

  for(int i = 0; i < number_rotors; i++) {
		if(rotor_array[i].testForNotch() == true && number_rotors > i+1) {
			rotor_array[i+1].turn();
		}
	}

}

char Enigma::runRotors(char c){

  for(int i = 0; i < number_rotors; i++){

    c = rotor_array[i].encodeChar(c);

  }

  return c;
}

char Enigma::runRotorsBack(char c){

  for(int i = 0; i < number_rotors; i++){
    c = rotor_array[i].encodeCharBack(c);
  }

  return c;
}

char Enigma::runRotorProcess(char c){

  c = c - 65;

  // Forward rotor encryption
  if (number_rotors != 0)
    turnRotors();
    c = this->runRotors(c);

  // Reflector encryption
	c = reflector.runReflector(c);

  // Reverse rotor encryption
	if (number_rotors != 0)
    c = this->runRotorsBack(c);

  return c + 65;
}

string Enigma::encode(string message){

  cout << endl << "Number of rotors: " << number_rotors << endl;
  string encoded_message = "";

  // 1. run of plugboard
  cout << "Plugboard1-Test before: " << message << endl;
  message = plugboard.runPlugboard(message);
  cout << "Plugboard1-Test after: " << message << endl << endl;

  // Run the rotor process & reflector
  cout << "Rotor-Test before: " << message << endl;

  for(int i=0; i<message.length(); i++){
    encoded_message += this->runRotorProcess(message.at(i));
  }

  cout << "Rotor-Test after: " << encoded_message << endl << endl;

  // 2. run of plugboard
  cout << "Plugboard2-Test before: " << encoded_message << endl;
  encoded_message = plugboard.runPlugboard(encoded_message);
  cout << "Plugboard2-Test after: " << encoded_message << endl << endl;

  return encoded_message;

}
