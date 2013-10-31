#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include <iostream>

// macro for turning release mode on
//#define NDEBUG

// macros for release mode compilation
#ifdef NDEBUG

#define DCODE(x)
#define DPRINT(x)
#define DPRINTLN(x)

// macros for debug mode compilation
#else

#define DCODE(x) { x }
#define DPRINT(x) { std::cout << x; }
#define DPRINTLN(x) { std::cout << x << std::endl; }

#endif

#endif
