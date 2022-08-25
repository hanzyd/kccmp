/*----------------------------------------------------------------------
 * $Id: config_view.cpp,v 1.6 2012-02-12 01:31:30 salem Exp $
 *
 *
 * Copyright (C)   2005            Salem Ganzhorn <eyekode@yahoo.com>
 *
 * This file is part of kccmp - Kernel Config CoMPare
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *----------------------------------------------------------------------*/

#include <sstream>
#include <fstream>
#include <iomanip>

#include "config.hpp"

using namespace std;

void compare(const string &filename1, const string &filename2)
{
	config c1;
	config c2;
	c1.read(filename1.c_str());
	c2.read(filename2.c_str());
	set<string> same, diff, in1, in2;

	config::analyze(c1, c2, same, diff, in1, in2);

	for (auto itr = diff.begin(); itr != diff.end(); itr++) {
		std::cout << setw(32) << itr->c_str() << "\t" << setw(8)
			  << *c1.find(*itr) << "\t" << *c2.find(*itr) << endl;
	}

	for (auto itr = in1.begin(); itr != in1.end(); itr++) {
		std::cout << setw(32) << itr->c_str() << "\t" << setw(8)
			  << *c1.find(*itr) << "\t"
			  << "Missing" << endl;
	}

	for (auto itr = in2.begin(); itr != in2.end(); itr++) {
		std::cout << setw(32) << itr->c_str() << "\t" << setw(8)
			  << "Missing"
			  << "\t" << *c2.find(*itr) << endl;
	}
}

int main(int argc, char **argv)
{
	if (3 != argc) {
		cerr << "Usage:" << endl;
		cerr << argv[0] << " config1 config2" << endl;
		exit(-1);
	}
	int result;
	try {
		compare(argv[1], argv[2]);
		result = 0;
	} catch (exception &e) {
		cerr << e.what() << endl;
		result = 2;
	} catch (...) {
		cerr << "Caught unhandled exception" << endl;
		result = 1;
	}
	return result;
}
