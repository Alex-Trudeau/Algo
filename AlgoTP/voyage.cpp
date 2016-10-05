/**
 * \file voyage.cpp
 * \brief
 * \author Daniel Lavoie Alexandre Trudeau
 * \version 1
 * \date  2016-09-22
 */

#include "ContratException.h"
#include "voyage.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;
/**
 * \brief Constructeur avec paramètre
 * Création d'un objet voyage à partir du vecteur passé en paramètre.
 * \param[in] p_l Vecteur d'une ligne gtfs
 * \param[in] p_ligne pointeur sur un objet ligne
 */
Voyage::Voyage(const std::vector<std::string>& p_l, Ligne* p_ligne) :
		m_id(p_l[2]), m_destination(p_l[3]), m_service_id(p_l[1]), m_ligne(p_ligne) {
}
Arret & Voyage::arretDeLaStation(unsigned int p_num_station) {
	for (unsigned int i = 0; i < m_arrets.size(); i++){
		if( m_arrets[i].getStationId() == p_num_station) {
			return m_arrets[i];
		}

		else {
			// la station est pas dans le voyage
		}
	}
}
/**
 * \brief Accesseur des arrêts
 * \return m_arrets
 */
std::vector<Arret> Voyage::getArrets() const {
	return m_arrets;
}
/**
 * \brief Accesseur des destinations
 * \return m_destination
 */
const std::string& Voyage::getDestination() const {
	return m_destination;
}
/**
 * \brief Ajuste la destination
 * \param[in] p_destination
 */
void Voyage::setDestination(const std::string& p_destination) {
	m_destination = p_destination;
}
/**
 * \brief Accesseur de l'id du voyage
 * \return m_id
 */
std::string Voyage::getId() const {
	return m_id;
}
/**
 * \brief Ajuste le Id du voyage
 * \param[in] p_id
 */
void Voyage::setId(std::string p_id) {
	m_id = p_id;
}
/**
 * \brief Accesseur d'une ligne du voyage
 * \return m_ligne
 */
Ligne* Voyage::getLigne() const {
	return m_ligne;
}
/**
 * \brief Ajuste la ligne
 * \param[in] p_ligne
 */
void Voyage::setLigne(Ligne* p_ligne) {
	m_ligne = p_ligne;
}
/**
 * \brief Accesseur du serviceId du voyage
 * \return m_service_id
 */
std::string Voyage::getServiceId() const {
	return m_service_id;
}
/**
 * \brief Ajuste le serviceId du voyage
 * \param[in] p_service_id
 */
void Voyage::setServiceId(std::string p_service_id) {
	m_service_id = p_service_id;
}
/**
 * \brief Accesseur de l'heure de départ du voyage, passe par l'accesseur d'heure de départ de arrêt
 * \return heureDepart
 */
Heure Voyage::getHeureDepart() const {
	return m_arrets.front().getHeureDepart();
}
/**
 * \brief Accesseur de l'heure de fin du voyage, passe par l'accesseur d'heure de fin de arrêt
 * \return heureFin
 */
Heure Voyage::getHeureFin() const {
	return m_arrets.back().getHeureArrivee();
}
/**
 * \brief Mêt en ordre les arrêts pour ensuite ajuster les arrêts
 * \param[in] resultat -- vecteur d'arrêt
 */
void Voyage::setArrets(std::vector<Arret>& resultat) {
	sort(resultat.begin(),resultat.end());
	m_arrets = resultat;
}
bool Voyage::operator<(const Voyage & p_other) const {
	return (this->getHeureDepart() < p_other.getHeureDepart());
}
bool Voyage::operator>(const Voyage & p_other) const {
	return (this->getHeureDepart() > p_other.getHeureDepart());
}
/**
 * \brief Operator << qui permet d'affiche les informations que l'on veut de l'objet
 * \return flux
 */
std::ostream & operator<<(std::ostream & flux, const Voyage & p_voyage) {
	return flux << p_voyage.getLigne()->getNumero() << ": Vers " << p_voyage.getDestination() << endl;
}
