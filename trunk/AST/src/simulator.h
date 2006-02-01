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
 
 #ifndef _SIMULATOR_H_
 #define _SIMULATOR_H_
 
/**
	The Simulator class should once do all necessary simulations.
*/

#include <list>
#include <map>
#include <string>

#include "car.h"
#include "road.h"
#include "junction.h"

typedef std::pair<int,void*> id_map_entry;

class Simulator {
	
	private:
		
			/**
				Global ID map.
			*/
			std::map<int,void*> id_map;
			int last_id;
	
			/**
				Allows you to register an object with a specified ID.
				\param	object	Object to register
				\param	id		ID to use
				\throws an std::invalid_argument exception if the ID is already taken
			*/
			void register_object(void *object, int id);
	
			/**
				Empties the ID map and the car, road and junction lists and
				frees the objects in them.
			*/
			void empty_lists();
	/* TODO: Why public? */
	public:
			/**
				Global car list. The simulator will take care of
				freeing all cars in the list on exit.
			*/
			std::list<Car*> cars;
	
			/**
				Global road list. The simulator will take care of
				freeing all roads in the list on exit.
			*/
			std::list<Road*> roads;
	
			/**
				Global junction list. The simulator will take care of
				freeing all junctions in the list on exit.
			*/
			std::list<Junction*> junctions;
	
	
			/**
				Standard constructor.
			*/
			Simulator();
			
			/**
				Standard desconstructor. Will free all cars, roads and 
				junctions int the global lists.
			*/
			~Simulator();
			
			/**
				Registers an object with the ID map. 
				\param	object	Object to register
				\returns the new ID.
				TODO exception
			*/
			int register_object(void *object);
			
			/**
				Unregisters an object from the ID map. 
				\param	ID	ID to unregister
				TODO exception
			*/
			void unregister_object(int id);
			
			/**
				Looksup an ID in the ID map.
				\param	id	ID to lookup
				\returns the object registered with the ID or NULL if there's no such object.
			*/
			void *id_to_object(int id);
			
			/**
				Saves the simulator state into a file.
				\param	filename	File to save state in
			*/
			void save_to_file(std::string filename);
			
			/**
				Loads the simulator state from a file.
				\param	filename	File to load state from
				\throws a std::invalid_argument exception if the file can't be loaded.
			*/
			void load_from_file(std::string filename);
			
			/**
				Performs a simulation step of the given time length.
				\param	t	Length of simulation step
				TODO what unit is t in?
			*/
			void step(double t);
};

#endif //_SIMULATOR_H_
