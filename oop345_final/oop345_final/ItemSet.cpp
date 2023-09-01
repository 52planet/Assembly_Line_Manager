#include <string>
#include <iomanip>
#include "ItemSet.h"
namespace sict{

	//extrats 4 tokens from the string, populates object with the tokens and determines the field width to be used.
	ItemSet::ItemSet(const std::string str)
	{
		Utilities obj;
		//extract tokens 
		//call extract token from utilities
		if (str != "")
		{
			m_itemName = obj.extractToken(str, m_next_pos);
			m_serial_number = std::stoi(obj.extractToken(str, m_next_pos)); //stoi converts string to int
			m_quantity = std::stoi(obj.extractToken(str, m_next_pos));		//stoi converts string to int
			m_description = (obj.extractToken(str, m_next_pos));
			//determine field width
			m_field_width = obj.getFieldWidth();
		}
	}

	//returns reference to name of item
	const std::string& ItemSet::getName() const
	{
		return m_itemName;
	}

	//returns serial number of the item
	const unsigned int ItemSet::getSerialNumber() const
	{
		return m_serial_number;
	}

	//returns the remaining number of items in the set
	const unsigned int ItemSet::getQuantity() const
	{
		return m_quantity;
	}

	//reduces the number of items in stock by one and increases the serial number by one
	ItemSet& ItemSet::operator--()
	{
		m_quantity = m_quantity - 1;
		m_serial_number++;
		return *this;
	}

	//inserts data from current object into OS.
	void ItemSet::display(std::ostream& os, bool full) const
	{
		// if bool is false data is name of the items in set and next serial number to be assigned
		if (!full) 
		{
			os << m_itemName << m_serial_number;
		}

		// if bool is true data consists of name, serial number, quantity in stock, and the description
		else
		{
			os << std::setw(13) << std::left << std::fixed << m_itemName;
			os << "[" << m_serial_number << "] Quantity " << std::setw(3) << std::left << m_quantity << " Description: " << m_description << std::endl;
		}
	}
	
		
}