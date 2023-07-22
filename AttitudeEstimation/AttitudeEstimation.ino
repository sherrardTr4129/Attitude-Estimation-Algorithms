#include "Nicla_System.h"
#include "Matrix/Matrix.hpp"
#include <vector>

std::vector<int> t(5);

void setup() {
  for(int i = 0; i < t.size(); i++)
  {
    t.at(i) = i;
  }
  Serial.begin(9600);
  Serial.println("here");
}

void loop() {
  for(int i = 0; i < t.size(); i++)
  {
    Serial.println(t[i]);
  }
}
