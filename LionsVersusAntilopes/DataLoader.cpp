#include "pch.h"
#include "DataLoader.h"

using namespace LionsVersusAntilopes;

DataLoader * DataLoader::m_instance = 0;

DataLoader::DataLoader()
{
	rapidxml::file<> xmlFile("GameData.xml"); 
	m_fileReader.parse<0>(xmlFile.data());
	m_nodeLion = m_fileReader.first_node()->first_node("lion");
	m_nodeAntilope = m_fileReader.first_node()->first_node("antilope");
	m_nodeNumbersAnimal = m_fileReader.first_node()->first_node("numberAnimals");
	m_nodeFlag= m_fileReader.first_node()->first_node("flag");
}

DataLoader * DataLoader::getInstance()
{
	if (m_instance == 0) m_instance = new DataLoader();
	return m_instance;
}

std::string DataLoader::getLionAttribute(std::string key)
{
	return std::string(m_nodeLion->first_attribute(key.c_str())->value());
}

std::string DataLoader::getAntilopeAttribute(std::string key)
{
	return std::string(m_nodeAntilope->first_attribute(key.c_str())->value());
}

std::string DataLoader::getFlagAttribute(std::string key)
{
	return std::string(m_nodeFlag->first_attribute(key.c_str())->value());
}

std::string DataLoader::getNumbersAnimalAttribute(std::string key)
{
	return std::string(m_nodeLion->first_attribute(key.c_str())->value());
}
