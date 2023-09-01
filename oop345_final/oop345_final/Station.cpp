//implementation of station.h file
#include <string>
#include<iostream>
#include "Station.h"


//namespace
namespace sict
{


	Station::Station(const std::string& s)
		:m_itemSet_object(s) //itemSet constructor
	{
		//get station name
		m_station_name = m_itemSet_object.getName();
	}

	void Station::display(std::ostream& os)const 
	{
		m_itemSet_object.display(os);
	}


	void Station::fill(std::ostream& os)
	{
		if (!m_cust_queue.empty()) //if there is still orders in the queue
		{
			//fill order
			m_cust_queue.front().fillItem(m_itemSet_object, os);
		}
	}

	const std::string& Station::getName() const
	{
		return m_itemSet_object.getName();
	}

	bool Station::hasAnOrderToRelease() const 
	{
		bool Order = false; //stores return value
		if (!m_cust_queue.empty()) //false
		{
			if (!m_itemSet_object.getQuantity())
				Order = true;
			else
				Order = m_cust_queue.front().isItemFilled(m_station_name);
		}
		return Order;
	}


	Station& Station::operator--()
	{
		--m_itemSet_object; //overloaded --
		return *this;
	}


	Station& Station::operator+=(CustomerOrder&& order)
	{
		// puts the order at the back of queue
		m_cust_queue.push_back(std::move(order));
		return *this;
	}


	bool Station::pop(CustomerOrder& ready) 
	{
		bool filled = false;

		if (!m_cust_queue.empty()) //false
		{

			filled = m_cust_queue.front().isItemFilled(m_station_name); 
			ready = std::move(m_cust_queue.front());
			m_cust_queue.erase(m_cust_queue.begin());
		}
		return filled;
	}


	void Station::validate(std::ostream& os)const
	{
		os << " getName(): " << m_itemSet_object.getName() << std::endl;
		os << " getSerialNumber(): " << m_itemSet_object.getSerialNumber() << std::endl;
		os << " getQuantity(): " << m_itemSet_object.getQuantity() << std::endl;
	}

}