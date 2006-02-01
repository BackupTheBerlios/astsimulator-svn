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
 
#include "simulator.h"

#include <iostream>
#include <stdexcept>
#include <limits>

#include "tinyxml.h"

Simulator::Simulator() {
	last_id = -1;
}

Simulator::~Simulator() {
	empty_lists();
}

void
Simulator::empty_lists() {
	std::cout << "(Simulator) emptying lists... ";
	
	//Empty ID Map
	id_map.clear();
	last_id = -1;
	
	//Empty car list
	std::list<Car*>::iterator car_it = cars.begin();
	while(car_it!=cars.end()) {
		delete (*car_it);	//Free car
		car_it = cars.erase(car_it);	//Remove from list
		
	}
	
	//Empty road list
	std::list<Road*>::iterator road_it = roads.begin();
	while(road_it!=roads.end()) {
		delete (*road_it);	//Free road
		road_it = roads.erase(road_it);	//Remove from list		
	}
	
	//Empty junction list
	std::list<Junction*>::iterator junction_it = junctions.begin();
	while(junction_it!=junctions.end()) {
		delete (*junction_it);	//Free junction
		junction_it = junctions.erase(junction_it);	//Remove from list		
	}
	
	std::cout << "ok" << std::endl;
}

void
Simulator::register_object(void *object, int id) {
	if (id_map.find(id)!=id_map.end()) {
		throw std::invalid_argument("ID already taken");
	}
	id_map.insert(id_map_entry(id,object));
}

int
Simulator::register_object(void *object) {
	//Find a free ID
	int id = last_id+1;
	while (id_map.find(id) != id_map.end()) { 
		if (id<INT_MAX-1) {			
			id++; 
		} else {
			id = 0;
		}
		if (id == last_id) {
			//checked all IDs
			throw std::invalid_argument("No free IDs");
		}
	}
	last_id = id;
	id_map.insert(id_map_entry(id,object));
	std::cout << "Registering " << object << " as " << id << std::endl;	
	return id;
}

void
Simulator::unregister_object(int id) {
	id_map.erase(id);
}

void*
Simulator::id_to_object(int id) {
	std::map<int,void*>::iterator it = id_map.find(id);
	if (it==id_map.end()) {
		return NULL;
	} else {
		return (*it).second;
	}
}


void
Simulator::save_to_file(std::string filename) {
	throw std::logic_error("NOT IMPLEMENTED");
}

void
Simulator::load_from_file(std::string filename) {
		
	empty_lists(); //Remove old simulation
	
	TiXmlDocument doc(filename);

	if (!doc.LoadFile()) {
		throw std::invalid_argument(doc.ErrorDesc());		
	}
	
	TiXmlElement *el_root = doc.RootElement();
	if (el_root == NULL) { 
		throw std::invalid_argument("Missing 'ast' element");		
	}	
	TiXmlElement *el_sim = el_root->FirstChildElement("simulator");
	if (el_sim == NULL) { 
		throw std::invalid_argument("Missing 'ast/simulator' element");		
	}	
	TiXmlElement *el_junctions = el_sim->FirstChildElement("junctions");
	if (el_junctions == NULL) {
		throw std::invalid_argument("Missing 'ast/simulator/junctions' element");
	}
	TiXmlElement *el_roads = el_sim->FirstChildElement("roads");
	if (el_roads == NULL) {
		throw std::invalid_argument("Missing 'ast/simulator/roads' element");
	}
	TiXmlElement *el_cars = el_sim->FirstChildElement("cars");
	if (el_cars == NULL) {
		throw std::invalid_argument("Missing 'ast/simulator/cars' element");
	}
	
	//Load junctions
	TiXmlElement *el_junction = el_junctions->FirstChildElement("junction");
	while (el_junction!=NULL) {
		int x,y,id;
		el_junction->Attribute("x",&x);
		el_junction->Attribute("y",&y);
		el_junction->Attribute("id",&id);	
		Junction *junction = new Junction(x,y,id);
		try {
			register_object(junction,id);
		} catch(...) {
			delete junction;
			throw std::invalid_argument("ID already taken");
		}
		std::cout << "Loaded junction " << id << " at " << x << ", " << y << std::endl;
		junctions.push_back(junction);
		
		el_junction = el_junction->NextSiblingElement("junction");
	}
	
	//Load roads
	TiXmlElement *el_road = el_roads->FirstChildElement("road");
	while (el_road!=NULL) {
		int start_id,end_id,id;
		el_road->Attribute("start",&start_id);
		el_road->Attribute("end",&end_id);
		el_road->Attribute("id",&id);
		Junction *start = (Junction*)id_to_object(start_id);		
		Junction *end = (Junction*)id_to_object(end_id);
		if (start==NULL || end==NULL) {
			throw std::invalid_argument("Invalid start/end ID in road");
		}
		Road *road = new Road(start,end,id);
		try {
			register_object(road,id);
		} catch(...) {
			delete road;
			throw std::invalid_argument("ID already taken");
		}
		start->outgoing_roads.push_back(road);
		end->incoming_roads.push_back(road);
		roads.push_back(road);
		std::cout << "Loaded Road " << id << " from " << start_id << " to " << end_id << std::endl;
		
		
		el_road = el_road->NextSiblingElement("road");
	}
	
	//Load cars
	TiXmlElement *el_car = el_cars->FirstChildElement("car");
	while (el_car!=NULL) {
		int road_id,id;
		double position, speed;
		el_car->Attribute("road",&road_id);
		el_car->Attribute("position",&position);
		el_car->Attribute("speed",&speed);
		el_car->Attribute("id",&id);
		Road *road = (Road*)id_to_object(road_id);				
		if (road==NULL) {
			throw std::invalid_argument("Invalid road ID in car");
		}
		Car *car = new Car(road,position,speed,id);
		try {
			register_object(car,id);
		} catch(...) {
			delete car;
			throw std::invalid_argument("ID already taken");
		}
		road->cars.push_back(car);
		cars.push_back(car);
		std::cout << "Loaded Car " << id << " on " << road_id << " at " << position << std::endl;
			
		el_car = el_car->NextSiblingElement("car");
	}
}

void
Simulator::step(double t) {	
	//TODO the simulator should save the last time of update itself
	
	std::list<Car*>::iterator it;
	
	//Allow each car to steer
	for (it=cars.begin(); it!=cars.end(); it++) {
		(*it)->steer(t);
	}
	
	//Commit new data into simulation
	for (it=cars.begin(); it!=cars.end(); it++) {
		(*it)->commit();
	}
}
