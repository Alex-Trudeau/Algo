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
#include "auxiliaires.h"

using namespace std;

std::vector<std::string> split(const std::string &s, char delim) {
	std::istringstream splitter(s);
	std::vector<std::string> tokens;
	for (std::string partie; std::getline(splitter, partie, delim);
			tokens.push_back(partie))
		;
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
}
Date::Date(unsigned int an, unsigned int mois, unsigned int jour) {
}
bool Date::operator==(const Date & other) const {
}
bool Date::operator<(const Date & other) const {
}
bool Date::operator>(const Date & other) const {
}
std::ostream & operator<<(std::ostream & flux, const Date & p_date) {
}

Heure::Heure() {
}
Heure::Heure(unsigned int heure, unsigned int min, unsigned int sec) {
}
Heure Heure::add_secondes(unsigned int secs) const {
}
bool Heure::operator==(const Heure & other) const {
}
bool Heure::operator<(const Heure & other) const {
}
bool Heure::operator>(const Heure & other) const {
}
bool Heure::operator<=(const Heure & other) const {
}
bool Heure::operator>=(const Heure & other) const {
}
int Heure::operator-(const Heure & other) const {
}
std::ostream & operator<<(std::ostream & flux, const Heure & p_heure) {
}
