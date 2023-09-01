#pragma once
//Contains all the functionality for processing customer orders across the entire assembly line. The line manager moves orders
//along the assembly line one step at a time. At each step, each station fills one order. The manager moves orders that are
//ready from station to station. Once an order has reached the end of the line, it is either completed or incompleted
//an order can be incomplete due to insufficient items in stock to cover the request

//Luke Belch
//
//
//

//#includes
#include <iostream>
#include <vector>
#include <deque>
//#file includes
#include "CustomerOrder.h"
#include "Station.h"
//namespace
namespace sict {

//class definition

	class LineManager
	{

	private:
		// private data members
		std::vector<Station*> m_station_address_list;
		//std::vector<CustomerOrder> m_not_filled_orders; //holds non filled orders
		std::vector<CustomerOrder> m_incomplete_orders; //holds orders that did not get filled by the end of run
		std::vector<CustomerOrder> m_filled_orders; //holds filled orders
		std::deque<CustomerOrder> m_orders_to_be_filled_queue; //holds orders to be filled
		std::vector<size_t> m_order_of_stations; //holds the order of the stations
		std::vector<size_t> m_next_station_index; //holds the next station index's
		size_t m_first_station_index;
		size_t m_last_station_on_the_line;
	public:
		//five argument constructor
		//this constructor moves the customer orders to the front of the queue holding the orders waiting to be filled 
		//and determines the index of the last station on the line 
		LineManager(std::vector<Station*>&, std::vector<std::size_t>&, std::vector<CustomerOrder>&, std::size_t, std::ostream&);
		
		//query  displays the completed and incomplete orders at the end of the line
		void display(std::ostream& os) const;

		//if there is a customer order on the back of the queue of orders waiting to be filled, this function moves
		//it to the starting station on the line. This function then executes one fill step of the asssemlby process
		//at each station on the line, by filling the customer order at each station with one item from that station if
		//requested. once this filling step is done at each station, this function checks if there is a customer order to
		//be released at each station on the line in the order in which the user has specified. If there is an order
		//to be released, this function releases the order from the station. if the station is not the last station
		// this function moves the order to the next station. if the station is the last one this function moves the order to 
		//the completed or incompleted  set as appropriate.
		bool run(std::ostream& os);


	};

}