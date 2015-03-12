#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include "dp_close.hpp"
#include "dp_open.hpp"
#include "mat.hpp"
#include "utils.hpp"
#include "vec2.hpp"

using std::array;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

typedef mat<double> mat_t;
typedef vec2<double> vec2_t;

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
//	vector<vec2_t> pts(n);
//	for (size_t i = 0; i < n; ++i) pts[i] = vec2_t(ptsArr[i], ptsArr[n + i]);

	// load point from file;
	vector<vec2_t> pts;
	ifstream in("points.txt");

	double x, y;
	while (in >> x >> y) pts.push_back(vec2_t(x, y));
	const size_t m = 14;

	// run polygonal approximation
//	dp_open<double> dp;
	dp_close<double> dp;

	auto t0 = system_clock::now();
	vector<size_t> ind = dp(pts, m);
	auto t1 = system_clock::now();
	cout << (duration_cast<milliseconds>(t1 - t0)).count() << endl;

	cout << ind << endl;

	return 0;
}
