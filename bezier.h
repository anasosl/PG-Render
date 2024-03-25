#ifndef BEZIERH
#define BEZIERH

#define ll long long int

#include "point3.h"
#include "vec3.h"
#include <vector>
#include <tuple>
#include <math.h>
#include "mesh.h"


ll factorial(int n){
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

class Bezier{
    public:
    vector<vector<vec3>> control_points;

    Bezier(){

    }

    ll bernstein(int n, int i, int t){
        ll binomial_coef = factorial(n) / (factorial(i)*factorial(n - i));
        return binomial_coef * pow(t, i) * (pow(1-t, n-i));
    }

    point3 surface_point(int s, int t){
        int rows = control_points.size();
        vec3 point = vec3(0,0,0);
        int columns;
        ll bs;
        ll bt;

        for(int i=0; i<rows; i++){
            columns = control_points[i].size();
            for(int j=0; j<columns; j++){
                bs = bernstein(rows - 1, i, s);
                bt = bernstein(columns - 1, j, t);
                point =  point + bs * bt * control_points[i][j];
            } 
        }

        return point3(point[0], point[1], point[2]);
    }

    Mesh triangulate(double tolerance){

        vector<vector<point3>> bezier_points;
        vector<point3> columns;
        vector<vector<int>> listTriangles;

        for(double s=0; s<=1; s+=tolerance){
            for(double t=0; t<=1; t+=tolerance){
                columns.push_back(surface_point(s,t));
            }
            bezier_points.push_back(columns);
        }

        int n = int(1/tolerance);
        int numberOfPoints = bezier_points.size();

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                listTriangles.push_back({i * (n+1) + j, (i+1) * (n+1) + j, i * (n+1) + j + 1}); 
                listTriangles.push_back({(i+1) * (n+1) + j, (i+1) * (n+1) + j + 1, i * (n+1) + j + 1}); 
            }
        }

        return Mesh(listTriangles.size(), bezier_points.size(), bezier_points, listTriangles, (255,0,0), (0.5, 0.5, 0.2, 0.5, 0.5, 5.0));
    }

};

#endif