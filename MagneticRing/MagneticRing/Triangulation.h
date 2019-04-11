#pragma once
#include <vector>
using namespace std;
struct Dot
{
	double x;
	double y;
};

struct triang
{
	Dot dot1;
	Dot dot2;
	Dot dot3;
};

class Triangulation
{
public:
	Triangulation();
	~Triangulation();
	double RandDots(double a, double b);
	void KoordCenter(Dot dot1, Dot dot2, Dot dot3, Dot &centrDots);
	double RadiusCircle(Dot centrDots, Dot dot);

	vector<triang> treugTriang;
	vector<triang> TrianglBust(vector<Dot> dots);
};

