#pragma once
#include <iostream>
#include <string> //std::string 
namespace sict {
	class Utilities
	{

	private:	

		static char m_delimiter;
		size_t m_FieldWidth = 0;

	public:
		//default constructor // safe empty state initialized its field width to a size that is less than the possible size token
		Utilities();
		const std::string extractToken(const std::string& str, size_t& next_pos);
		const char getDelimiter() const;
		size_t getFieldWidth() const;
		static void setDelimiter(const char d);
		void setFieldWidth(size_t);
	};
}

