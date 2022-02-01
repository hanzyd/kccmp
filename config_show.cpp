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

void save_set(const string &filename, const set<string> &diff, const config &c1)
{
	std::ofstream file(filename);

	if (!file.is_open()) {
		std::cout << "Failed to open file" << std::endl;
		return;
	}

	for (auto itr = diff.begin(); itr != diff.end(); itr++) {
		file << setw(32) << itr->c_str() << "\t" << *c1.find(*itr)
		     << endl;
	}

	file.flush();
	file.close();
}

void save_diff(const string &filename, const set<string> &diff,
	       const config &c1, const config &c2)
{
	std::ofstream file(filename);

	if (!file.is_open()) {
		std::cout << "Failed to open file" << std::endl;
		return;
	}

	for (auto itr = diff.begin(); itr != diff.end(); itr++) {
		file << setw(32) << itr->c_str() << "\t" << setw(8)
		     << *c1.find(*itr) << "\t" << *c2.find(*itr) << endl;
	}

	file.flush();
	file.close();
}

void compare(const string &filename1, const string &filename2)
{
	config c1;
	config c2;
	c1.read(filename1.c_str());
	c2.read(filename2.c_str());
	set<string> cunion, diff, in1, in2;

	config::analyze(c1, c2, cunion, diff, in1, in2);

	save_diff("diff.txt", diff, c1, c2);
	save_set("in1.txt", in1, c1);
	save_set("in2.txt", in2, c2);
}

int main(int argc, char **argv)
{
	if (3 != argc) {
		cerr << "symtax error, should be:" << endl;
		cerr << "% " << argv[0] << " config_file1 config_file2" << endl;
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
		cerr << "caught unhandled exception" << endl;
		result = 1;
	}
	return result;
}
