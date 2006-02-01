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
 
#ifndef _JUNCTION_H_
#define _JUNCTION_H_
 
#include <list>
 
class Road;
 
/**
	A junction in the road network.
*/
class Junction {
	//TODO member for right of way model
	
	private:
		int pos_x, pos_y; //position
		int id;	//global id
	
	public:
		
		/**
			Roads arriving at this junction.
		*/
		std::list<Road*> incoming_roads;
	
		/**
			Roads leaving from this junction.
		*/
		std::list<Road*> outgoing_roads;
		
		/**
			Standard constructor.
			\param	x	x coordinate
			\param	y	y coordinate
			\param	ID	Global ID. No collision detection is done.
		*/
		Junction(int x, int y, int ID);
	
		/**
			Standard destructor.
		*/
		~Junction();
	
		/**
			\returns the junction's x coordinate.
		*/		
		int get_x() { return pos_x; }
		
		/**
			\returns the junction's y coordinate.
		*/
		int get_y() { return pos_y; }
		
		/**
			Sets a new position for the junction.
			\param	x	New x coordinate.
			\param	y	New y coordiante.
		*/
		void set_position(int x, int y) { pos_x = x; pos_y = y; }
		
		/**
			\returns the junction's global ID.
		*/
		int get_id() { return id; }
};

#endif //_JUNCTION_H_
