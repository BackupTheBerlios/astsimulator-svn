/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
#ifndef _ROAD_H_
#define _ROAD_H_
 
#include <list>
  
class Car;
class Junction;
 
/**
	A road in the road network.
*/
class Road {	
	private:
		Junction *start_junction, *end_junction;
		int id;
		double length;	/** Length of road is stored here */
	
	public:
		/**
			List of cars on the road.
		*/
		std::list<Car*> cars;
	
		/**
			Standard constructor.
			\param	start	Start junction
			\param	end		End junction
			\param	ID		Global ID. No collision checking is done.
		*/
		Road(Junction *start, Junction *end, int ID);
	
		/**
			Standard destructor.
		*/
		~Road();
	
		/**
			\returns the road's global ID.
		*/
		int get_id() { return id; }
		
		/**
			\returns the road's start junction.
		*/
		Junction* get_start() { return start_junction; }
		
		/**
			\returns the road's end junction.
		*/
		Junction* get_end() { return end_junction; }
		
		/**
			\returns the length of the road.
		*/
		double get_length() { return length; }
};

#endif //_ROAD_H_
