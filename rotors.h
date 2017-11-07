#ifndef ROTORS_H
#define ROTORS_H

#include <iostream>
#include <string>
#include "helper.h"

using namespace std;

class Rotors {
private:


public:
  Rotors(){ //Constructor
  }
	int checkRotorConfig(const char* filename);
  void loadRotors(const char* filename);
  string runRotors(Rotors inputrotors, string input);
  string runbackRotors(Rotors inputrotors, string input);
  char encodeChar(char c);
  char encodebackChar(char c);

};

#endif
