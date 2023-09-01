#pragma once
//contains all the functionality for filling customer orders with items
//each station that has an order can fill one request at a time for an item from that station
//an order can be incomplete due to insufficient items in stock to cover requests
//manages a set of identical items (not serial number) and processes a queue of customer orders
//each station object is unique
//each station contains a customerOrder queue and an itemSet sub-object
//fills request from the items in its itemSet sub-object
//The name of a station object is the name of the itemSet sub object

//Luke Belch
//
//
//

//#includes
#include <iostream>
#include <vector>
//#file includes
#include "CustomerOrder.h"

//namespace
namespace sict {

	//class definition

	class Station
	{

	private:
		//station class private members

		//name of station
		std::string m_station_name;
		//customer queue
		std::vector<CustomerOrder> m_cust_queue;
		//itemset sub-object
		ItemSet m_itemSet_object;

	public:

		//one argument constructor
		Station(const std::string&);

		//displays data for its ItemSet on os
		void display(std::ostream& os)const;

		//fills the last order in the customer order queue, if there is one, else do nothing
		void fill(std::ostream& os);

		//a forwarding query that returns a reference to the name of the itemSet sub-object
		const std::string& getName() const;

		//query that returns the release state of the current object. returns true if the station has filled the item request(s)
		//for the customer order at the front of the queue or the station has no items left; else return false. no orders = false
		bool hasAnOrderToRelease() const;

		//modifier decrements the number of items in the itemSet, increments the serial number for the next item, return current object
		Station& operator--();

		//recieves a right hand refernece value of an order and moves that order to the back of the stations queue returns reference to the current object
		Station& operator+=(CustomerOrder&& order);

		//removes the order at the front of the queue and moves it to the calling function through the parameter list
		//returns true if station filled its part of the order else false
		bool pop(CustomerOrder& ready);

		//reports the state of the itemSet object in a format
		void validate(std::ostream& os)const;

		//deleted functions
		//Station(const Station&) = delete;
		//Station& operator=(const Station&) = delete;
		//Station(Station&&) = delete;
		//Station& operator=(Station&&) = delete;

	};

}