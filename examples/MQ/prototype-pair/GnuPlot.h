#ifndef GNUPLOT_H_
#define GNUPLOT_H_

#include <iostream>
#include <fstream>
#include <string>


class GnuPlot {
public:
	GnuPlot();
	void write(std::string s1, std::string s2);
	virtual ~GnuPlot();
};

#endif
