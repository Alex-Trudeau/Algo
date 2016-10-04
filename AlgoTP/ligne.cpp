/*
 * ligne.cpp
 *
 *  Created on: 2016-09-22
 *      Author: etudiant
 */
#include "ligne.h"

using namespace std;

Ligne::Ligne(const std::vector<std::string>& p_ligne) :
		m_id(std::stoi(p_ligne[0])), m_numero(p_ligne[2]), m_description(
				p_ligne[4]), m_categorie(Ligne::couleurToCategorie(p_ligne[7])), m_voyages(
				std::vector<Voyage*>()) {
}

CategorieBus Ligne::couleurToCategorie(std::string p_couleur) {
	if (p_couleur == "97BF0D")
		return CategorieBus::METRO_BUS;
	if (p_couleur == "013888")
		return CategorieBus::LEBUS;
	if (p_couleur == "E04503")
		return CategorieBus::EXPRESS;
	if (p_couleur == "1A171B" || p_couleur == "003888")
		return CategorieBus::COUCHE_TARD;
}

std::string Ligne::categorieToString(CategorieBus p_cat) {
	if (p_cat == CategorieBus::METRO_BUS)
		return "METRO_BUS";
	if (p_cat == CategorieBus::LEBUS)
		return "LEBUS";
	if (p_cat == CategorieBus::EXPRESS)
		return "EXPRESS";
	if (p_cat == CategorieBus::COUCHE_TARD)
		return "COUCHE_TARD";
}

CategorieBus Ligne::getCategorie() const {
	return m_categorie;
}

void Ligne::setCategorie(CategorieBus p_categorie) {
	m_categorie = p_categorie;
}

std::pair<std::string, std::string> Ligne::getDestinations() const {	// Marche pas!!!
	std::vector<string> destinations;
	for (int i = 0; i < m_voyages.size(); i++) {	// Doublons?
		if(destinations.size() == 0)
			destinations.push_back(m_voyages[i]->getDestination());
		else
			if(m_voyages[i]->getDestination() != destinations[0])
				destinations.push_back(m_voyages[i]->getDestination());
	}
	if (destinations.size() == 1)
		return {destinations[0], ""};
	else
		return {destinations[0], destinations[1]};
	//return {"Chez moi", "Chez toi"};
}

unsigned int Ligne::getId() const {
	return m_id;
}

void Ligne::setId(unsigned int p_id) {
	m_id = p_id;
}

const std::string& Ligne::getNumero() const {
	return m_numero;
}

void Ligne::setNumero(const std::string& p_numero) {
	m_numero = p_numero;
}

const std::vector<Voyage*>& Ligne::getVoyages() const {
	return m_voyages;
}

void Ligne::setVoyages(const std::vector<Voyage*>& p_voyages) {
	m_voyages = p_voyages;
}

void Ligne::addVoyage(Voyage* ptr_voyage) {
	m_voyages.push_back(ptr_voyage);
}

const std::string& Ligne::getDescription() const {
	return m_description;
}

void Ligne::setDescription(const std::string& p_description) {
	m_description = p_description;
}

std::ostream& operator <<(std::ostream& f, const Ligne& p_ligne) {
	f << Ligne::categorieToString(p_ligne.getCategorie()) << " "
			<< p_ligne.getNumero() << " : " << p_ligne.getDescription();
	return f;
}
