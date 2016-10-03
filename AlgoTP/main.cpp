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
//#include "arret.h"
#include "auxiliaires.h"
#include "coordonnees.h"
#include "ligne.h"
#include "station.h"
//#include "voyage.h"

using namespace std;
using namespace tp;

int main(){

	vector<string> test;
	string line_;
	ifstream file_("TXT/routes.txt");

	if(file_.is_open()){
		while(getline(file_,line_))
		{
			test.push_back(line_);
		}
		file_.close();

		unsigned int taille = test.size();
		for (unsigned int i = 0; i < taille; i++){
			cout << test[i] << endl;

		}

	}
	else {
		cout<<"File isn't open"<< '\n';
	}

	split(test[1], ',');


	return 0;
}
