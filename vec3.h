#ifndef VECH
#define VECH

#include <math.h>
#include <stdlib.h>
#include <iostream>

//vetor tridimensional 
class Vec3
{
public:
	Vec3() {}
	Vec3(double e0, double e1, double e2)
	{
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}

	//coordenadas dos vetores espaciais
	inline double x() const { return e[0]; }
	inline double y() const { return e[1]; }
	inline double z() const { return e[2]; }

	//coordenadas dos vetores de cor
	inline double r() const { return e[0]; }
	inline double g() const { return e[1]; }
	inline double b() const { return e[2]; }

	inline const Vec3 &operator+() const { return *this; }
	inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
	inline double operator[](int i) const { return e[i]; }
	inline double &operator[](int i) { return e[i]; }

	inline Vec3 &operator+=(const Vec3 &v2);
	inline Vec3 &operator-=(const Vec3 &v2);
	inline Vec3 &operator*=(const Vec3 &v2);
	inline Vec3 &operator/=(const Vec3 &v2);
	inline Vec3 &operator*=(const double t);

	inline Vec3 &operator/=(const double t) { return *this *= 1 / t; }

	inline double length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	inline double length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
	inline void make_unit_vector();

	double e[3];
};

//cin >> >> - recebe os tres valores do vetor
inline std::istream &operator>>(std::istream &is, Vec3 &t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

//cout << << - imprime todos os valores do vetor
inline std::ostream &operator<<(std::ostream &os, Vec3 &t)
{
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

inline void Vec3::make_unit_vector()
{
	double k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}
inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}
inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}
inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}
inline Vec3 operator*(double t, const Vec3 &v)
{
	return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
inline Vec3 operator*(const Vec3 &v, double t)
{
	return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
inline Vec3 operator/(double t, const Vec3 &v)
{
	return Vec3(t / v.e[0], t / v.e[1], t / v.e[2]);
}
inline Vec3 operator/(const Vec3 &v, double t)
{
	return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline double dot(const Vec3 &v1, const Vec3 &v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2[1],
				-(v1.e[0] * v2.e[2] - v1.e[2] * v2[0]),
				v1.e[0] * v2.e[1] - v1.e[1] * v2[0]);
}

inline Vec3 &Vec3::operator+=(const Vec3 &v)
{
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}
inline Vec3 &Vec3::operator-=(const Vec3 &v)
{
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}
inline Vec3 &Vec3::operator*=(const Vec3 &v)
{
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}
inline Vec3 &Vec3::operator/=(const Vec3 &v)
{
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}
inline Vec3 &Vec3::operator*=(const double t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

inline Vec3 unit_vector(Vec3 v)
{
	return v / v.length();
}

Vec3 reflect(const Vec3 &v, const Vec3 &n)
{
	return v - 2 * dot(v, n) * n;
}

bool refract(const Vec3 &v, const Vec3 &n, double ni_over_nt, Vec3 &refracted)
{
	Vec3 uv = unit_vector(v);
	double dt = dot(uv, n);
	double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant > 0)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	return false;
}

double schlick(double cosine, double ref_idx)
{
	double r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

#endif