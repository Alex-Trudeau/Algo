/*
 * arret.cpp
 *
 *  Created on: 2016-09-22
 *      Author: etudiant
 */

#include "arret.h"
#include "auxiliaires.h"

using namespace std;

Arret::Arret(const std::vector<std::string>& p_l) :
		m_voyage_id(p_l[0]), m_station_id(stoi(p_l[3])), m_numero_sequence(stoi(p_l[4])) {
	vector<string> heure_arr = split(p_l[1],':');
	vector<string> heure_dep = split(p_l[2],':');
	m_heure_arrivee = Heure(stoul(heure_arr[0]),stoul(heure_arr[1]),stoul(heure_arr[2]));
	m_heure_depart = Heure(stoul(heure_dep[0]),stoul(heure_dep[1]),stoul(heure_dep[2]));
}

const Heure& Arret::getHeureArrivee() const {
	return m_heure_arrivee;
}

void Arret::setHeureArrivee(const Heure& p_heureArrivee) {
	m_heure_arrivee = p_heureArrivee;
}

const Heure& Arret::getHeureDepart() const {
	return m_heure_depart;
}

void Arret::setHeureDepart(const Heure& p_heureDepart) {
	m_heure_depart = p_heureDepart;
}

unsigned int Arret::getNumeroSequence() const {
	return m_numero_sequence;
}

void Arret::setNumeroSequence(unsigned int p_numeroSequence) {
	m_numero_sequence = p_numeroSequence;
}

unsigned int Arret::getStationId() const {
	return m_station_id;
}

void Arret::setStationId(unsigned int p_stationId) {
	m_station_id = p_stationId;
}

std::string Arret::getVoyageId() const {
	return m_voyage_id;
}

void Arret::setVoyageId(const std::string& p_voyageId) {
	m_voyage_id = p_voyageId;
}

bool Arret::operator<(const Arret & p_other) const {
	// Pas fait
}

bool Arret::operator>(const Arret & p_other) const {
	// Pas fait
}

std::ostream & operator<<(std::ostream & flux, const Arret & p_arret) {
	// Pas fait
}
