#ifndef POINTH
#define POINTH

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "vec3.h"

class Point3 {
public:
	Point3() {}
	Point3(double e0, double e1, double e2) {e[0]=e0;e[1]=e1;e[2]=e2;}
	
	//dimensoes do ponto
	inline double x() const {return e[0];}
	inline double y() const {return e[1];}
	inline double z() const {return e[2];}
	
    inline const Point3 &operator+() const { return *this; }
    inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
	inline double operator[](int i) const {return e[i];}
	inline double& operator[](int i) {return e[i];}

	double e[3];
};

//cin >> >> - recebe todas as dimensoes do ponto
inline std::istream& operator>>(std::istream &is, Point3 &t) {
 is >> t.e[0] >> t.e[1] >> t.e[2];
 return is;
}

//cout << << - imprime todas as dimensoes do ponto
inline std::ostream& operator<<(std::ostream &os, Point3 &t) {
 os << t.e[0] << " " << t.e[1] << " " << t.e[2];
 return os;
}

inline Point3 operator+(const Point3 &p, const Vec3 &v)
{
	return Point3(p.e[0] + v.e[0], p.e[1] + v.e[1], p.e[2] + v.e[2]);
}
inline Vec3 operator-(const Point3 &p1, const Point3 &p2)
{
	return Vec3(p1.e[0] - p2.e[0], p1.e[1] - p2.e[1], p1.e[2] - p2.e[2]);
}

#endif