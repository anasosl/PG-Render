#include "vec3.h"
#include <iostream>

int main(){
    vec3 p = vec3(1,1,1);
    long long int t = 1e11;

    p = p*t;

    std::cout << p;
}