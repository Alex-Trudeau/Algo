/*
 * ligne.cpp
 *
 *  Created on: 2016-09-22
 *      Author: etudiant
 */
#include "ligne.h"

Ligne::Ligne(const std::vector<std::string>& p_ligne):
	m_id(std::stoi(p_ligne[0])),
	m_numero(p_ligne[2]),
	m_description(p_ligne[4]),
	m_categorie(Ligne::couleurToCategorie(p_ligne[7])),
	m_voyages(std::vector<Voyage*> p_vide){

}

static Ligne::CategorieBus Ligne::couleurToCategorie(std::string p_couleur){
	switch (p_couleur){
	case "97BF0D":
		return CategorieBus::METRO_BUS;
		break;
	case "013888":
		return CategorieBus::LEBUS;
		break;
	case "E04503":
		return CategorieBus::EXPRESS;
		break;
	case "1A171B":
		return CategorieBus::COUCHE_TARD;
		break;
	}
}

static std::string Ligne::categorieToString(CategorieBus p_cat){
	switch (p_cat){
	case CategorieBus::METRO_BUS:
		return "METRO_BUS";
		break;
	case CategorieBus::LEBUS:
		return "LEBUS";
		break;
	case CategorieBus::EXPRESS:
		return "EXPRESS";
		break;
	case CategorieBus::COUCHE_TARD:
		return "COUCHE_TARD";
		break;
	}
}

CategorieBus Ligne::getCategorie() const{
	return m_categorie;
}

void Ligne::setCategorie(CategorieBus p_categorie){
	m_categorie = p_categorie;
}

std::pair<std::string, std::string> Ligne::getDestinations() const{
	// A FAIRE
}

unsigned int Ligne::getId() const{
	return m_id;
}

void Ligne::setId(unsigned int p_id){
	m_id = p_id;
}

const std::string& Ligne::getNumero() const;

void Ligne::setNumero(const std::string& numero);

const std::vector<Voyage*>& Ligne::getVoyages() const;

void Ligne::setVoyages(const std::vector<Voyage*>& voyages);

void Ligne::addVoyage(Voyage* ptr_voyage);

const std::string& Ligne::getDescription() const;

void Ligne::setDescription(const std::string& description);

friend std::ostream& Ligne::operator <<(std::ostream& f, const Ligne& p_ligne);



