#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <iostream>
#include <string>
#include "helper.h"

using namespace std;

class Reflector {
private:
  int reflectorconfig[ALPHABET_SIZE];

public:
	int checkReflectorConfig(const char* filename);
  void loadReflector(const char* filename);
  char runReflector(char c);
};

#endif
