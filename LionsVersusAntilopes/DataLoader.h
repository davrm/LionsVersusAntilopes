#pragma once
#include "Libraries/rapidxml_utils.hpp"

namespace LionsVersusAntilopes
{
	class DataLoader
	{
	public:
		static DataLoader * getInstance();
		std::string getLionAttribute(std::string key);
		std::string getAntilopeAttribute(std::string key);
		std::string getFlagAttribute(std::string key);
		std::string getNumbersAnimalAttribute(std::string key);

	private:
		static DataLoader * m_instance;
		DataLoader();
		rapidxml::xml_document<> m_fileReader;
		rapidxml::xml_node<char> * m_nodeNumbersAnimal;
		rapidxml::xml_node<char> * m_nodeFlag;
		rapidxml::xml_node<char> * m_nodeLion;
		rapidxml::xml_node<char> * m_nodeAntilope;
		
	};
}

