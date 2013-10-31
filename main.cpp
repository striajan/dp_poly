#include <iostream>
#include <vector>
#include "mat.hpp"
#include "vec2.hpp"
#include "dp_poly.hpp"

using std::vector;
using std::cout;
using std::endl;

typedef vec2<double> v2t;
typedef mat<double> mt;


int main(int argc, char** argv)
{
//	const size_t m = 3;
//	const size_t n = 7;
//	const double ptsArr[2 * n] = {
//			1, 3, 5, 6, 7, 8, 8,
//			1, 1, 2, 3, 4, 6, 8 };

	const size_t m = 5;
	const size_t n = 12;
	const double ptsArr[2 * n] = {
			1, 2, 4, 6, 8, 9, 9, 8, 6, 4, 2, 1,
			4, 2, 1, 1, 2, 4, 6, 8, 9, 9, 8, 6 };

	// build vector of points
	vector<v2t> pts(n);
	for (size_t i = 0; i < n; ++i) pts[i] = v2t(ptsArr[i], ptsArr[n + i]);

	// run polygonal approximation
	vector<size_t> ind = dp_open(pts, n, m);

	return 0;
}
