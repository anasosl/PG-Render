#ifndef BEZIERH
#define BEZIERH

#define ll long long int

#include "point3.h"
#include "vec3.h"
#include <vector>
#include <tuple>
#include <math.h>
#include <map>
#include "mesh.h"

ll factorial(int n){
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

class Bezier : public geometricObj {
    public:
    vector<vector<vec3>> control_points;
    vector<Triangle> triangles;
    map<tuple<double,double,double>, pair<double,double>> st;

    pair<double, double> getST(point3 vert) {
        return st[{vert.x(), vert.y(), vert.z()}];
    }

    Bezier(vector<vector<vec3>> points, const vec3 &color, double Kd, double Ks, double Ka, double Kr, double Kt, double N)
        : geometricObj(color, Kd, Ks, Ka, Kr, Kt, N) {
            control_points = points;
        }

    tuple<double, vec3, vec3> intersect(const ray &r, vector<vector<vec3>> &texture)
    {
        auto [t, a] = intersectTriangle(r);
        vec3 normal = a.intNormal(r);
        vec3 color = vec3(0,0,0);

        if (t != 10000000) {
            color = getColor(a, r.point_at(t), texture);
        }

        

        return {t, normal, color};
        
    }
    
    pair<double,Triangle> intersectTriangle(const ray &r) {
        double t;
        double minT = 10000000;
        point3 A = point3(0,0,0);
        Triangle T = Triangle(A,A,A);
        
        for (auto a : triangles)
        {
            t = a.intersect(r);
            // t negativo significa que não tem interseção ou ela ocorreu atrás da câmera
            if(t > 0 && t < minT){
                minT = t;
                T = a;
            }
        }

        return {minT, T};
    }

    vec3 getColor (Triangle a, point3 P, vector<vector<vec3>> &texture) {
        point3 A = a.A;
        point3 B = a.B;
        point3 C = a.C;

        /*
        vec3 PAB = cross(A - P, B - P);
        vec3 PAC = cross(C - P, A - P);
        vec3 PBC = cross(C - P, B - P);

        vec3 ABC = cross(C - B, A - B);

        double alpha = PAB.length()/ABC.length();
        double beta = PAC.length()/ABC.length();
        double gamma = PBC.length()/ABC.length();
        */

        vec3 AB = B - A;
        vec3 AC = C - A;
        vec3 AP = P - A;

        // Produtos cruzados para calcular as áreas dos subtriângulos
        double areaABC = cross(AB, AC).length();
        double areaPBC = cross(B - P, C - P).length();
        double areaPCA = cross(C - P, A - P).length();

        // Coordenadas baricêntricas
        double alpha = areaPBC / areaABC;
        double beta = areaPCA / areaABC;
        double gamma = 1.0 - alpha - beta;

        auto [sa, ta] = getST(A);
        auto [sb, tb] = getST(B);
        auto [sc, tc] = getST(C);

        double s = sa*alpha + sb*beta + sc*gamma;
        double t = ta*alpha + tb*beta + tc*gamma;

        int x = texture.size()*s;
        int y = texture[x].size()*t;

        return texture[x][y];

    }

    double bernstein(int n, int i, double t){
        ll binomial_coef = factorial(n) / (factorial(i)*factorial(n - i));
        double res = binomial_coef * pow(t, i) * (pow(1-t, n-i));
        return res;
    }

    point3 surface_point(double s, double t){
        int rows = control_points.size();
        vec3 point = vec3(0,0,0);
        int columns;
        double bs;
        double bt;

        for(int i=0; i<rows; i++){
            columns = control_points[i].size();
            for(int j=0; j<columns; j++){
                bs = bernstein(rows - 1, i, s);
                bt = bernstein(columns - 1, j, t);
                point = point + bs * bt * control_points[i][j];
            } 
        }

        point3 p = point3(point[0], point[1], point[2]);

        st[{p.x(), p.y(), p.z()}] = {s,t};

        return p;
    }

    void triangulate(double tolerance){

        vector<point3> bezier_points;
        vector<vector<int>> listTriangles;

        for(double s=0; s<=1; s+=tolerance){
            for(double t=0; t<=1; t+=tolerance){
                bezier_points.push_back(surface_point(s,t));
            }
        }

        int n = int(1/tolerance);
        int numberOfPoints = bezier_points.size();

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                listTriangles.push_back({i * (n+1) + j, (i+1) * (n+1) + j, i * (n+1) + j + 1}); 
                listTriangles.push_back({(i+1) * (n+1) + j, (i+1) * (n+1) + j + 1, i * (n+1) + j + 1}); 
            }
        }

        for (int i = 0; i < listTriangles.size(); i++)
        {
            int idxA = listTriangles[i][0];
            int idxB = listTriangles[i][1];
            int idxC = listTriangles[i][2];

            point3 A = bezier_points[idxA];
            point3 B = bezier_points[idxB];
            point3 C = bezier_points[idxC];

            triangles.push_back(Triangle(A, B, C));
        }
    }

    

};

#endif
