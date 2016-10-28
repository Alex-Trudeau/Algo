/*
 * affichage.h
 *
 *  Created on: Oct 28, 2016
 *      Author: xub-msi
 */

#ifndef AFFICHAGE_H_
#define AFFICHAGE_H_

#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include "ContratException.h"
#include "auxiliaires.h"
#include "coordonnees.h"
#include "arret.h"
#include "station.h"
#include "voyage.h"
#include "ligne.h"
#include "traitementDonnees.h"

void afficherLignesTrieesNo(std::ofstream & p_fichier, std::vector<Ligne> & p_obj);

void afficherStationsTrieesNo(std::ofstream & p_fichier, std::vector<Station> & p_obj);

void afficherVoyagesProchaineHeure(std::ofstream & p_fichier, std::vector<Voyage> & p_obj,
		std::map<std::string,std::vector<Date>> & p_dates);

void tp1(std::ofstream & p_fichier, std::vector<Ligne> & p_l, std::vector<Station> & p_s,
		std::vector<Voyage> & p_v, std::map<std::string,std::vector<Date>> & p_d);

#endif /* AFFICHAGE_H_ */
