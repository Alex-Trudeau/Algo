/*
 * voyage.cpp
 *
 *  Created on: 2016-09-22
 *      Author: etudiant
 */

#include "ContratException.h"
#include "voyage.h"
#include <sstream>
#include <iostream>

namespace tp {

	Voyage::Voyage(const std::vector<std::string>& ligne_gtfs, Ligne* p_ligne){}
	Arret & Voyage::arretDeLaStation(unsigned int p_num_station){}
	std::vector<Arret> Voyage::getArrets() const{}
	const std::string& Voyage::getDestination() const{}
	void Voyage::setDestination(const std::string& p_destination){}
	std::string Voyage::getId() const{}
	void Voyage::setId(std::string p_id){}
	Ligne* Voyage::getLigne() const{}
	void Voyage::setLigne(Ligne* p_ligne){}
	std::string Voyage::getServiceId() const{}
	void Voyage::setServiceId(std::string p_service_id){}
	Heure Voyage::getHeureDepart() const{}
	Heure Voyage::getHeureFin() const{}
	void Voyage::setArrets(std::vector<Arret>& resultat){}
	bool Voyage::operator< (const Voyage & p_other) const{}
	bool Voyage::operator> (const Voyage & p_other) const{}
	std::ostream & operator<<(std::ostream & flux, const Voyage & p_voyage){}

}
