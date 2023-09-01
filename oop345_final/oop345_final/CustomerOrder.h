#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "ItemSet.h"
namespace sict {

	class CustomerOrder
	{

	private:
		//data members

		//holds customers name
		std::string m_customer_name;

		//holds name of product being assembled
		std::string m_name_of_product_being_assembled;

		// one customer order can have many items and so we keep track of the product info here
		struct
		{
		public:
			std::string m_prod_name; //product name
			size_t m_serial_number = 0; // serial_number
			bool m_filled_stat; // filled status of particular item / defaults to false
		} itemInfo;
		//vector of anonamous struct
		std::vector<decltype(itemInfo)> m_itemInfo;
		//position
		size_t m_position = 0;

		//bool m_filled_status; //this staus is only true if all orders are filled for customer
		bool m_isfill = false;

	public:

		//default constructor
		CustomerOrder();

		//one argument constructor
		CustomerOrder(const std::string&);

		//destrutor
		~CustomerOrder();

		//move constructor
		CustomerOrder(CustomerOrder &&);

		//= operator
		CustomerOrder& operator=(CustomerOrder &&);

		//checks each item request, fills it if requested item is available and reports the filling
		void fillItem(ItemSet& item, std::ostream& os);

		//searches the list of items requested and returns true if all the requests have been filled.
		bool isFilled()const;

		//search for a particular item by name / return true if all requests for that item are filled
		bool isItemFilled(const std::string& item) const;

		//returns name of customer and their product in a format
		std::string getNameProduct() const;

		//prints in format
		void display(std::ostream& os, bool showDetail = false) const;

		//returns customer name
		std::string getCustName();

		//deleted copy constructor and copy assignment operator

	};
}