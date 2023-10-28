#ifndef ASSIGNMENT9_PET_HPP
#define ASSIGNMENT9_PET_HPP

#include <string>
#include "dog.cpp"
#include "cat.cpp"

using namespace std;

class pet {
public:
    pet();
    pet(string name, int weight);
    void SetName(string name) {petName = name;}
    string GetName() {return petName;}
    void SetPrice(int weight) {price = weight}
    int GetPrice();
};



#endif //ASSIGNMENT9_PET_HPP
