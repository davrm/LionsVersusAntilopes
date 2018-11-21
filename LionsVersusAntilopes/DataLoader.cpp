#include "pch.h"
#include "DataLoader.h"

using namespace LionsVersusAntilopes;

DataLoader * DataLoader::m_instance = 0;

DataLoader::DataLoader()
{
	rapidxml::file<> xmlFile("GameData.xml"); 
	m_fileReader.parse<0>(xmlFile.data());
	rapidxml::xml_node<char> * root = m_fileReader.first_node();
	for (rapidxml::xml_node<char> * it_n = root->first_node(); it_n != nullptr; it_n = it_n->next_sibling())
	{
		std::string key_n = it_n->name();
		for (rapidxml::xml_attribute<char> * it_a = it_n->first_attribute(); it_a != nullptr; it_a = it_a->next_attribute())
		{
			std::string key_a = it_a->name();
			std::string key_av = it_a->value();
			m_dataMap[key_n][key_a] = key_av;
		}
	}
}

DataLoader * DataLoader::getInstance()
{
	
	if (m_instance == 0) m_instance = new DataLoader();
	return m_instance;
}

std::string DataLoader::getLionAttribute(std::string key)
{
	return m_dataMap["lion"][key];
}

std::string DataLoader::getAntilopeAttribute(std::string key)
{
	return m_dataMap["antilope"][key];
}

std::string DataLoader::getFlagAttribute(std::string key)
{
	return m_dataMap["flag"][key];
}

std::string DataLoader::getNumbersAnimalAttribute(std::string key)
{
	return m_dataMap["numberAnimals"][key];
}
