/**
 * \file station.cpp
 * \brief
 * \author Daniel Lavoie Alexandre Trudeau
 * \version 1
 * \date  2016-09-22
 */

#include "station.h"

using namespace std;
/**
 * \brief Constructeur avec paramètre
 * Création d'un objet Ligne à partir du vecteur passé en paramètre.
 * \param[in] p_ligne Vecteur d'une ligne
 */
Station::Station(const std::vector<std::string>& p_ligne):
	m_id(std::stoi(p_ligne[0])),m_nom(p_ligne[1]),
	m_description(p_ligne[2]),m_coords(Coordonnees(std::stod(p_ligne[3]),std::stod(p_ligne[4]))),
	m_voyages_passants(std::vector<Voyage*>()){

}

std::ostream& operator<<(std::ostream& flux, const Station& p_station){
	return  flux << p_station.m_id << " - " << p_station.m_nom;
}
/**
 * \brief Accesseur des coordonnées
 * \return m_coords
 */
const Coordonnees& Station::getCoords() const{
	return m_coords;
}
/**
 * \brief Ajuste les coordonnées
 * \param[in] p_coords
 */
void Station::setCoords(const Coordonnees& p_coords){
	m_coords = p_coords;
}
/**
 * \brief Accesseur de la description
 * \return m_description
 */
const std::string& Station::getDescription() const{
	return m_description;
}
/**
 * \brief Ajuste la description
 * \param[in] p_description
 */
void Station::setDescription(const std::string& p_description){
	m_description = p_description;
}
/**
 * \brief Accesseur de tout les lignes passantes par une station
 * \return vecteur de lignesPassantes
 */
std::vector<Ligne*> Station::getLignesPassantes() const{
	std::vector<Ligne*> LignesPassantes;
	for(int i =0 ; i < m_voyages_passants.size(); i++){

		LignesPassantes.push_back(m_voyages_passants[i]->getLigne());

	}

	return LignesPassantes;
}
/**
 * \brief Accesseur du nom de la station
 * \return m_nom
 */
const std::string& Station::getNom() const{
	return m_nom;
}
/**
 * \brief Ajuste le nom de la station
 * \param[in] p_nom
 */
void Station::setNom(const std::string& p_nom){
	m_nom = p_nom;
}
/**
 * \brief Accesseur du id de la station
 * \return m_id
 */
unsigned int Station::getId() const{
	return m_id;
}
/**
 * \brief Ajuste le id de la station
 * \param[in] p_id
 */
void Station::setId(unsigned int p_id){
	m_id = p_id;
}
/**
 * \brief Accesseur de tout les voyages passantes par une station
 * \return vecteur de m_voyages_passants
 */
const std::vector<Voyage*> & Station::getVoyagesPassants() const{
	return m_voyages_passants;
}
/**
 * \brief Ajoute un voyage à la station
 * \param[in] ptr_voyage
 */
void Station::addVoyage(Voyage* ptr_voyage){
	m_voyages_passants.push_back(ptr_voyage);
}
/**
 * \brief Calcule la distance entre la derniere station et celle-ci
 * \param[in] p_station
 */
double Station::distance(const Station& p_station) const{
	return this->getCoords()-p_station.getCoords();
}

