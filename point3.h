#ifndef POINTH
#define POINTH

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "vec3.h"

using namespace std;

class point3 {
public:
	point3() {}
	point3(double e0, double e1, double e2) {e[0]=e0;e[1]=e1;e[2]=e2;}
	
	inline double x() const {return e[0];}
	inline double y() const {return e[1];}
	inline double z() const {return e[2];}
	
    inline const point3 &operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	inline double operator[](int i) const {return e[i];}
	inline double& operator[](int i) {return e[i];}

	double e[3];
};

inline std::istream& operator>>(std::istream &is, point3 &t) {
 is >> t.e[0] >> t.e[1] >> t.e[2];
 return is;
}

inline std::ostream& operator<<(std::ostream &os, point3 &t) {
 os << t.e[0] << " " << t.e[1] << " " << t.e[2];
 return os;
}

inline point3 operator+(const point3 &p, const vec3 &v)
{
	return point3(p.e[0] + v.e[0], p.e[1] + v.e[1], p.e[2] + v.e[2]);
}
inline vec3 operator-(const point3 &p1, const point3 &p2)
{
	return vec3(p1.e[0] - p2.e[0], p1.e[1] - p2.e[1], p1.e[2] - p2.e[2]);
}

#endif