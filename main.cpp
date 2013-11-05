#include <fstream>
#include <iostream>
#include <vector>
#include "mat.hpp"
#include "vec2.hpp"
#include "dp_close.hpp"
#include "dp_open.hpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

typedef vec2<double> v2t;
typedef mat<double> mt;

int main(int argc, char** argv)
{
//	const size_t n = 7;
//	const size_t m = 3;
//	const double ptsArr[2 * n] = {
//			1, 3, 5, 6, 7, 8, 8,
//			1, 1, 2, 3, 4, 6, 8 };

//	const size_t n = 12;
//	const size_t m = 5;
//	const double ptsArr[2 * n] = {
//			1, 2, 4, 6, 8, 9, 9, 8, 6, 4, 2, 1,
//			4, 2, 1, 1, 2, 4, 6, 8, 9, 9, 8, 6 };

//	const size_t n = 8;
//	const size_t m = 4;
//	const double ptsArr[2 * n] = {
//			1, 2, 3, 4, 4, 3, 2, 1,
//			2, 1, 1, 2, 3, 4, 4, 3 };

//	// build vector of points
//	vector<v2t> pts(n);
//	for (size_t i = 0; i < n; ++i)
//	{
//		pts[i] = v2t(ptsArr[i], ptsArr[n + i]);
//	}

	// load point from file;
	vector<v2t> pts;
	ifstream in("../out/pts.txt");
	while (!in.eof())
	{
		double x, y;
		in >> x >> y;
		pts.push_back(v2t(x, y));
	}
	const size_t m = 14;

	// run polygonal approximation
//	vector<size_t> ind = dp_open(pts, m);
	vector<size_t> ind = dp_close(pts, m);

	return 0;
}
