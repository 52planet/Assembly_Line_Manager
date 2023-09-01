#pragma once
#include <iostream>
#include <string>
#include "Utilities.h"

namespace sict {

	class ItemSet
	{

	private:
		std::string m_itemName, m_description;
		unsigned int m_serial_number, m_quantity;
		size_t m_next_pos = 0, m_field_width = 0;
	public:
		ItemSet(const std::string str);
		const std::string& getName() const;
		const unsigned int getSerialNumber() const;
		const unsigned int getQuantity() const;
		ItemSet& operator--();
		void display(std::ostream& os, bool full = true) const;
		//ItemSet(const ItemSet& obj) = delete; // disables copy construction
		//ItemSet& operator=(ItemSet & obj) = delete; // disables copy assignment
		//ItemSet& operator=(ItemSet&& obj) = delete; //disables move assignment

	};

}