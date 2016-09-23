/*
 * main.cpp
 *
 *  Created on: 2016-09-22
 *      Author: etudiant
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int main(){

	string line_;
	ifstream file_("bob.txt");

	if(file_.is_open()){
		while(getline(file_,line_))
		{
			cout<<line_<< '\n';
		}
		file_.close();
	}
	else {
		cout<<"File isn't open"<< '\n';
	}


	return 0;
}
