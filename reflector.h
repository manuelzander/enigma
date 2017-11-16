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
  Reflector();
  void loadReflector(const char* filename);
  char runReflector(char c);
};

#endif
