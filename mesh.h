#ifndef MESHH
#define MESHH

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector> 

#include "geometricObj.h"

using namespace std;

/*
Input:
    número de triângulos 
    número de vértices 
    lista com triplas dos vértices
    Cor RGB normalizada [0,1]

lista com normais de triângulos
lista com normais dos vértices
*/

class Mesh : public geometricObj
{
public:
    Mesh(int num_tri,  int num_vert, vector<point3> list_vert, const vec3 &color)
        : geometricObj(color) {}
};

#endif