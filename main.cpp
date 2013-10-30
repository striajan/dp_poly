#include <iostream>
#include "vec2.hpp"
#include "dp_poly.hpp"

using std::cout;
using std::endl;

typedef vec2<double> v2t;

int main(int argc, char** argv)
{
//	const v2t u(1, 2);
//	const v2t v(3, 4);
//
//	cout << u << " " << v << endl;
//	cout << u.norm2() << endl;
//	cout << -u << endl;
//	cout << 2 * u << " " << u * 3 << " " << u / 2.0 << endl;
//	cout << u + v << " " << u - v << endl;
//	cout << v2t::dot(u, v) << endl;

	const size_t n = 7;
	const v2t pts[n] = { v2t(1,1), v2t(3,1), v2t(5,2), v2t(6,3), v2t(7,4), v2t(8,6), v2t(8,8) };

//	for (size_t i = 0; i < n; ++i) cout << pts[i] << " ";
//	cout << endl;

//	double dist[n];
//	pts_seg_dist(pts, 1, 5, dist);
//	for (size_t i = 0; i < n; ++i) cout << dist[i] << " ";
//	cout << endl;

	dp_open(pts, n);

	return 0;
}
