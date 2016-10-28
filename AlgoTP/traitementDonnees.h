/*
 * traitementDonnees.h
 *
 *  Created on: Oct 28, 2016
 *      Author: xub-msi
 */

#ifndef TRAITEMENTDONNEES_H_
#define TRAITEMENTDONNEES_H_

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "ContratException.h"
#include "auxiliaires.h"
#include "coordonnees.h"
#include "arret.h"
#include "station.h"
#include "voyage.h"
#include "ligne.h"

void importer(std::vector<Station> & p_s, std::vector<Ligne> & p_l, std::vector<Voyage> & p_v,
		std::map<std::string,std::vector<Arret>> & p_a, std::map<std::string,std::vector<Date>> & p_d);

void importerStations(std::string p_nom_fichier, std::vector<Station> & p_obj, bool rm_entete);

void importerLignes(std::string p_nom_fichier, std::vector<Ligne> & p_obj, bool rm_entete);

void importerVoyages(std::string p_nom_fichier, std::vector<Voyage> & p_voyages, std::vector<Ligne> & p_lignes, bool rm_entete);

void importerArrets(std::string p_nom_fichier, std::map<std::string,std::vector<Arret>> & p_arrets, bool rm_entete);

void importerDates(std::string p_nom_fichier, std::map<std::string,std::vector<Date>> & p_dates, bool rm_entete);

bool triStationId(const Station& s1, const Station& s2);

bool triLigneNumero(const Ligne& l1,const Ligne& l2);

bool triVoyageId(const Voyage& v1, const Voyage& v2);

bool triArretNumSeq(const Arret& a1, const Arret& a2);

bool triHeureDep(const Voyage* v1, const Voyage* v2);

std::string tempsTraitement(Heure p_hrDepart);

#endif /* TRAITEMENTDONNEES_H_ */
