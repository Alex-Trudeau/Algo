/**
 * \file ligne.cpp
 * \brief Implantation de la classe Ligne
 * \author Daniel Lavoie Alexandre Trudeau
 * \version 1
 * \date  2016-09-22
 */
#include "ligne.h"

using namespace std;
/**
 * \brief Constructeur avec paramètre
 * Création d'un objet Ligne à partir du vecteur passé en paramètre.
 * \param[in] p_ligne Vecteur d'une ligne
 */
Ligne::Ligne(const std::vector<std::string>& p_ligne) :
		m_id(std::stoi(p_ligne[0])), m_numero(p_ligne[2]), m_description(
				p_ligne[4]), m_categorie(Ligne::couleurToCategorie(p_ligne[7])), m_voyages(
				std::vector<Voyage*>()) {
}
/**
 * \brief Conversion d'une couleur à une catégorie
 * \param[in] p_couleur
 * \return Catégorie de bus selon la couleur
 */
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
/**
 * \brief Conversion d'une catégorie en string
 * \param[in] p_cat une catégorie
 * \return String selon la catégorie
 */
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
/**
 * \brief Accesseur d'une catégorie
 * \return la catégorie
 */
CategorieBus Ligne::getCategorie() const {
	return m_categorie;
}
/**
 * \brief Ajuste une catégorie
 * \param[in] p_categorie
 */
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
/**
 * \brief Accesseur du id de la ligne
 * \return id de la ligne
 */
unsigned int Ligne::getId() const {
	return m_id;
}
/**
 * \brief Ajuste le id de la ligne
 * \param[in] p_id
 */
void Ligne::setId(unsigned int p_id) {
	m_id = p_id;
}
/**
 * \brief Accesseur du numéro de ligne
 * \return numéro de ligne
 */
const std::string& Ligne::getNumero() const {
	return m_numero;
}
/**
 * \brief Ajuste le numéro de ligne
 * \param[in] p_numero
 */
void Ligne::setNumero(const std::string& p_numero) {
	m_numero = p_numero;
}
/**
 * \brief Accesseur des voyages
 * \return vecteur de voyages
 */
const std::vector<Voyage*>& Ligne::getVoyages() const {
	return m_voyages;
}
/**
 * \brief Ajuste les voyages
 * \param[in] p_voyages vecteur de voyages
 */
void Ligne::setVoyages(const std::vector<Voyage*>& p_voyages) {
	m_voyages = p_voyages;
}
/**
 * \brief Permet d'ajouter un voyage dans le vecteur de voyages
 * \param[in] ptr_voyage
 */
void Ligne::addVoyage(Voyage* ptr_voyage) {
	m_voyages.push_back(ptr_voyage);
}
/**
 * \brief Accesseur de la description
 * \return m_description
 */
const std::string& Ligne::getDescription() const {
	return m_description;
}
/**
 * \brief Ajuste la description
 * \param[in] p_description
 */
void Ligne::setDescription(const std::string& p_description) {
	m_description = p_description;
}
/**
 * \brief Operator << qui permet d'affiche les informations que l'on veut de l'objet
 * \return f
 */
std::ostream& operator <<(std::ostream& f, const Ligne& p_ligne) {
	f << Ligne::categorieToString(p_ligne.getCategorie()) << " "
			<< p_ligne.getNumero() << " : " << p_ligne.getDescription();
	return f;
}
