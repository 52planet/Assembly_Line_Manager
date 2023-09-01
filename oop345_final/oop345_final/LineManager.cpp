#include <iostream>
#include <vector>
//#include <list>
#include "LineManager.h"

//namespace
namespace sict
{

	//five argument constructor
		//this constructor moves the customer orders to the front of the queue holding the orders waiting to be filled 
		//and determines the index of the last station on the line 
	LineManager::LineManager(std::vector<Station*>& station_address, std::vector<std::size_t>& next_station, std::vector<CustomerOrder>& cust_orders, std::size_t index_of_starting_station, std::ostream& os)
		:m_station_address_list(station_address), m_first_station_index(index_of_starting_station)
	{
		//push orders into not filled array
		for (auto& cust_orders: cust_orders)
		{
			m_orders_to_be_filled_queue.push_back(std::move(cust_orders)); //push unfilled order into not filled vector
		}
			//find index of last station in the line
			//store first station in order of stations vector
			m_order_of_stations.push_back(index_of_starting_station);
			//index_of_starting_station = next_station[1];

			//loop through next_station vector and store the order inside vector
			for (size_t i = 0; i < next_station.size(); ++i)
			{
				m_order_of_stations.push_back(next_station[index_of_starting_station]); //store 
				index_of_starting_station = next_station[index_of_starting_station]; //index is updated
			}
			m_last_station_on_the_line = m_order_of_stations.back(); //last station is equal to final element inside order_station vector
			m_next_station_index = next_station; //store next stations
	}

	void LineManager::display(std::ostream& os) const
	{
		os << "COMPLETED ORDERS" << std::endl;
		for (size_t i = 0; i < m_filled_orders.size(); i++) //loop through and display
		{
			m_filled_orders[i].display(os, true);
		}
		os << std::endl;
		os << "INCOMPLETE ORDERS" << std::endl;
		for (size_t j = 0; j < m_incomplete_orders.size(); j++) //loop through and display
		{
			m_incomplete_orders[j].display(os, true);
		}
	}

	bool LineManager::run(std::ostream& os)
	{
		//local variable definitions
		CustomerOrder cust_ord; //temporary customerOrder object
		static size_t size = m_orders_to_be_filled_queue.size(); //holds amount of orders

		//if there is a customer order on the back of the queue of orders waiting to be filled, this function moves it to the starting station on the line.
		if (!m_orders_to_be_filled_queue.empty()) //not empty
		{

			*m_station_address_list[m_first_station_index] += std::move(m_orders_to_be_filled_queue.front()); //calls overloaded += operator
			m_orders_to_be_filled_queue.pop_front();
		}
			//This function then executes one fill step of the asssemlby process at each station on the line, by filling the customer order at each station with one item from that station if requested.
			for (size_t i = 0; i < m_next_station_index.size(); i++)
			{
				m_station_address_list[i]->fill(os);
			}
		
			// once this filling step is done at each station, this function checks if there is a customer order to be released at each station on the line in the order in which the user has specified.
			for (size_t i = 0; i < m_station_address_list.size(); i++) //loop through all the stations 
			{
				if (m_station_address_list[i]->hasAnOrderToRelease()) //true
				{
					//If there is an order to be released, this function releases the order from the station.

					if (m_next_station_index[i] != m_last_station_on_the_line) //not last station 
					{
						// if the station is not the last station this function moves the order to the next station.
						m_station_address_list[i]->pop(cust_ord); //calls pop

						os << " --> " << cust_ord.getNameProduct() << " moved from " << m_station_address_list[i]->getName() << " to " << m_station_address_list[m_next_station_index[i]]->getName() << std::endl; //print message

						*m_station_address_list[m_next_station_index[i]] += std::move(cust_ord); //move cust_ord to the next station
					}

					if (m_next_station_index[i] == m_last_station_on_the_line) //last station
					{
						//if the station is the last one this function moves the order to the completed or incompleted  set as appropriate.
						m_station_address_list[i]->pop(cust_ord);
						if (cust_ord.isFilled()) //complete
						{
							os << " --> " << cust_ord.getNameProduct() << " moved from " << m_station_address_list[i]->getName() << " to Completed Set" << std::endl; //display message
							m_filled_orders.push_back(std::move(cust_ord)); //push order into completed set
							size--; //subtract from the total amount of orders
						}
						else //incomplete
						{
							os << " --> " << cust_ord.getNameProduct() << " moved from " << m_station_address_list[i]->getName() << " to Incompleted Set" << std::endl; //display message
							m_incomplete_orders.push_back(std::move(cust_ord)); //push order into incompleted set
							size--; //subtract from the total amount of orders

						}
					}
				}
			}
		
		if (size == 0) //if no orders need to filled
		{
			return true;
		}
		else
		{
			return false;
		}

	}


}