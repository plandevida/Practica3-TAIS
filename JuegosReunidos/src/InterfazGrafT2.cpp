/*
 * InterfazGrafT2.cpp
 *
 *  Created on: 22/11/2012
 *      Author: alberto
 */

#include "InterfazGrafT2.h"
#include <sstream>
using namespace std;
#pragma unmanaged


string convertInt(int number) {
   stringstream ss;  // create a stringstream
   ss << number;     // add number to the stream
   return ss.str();  // return a string with the contents of the stream
}
#pragma managed

InterfazGrafT2::InterfazGrafT2(int w, int h): window_width(w), window_height(h){}
InterfazGrafT2::~InterfazGrafT2(){}
