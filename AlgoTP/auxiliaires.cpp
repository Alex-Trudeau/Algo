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
#include <algorithm>
#include <ctime>
#include "auxiliaires.h"
#include "ContratException.h"

using namespace std;

std::vector<std::string> split(const std::string &s, char delim) {
	std::istringstream splitter(s);
	std::vector<std::string> tokens;
	for (std::string partie; std::getline(splitter, partie, delim);
			tokens.push_back(partie)){
		partie.erase(std::remove(partie.begin(), partie.end(), '"'), partie.end());
	}
	//cette ligne etait pour test  cout << tokens[4] << endl;
	return tokens;
}

/*!
 * \brief Permet de lire un fichier au format gtfs
 * \param[in] nomFichier: chemin d'acces au fichier qui est suposé contennir plusieurs lignes et plusieurs colonnes
 * \param[out] resultats: vecteur 2D destiné à contenir le fichier, l'élement [i][j] représente la ième ligne et la jème colonne du fichier
 * \param[in] delimiteur: le caractère délimiteur des colonnes dans ce fichier.
 * \param[in] rm_entete: un booléen qui spécifie s'il faut supprimer ou pas la première ligne du fichier.
 * \pre Le fichier existe.
 * \exception logic_error s'il y a un problème lors de l'ouverture du fichier.
 */
void lireFichier(std::string nomFichier,
		std::vector<std::vector<std::string>>& resultats, char delimiteur,
		bool rm_entete) {
	ifstream fichier(nomFichier);
	string ligne;
	if (fichier.is_open()) {
		if (rm_entete)
			getline(fichier, ligne);
		while (getline(fichier, ligne)) {
			resultats.push_back(split(ligne, delimiteur));
		}
		fichier.close();

	} else {
		//raise logic_error
	}

}

Date::Date() {
	time_t t;
	time(&t);
	tm *ltm = localtime(&t);
	m_an = ltm->tm_year;
	m_jour = ltm->tm_mday;
	m_mois = ltm->tm_mon;
}
Date::Date(unsigned int an, unsigned int mois, unsigned int jour):
	m_an(an), m_mois(mois), m_jour(jour){
	long JourParMois[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if(mois == 2)
		if((an % 4 == 0 && an % 100 != 0) || (an % 4 == 0 && an % 100 == 0 && an % 400 ==0))
			JourParMois[1]++;

	PRECONDITION(mois > 0 && mois <= 12);
	PRECONDITION(an > 1970 && an < 2037);
	PRECONDITION(jour > 0 && jour <= JourParMois[mois-1]);
}
bool Date::operator==(const Date & other) const {
	return (this->m_an == other.m_an && this->m_mois == other.m_mois && this->m_jour == other.m_jour);
}
bool Date::operator<(const Date & other) const {
	if(this->m_an < other.m_an)
		return true;
	if(this->m_an == other.m_an){
		if(this->m_mois < other.m_mois)
			return true;
		else{
			if(this->m_mois == other.m_mois)
				if(this->m_jour < other.m_jour)
					return true;
		}
	}
	return false;
}
bool Date::operator>(const Date & other) const {
	if(this->m_an > other.m_an)
		return true;
	if(this->m_an == other.m_an){
		if(this->m_mois > other.m_mois)
			return true;
		else{
			if(this->m_mois == other.m_mois)
				if(this->m_jour > other.m_jour)
					return true;
		}
	}
	return false;
}
std::ostream & operator<<(std::ostream & flux, const Date & p_date) {
	flux << p_date.m_an << "-" << p_date.m_mois << "-" << p_date.m_jour;
	return flux;
}

Heure::Heure() {
	time_t t;
	time(&t);
	tm *ltm = localtime(&t);
	m_heure = ltm->tm_hour;
	m_min = ltm->tm_min;
	m_sec = ltm->tm_sec;
}
Heure::Heure(unsigned int heure, unsigned int min, unsigned int sec) :
		m_heure(heure), m_min(min), m_sec(sec) {
	PRECONDITION(heure >= 0 && heure < 30);
	PRECONDITION(min >= 0 && min < 60);
	PRECONDITION(sec >= 0 && sec < 60);
}
Heure Heure::add_secondes(unsigned int secs) const {
	unsigned int sec = m_sec + secs;
	unsigned int min = m_min;
	unsigned int hr = m_heure;
	if (sec >= 60) {
		sec -= 60;
		min++;
	}
	if (min >= 60) {
		min -= 60;
		hr++;
	}
	return Heure(hr, min, sec);
}
bool Heure::operator==(const Heure & other) const {
	return (this->m_heure == other.m_heure && this->m_min == other.m_min
			&& this->m_sec == other.m_sec);
}
bool Heure::operator<(const Heure & other) const {
	return (this->m_heure * 3600 + this->m_min * 60 + this->m_sec
			< other.m_heure * 3600 + other.m_min * 60 + other.m_sec);
}
bool Heure::operator>(const Heure & other) const {
	return (this->m_heure * 3600 + this->m_min * 60 + this->m_sec
			> other.m_heure * 3600 + other.m_min * 60 + other.m_sec);
}
bool Heure::operator<=(const Heure & other) const {
	return (this->operator==(other) || this->operator<(other));
}
bool Heure::operator>=(const Heure & other) const {
	return (this->operator==(other) || this->operator>(other));
}
int Heure::operator-(const Heure & other) const {	//retour en secondes
	return (this->m_heure * 3600 + this->m_min * 60 + this->m_sec)
			- (other.m_heure * 3600 + other.m_min * 60 + other.m_sec);
}
std::ostream & operator<<(std::ostream & flux, const Heure & p_heure) {
	flux << p_heure.m_heure << ":" << p_heure.m_min << ":" << p_heure.m_sec
			<< endl;
	return flux;
}
