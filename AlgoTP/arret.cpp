/**
 * \file arret.cpp
 * \brief
 * \author Daniel Lavoie Alexandre Trudeau
 * \version 1
 * \date  2016-09-22
 */

#include "arret.h"
#include "auxiliaires.h"

using namespace std;

/**
 * \brief Constructeur avec paramètre
 * Création d'un objet Arrêt à partir du vecteur passé en paramètre.
 * \param[in] p_l(ligne_gtfs) Vecteur d'une ligne
 */
Arret::Arret(const std::vector<std::string>& p_l) :
		m_voyage_id(p_l[0]), m_station_id(stoi(p_l[3])), m_numero_sequence(stoi(p_l[4])) {
	vector<string> heure_arr = split(p_l[1],':');
	vector<string> heure_dep = split(p_l[2],':');
	m_heure_arrivee = Heure(stoul(heure_arr[0]),stoul(heure_arr[1]),stoul(heure_arr[2]));
	m_heure_depart = Heure(stoul(heure_dep[0]),stoul(heure_dep[1]),stoul(heure_dep[2]));
}

/**
 * \brief Accesseur heure d'arrivee
 * \return l'heure d'arrivee
 */
const Heure& Arret::getHeureArrivee() const {
	return m_heure_arrivee;
}
/**
 * \brief Ajuste l'heure d'arrivee
 * \param[in] p_heureArrivee
 */
void Arret::setHeureArrivee(const Heure& p_heureArrivee) {
	m_heure_arrivee = p_heureArrivee;
}

/**
 * \brief Accesseur heure de départ
 * \return l'heure de départ
 */
const Heure& Arret::getHeureDepart() const {
	return m_heure_depart;
}
/**
 * \brief Ajuste l'heure de départ
 * \param[in] p_heureDepart
 */
void Arret::setHeureDepart(const Heure& p_heureDepart) {
	m_heure_depart = p_heureDepart;
}

/**
 * \brief Accesseur numero sequence
 * \return le numero de sequence
 */
unsigned int Arret::getNumeroSequence() const {
	return m_numero_sequence;
}
/**
 * \brief Ajuste numéro séquence
 * \param[in] p_numeroSequence
 */
void Arret::setNumeroSequence(unsigned int p_numeroSequence) {
	m_numero_sequence = p_numeroSequence;
}

/**
 * \brief Accesseur station id
 * \return le numéro de la station
 */
unsigned int Arret::getStationId() const {
	return m_station_id;
}
/**
 * \brief Ajuste numéro station
 * \param[in] p_stationId
 */
void Arret::setStationId(unsigned int p_stationId) {
	m_station_id = p_stationId;
}

/**
 * \brief Accesseur voyage id
 * \return le numéro du voyage
 */
std::string Arret::getVoyageId() const {
	return m_voyage_id;
}
/**
 * \brief Ajuste numéro voyage
 * \param[in] p_voyageId
 */
void Arret::setVoyageId(const std::string& p_voyageId) {
	m_voyage_id = p_voyageId;
}

bool Arret::operator<(const Arret & p_other) const {
	return this->getNumeroSequence() < p_other.getNumeroSequence();
}

bool Arret::operator>(const Arret & p_other) const {
	return this->getNumeroSequence() > p_other.getNumeroSequence();
}

std::ostream & operator<<(std::ostream & flux, const Arret & p_arret) {
	flux << p_arret.getHeureArrivee() << p_arret.getVoyageId() << endl;
	return flux;
}
