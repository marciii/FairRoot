#include "GnuPlot.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

GnuPlot::GnuPlot() {
}

void GnuPlot::write(std::string s1, std::string s2) {
	std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
	gnudatafile << s1 << "\t" << s2 <<std::endl;
	return;
}

GnuPlot::~GnuPlot() {
}
