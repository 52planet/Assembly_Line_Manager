#include <string>
#include "Utilities.h"
namespace sict {
	
	char Utilities::m_delimiter = ' ';

	//default constructor sets object in safe empty state and sets field width
	Utilities::Utilities()
	{
		m_FieldWidth = 0;
	}

	//extractsToken from string
	const std::string Utilities::extractToken(const std::string& str, size_t& next_pos)
	{
		//define function variables
		size_t position = 0;
		std::string temp_string;

		//check next_pos to see if it holds a valid position
		if (next_pos != std::string::npos)
		{

			//extracts token starting at next_pos and ending at the delimeter '|'
			position = str.find(Utilities::m_delimiter, next_pos);
			position = position - next_pos;
			if (position != 0)
			{
				temp_string = str.substr(next_pos, position);
			}

			//compare field width to size of extracted token
			// if field width is smaller than the token then increase the field width
			if (m_FieldWidth < temp_string.size())
			{
				setFieldWidth(temp_string.size());
			}

			//store new next position
			//return the position of the next token of the string if it exists 

			if (position != std::string::npos)
			{
				next_pos = str.find(Utilities::m_delimiter, next_pos) + 1;
			}
			else
			{
				next_pos = std::string::npos;
				//str.substr(0, next_pos);
			}
		}
		//if not return the position that is beyond the end of the string	
		return temp_string;
		//report exception if one delimiter follows another without token between them.
	}



	//returns delimiting character
	const char Utilities::getDelimiter()const
	{
		return Utilities::m_delimiter;
	}

	//returns the current feildWidth of the object
	size_t Utilities::getFieldWidth() const
	{
		return m_FieldWidth;
	}
	
	//sets delimeter for all objects of the class
	void Utilities::setDelimiter(const char d)
	{
		Utilities::m_delimiter = d;
	}

	//sets feild width for the current object
	void Utilities::setFieldWidth(size_t fw)
	{
		m_FieldWidth = fw;
	}
}