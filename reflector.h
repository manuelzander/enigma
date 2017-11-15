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
  Reflector(){ //Constructor
    for (int i = 0; i < ALPHABET_SIZE; i++){
      reflectorconfig[i] = 0;
    }
  }

  void loadReflector(const char* filename);
  char runReflector(char c);
};

#endif
