/*
 * auxiliaires.cpp
 *
 *  Created on: 2016-09-22
 *      Author: etudiant
 */

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;


std::vector<std::string> split(const std::string &s, char delim){
	std::istringstream split(s);
	std::vector<std::string> tokens;
	for (std::string each; std::getline(split, each, delim); tokens.push_back(each));
	cout << tokens[4] << endl;
	return tokens;

}
