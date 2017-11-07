#include <iostream>
#include <fstream>
#include <cstdlib>
#include "errors.h"
#include "helper.h"
#include "rotors.h"

using namespace std;

string Rotors::runRotors(Rotors rotors, string beforerotors){

  cout << beforerotors << endl;

  string afterrotors = "";

  for(int i=0; i<beforerotors.length(); i++){
    afterrotors += rotors.encodeChar(beforerotors.at(i));
  }

  return afterrotors;

}

string Rotors::runbackRotors(Rotors rotors, string beforerotors){

  cout << beforerotors << endl;

  string afterrotors = "";

  for(int i=0; i<beforerotors.length(); i++){
    afterrotors += rotors.encodebackChar(beforerotors.at(i));
  }

  return afterrotors;

}

char Rotors::encodeChar(char c){

  c = c + 1;

  return c;

}

char Rotors::encodebackChar(char c){

  c = c - 1;

  return c;

}
