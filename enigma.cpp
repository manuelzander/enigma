#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "enigma.h"

using namespace std;

string Enigma::encode(string message){

  cout << endl << "Number of rotors: " << numRotors << endl; 

  // 1. run of plugboard
  message = plugboard.runPlugboard(message);

  // Run the rotors
  if (numRotors != 0){
  message = rotors.runRotors(rotors, message);
  }

  // REFLECTOR PLACEHOLDER

  // Run the rotors reverse
  if (numRotors != 0){
  message = rotors.runbackRotors(rotors, message);
  }

  // 2. run of plugboard
  //message = plugboard.runPlugboard(message);

  return message;

}
