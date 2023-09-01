#include <iostream>
#include<string>
#include<iomanip>
#include <utility>
#include "CustomerOrder.h"
namespace sict {


	//default constructor
	//safe empty state
	CustomerOrder::CustomerOrder()
	{
		m_customer_name.clear();
		m_name_of_product_being_assembled.clear();
		//m_itemInfo->m_prod_name.clear();
		m_isfill = false;
		m_position = 0;
	}

	//one argument constructor
	//extracts tokens from str.
	CustomerOrder::CustomerOrder(const std::string& str)
	{
		//define local function variables
		Utilities obj; //used to access utilities functions
		size_t increment = 0;
		size_t breakout = 1;
		if (str != "")
		{
			m_customer_name = obj.extractToken(str, m_position);
			m_name_of_product_being_assembled = obj.extractToken(str,m_position);

			//loop through the remainder of the string until the end
			while (breakout != 0)
			{
				std::string temp = obj.extractToken(str, m_position);
				m_itemInfo.emplace_back();
				m_itemInfo[increment].m_prod_name = temp;
				m_itemInfo[increment].m_serial_number = 1;
				m_itemInfo[increment].m_filled_stat = false;
				increment++;
				breakout = m_position;
			}
		}
	}

	//destrutor
	//deletes dynamic memory 
	CustomerOrder::~CustomerOrder()
	{
	}

	CustomerOrder::CustomerOrder(CustomerOrder && obj)
	{
		*this = std::move(obj);
	}

	// = operator definition
	CustomerOrder& CustomerOrder::operator=(CustomerOrder && obj)
	{
		// copy object over 
		m_customer_name = obj.m_customer_name;
		m_name_of_product_being_assembled = obj.m_name_of_product_being_assembled;
		m_position = obj.m_position;
		m_isfill = obj.m_isfill;

		//store struct info
		m_itemInfo = obj.m_itemInfo;
		
		//delete info from obj
		obj.m_customer_name = "";
		obj.m_name_of_product_being_assembled = "";
		obj.m_position = 0;
		obj.m_isfill = false;
		
		//delete obj struct info

		for (unsigned int i = 0; i < obj.m_itemInfo.size(); i++)
		{
			obj.m_itemInfo[i].m_prod_name = "";
			obj.m_itemInfo[i].m_serial_number = 0;
			obj.m_itemInfo[i].m_filled_stat = false;
		}
		return *this;
	}

	//checks each item request, fills it if requested item is available and reports the filling
	void CustomerOrder::fillItem(ItemSet& item, std::ostream& os)
	{
		if (!m_isfill)
		{
			//loop through items to be added and check for the item passed in
			for (unsigned int i = 0; i < m_itemInfo.size(); i++)
			{
				//check if names are the same
				if (item.getName() == m_itemInfo[i].m_prod_name)
				{
					//an item has been found
					//check if the order for that item has been filled
					if (m_itemInfo[i].m_filled_stat == false)
					{
						//item has not been filled so we need to check if we have the inventory to fill the order
						if (item.getQuantity() > 0)
						{
							//fill order
							//change filled status
							m_itemInfo[i].m_filled_stat = true;
							m_itemInfo[i].m_serial_number = item.getSerialNumber();
							//display filled message
							os << " Filled " << m_customer_name << " [" << m_name_of_product_being_assembled << "]" << "[" << item.getName() << "]" << "[" << item.getSerialNumber() << "]" << std::endl;
							//delete the items from the item object that were removed
							--item;
						}
						// not enough quantity to fill order
						else
						{
							os << " Unable to fill " << m_customer_name << " [" << m_name_of_product_being_assembled << "]" << "[" << item.getName() << "]" << "[" << item.getSerialNumber() << "]" << " out of stock" << std::endl;
						}

					}
					else {
						//if the quantity is equal or larger than the items requested the order can be filled
						os << " Unable to fill " << m_customer_name << " [" << m_name_of_product_being_assembled << "]" << "[" << item.getName() << "]" << "[" << item.getSerialNumber() << "]" << " already filled" << std::endl;
					}
				}
			}
		}
	}

	//searches the list of items requested and returns true if all the requests have been filled.
	bool CustomerOrder::isFilled()const
	{
		//loop through list of items if one is found that isnt filled return false
		for (unsigned int i = 0; i < m_itemInfo.size(); i++)
		{
			if (m_itemInfo[i].m_filled_stat == false) {
				return false;
			}
		}
		return true;
	}

	//search for a particular item by name / return true if all requests for that item are filled
	bool CustomerOrder::isItemFilled(const std::string& item) const
	{
		for (unsigned int i = 0; i < m_itemInfo.size(); i++)
		{
			if (m_itemInfo[i].m_prod_name == item && m_itemInfo[i].m_filled_stat == false)
			{
				return false;
			}

		}
		return true;
	}

	//returns name of customer and their product in a format
	std::string CustomerOrder::getNameProduct() const
	{
		return m_customer_name + "[" + m_name_of_product_being_assembled + "]";
	}

	//prints in format
	void CustomerOrder::display(std::ostream& os, bool showDetail) const
	{
		if (showDetail == false)
		{
			std::cout << std::setw(13) << std::left << m_customer_name << "[" << m_name_of_product_being_assembled << "]" << std::endl;
			for (unsigned int i = 0; i < m_itemInfo.size(); i++)
			{
				os << "             " << m_itemInfo[i].m_prod_name << std::endl;
			}
		}
		else
		{
			
			os << std::left << std::setw(13) << m_customer_name << "[" << m_name_of_product_being_assembled << "]" << std::endl;

			for (size_t i = 0; i < m_itemInfo.size(); i++) 
			{
				if (m_itemInfo[i].m_filled_stat)
					os <<std::setw(13) << "    " << "[" << m_itemInfo[i].m_serial_number << "] " << std::right << m_itemInfo[i].m_prod_name << " - FILLED" << std::endl;
				else
					os <<std::setw(13) <<  "    " << "[0] " << std::right << m_itemInfo[i].m_prod_name << " - MISSING" << std::endl;
			}
		}
	}

	std::string CustomerOrder::getCustName()
	{
		return m_customer_name;
	}
}