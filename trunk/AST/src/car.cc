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
 
#include <iostream>
#include <list>
 
#include "car.h"
#include "road.h"
#include "junction.h"

/*
	HELPERS
*/

#define MAX(x,y) (x>y ? x : y)
#define MIN(x,y) (x<y ? x : y)

/*
	PHYSIC CONSTANTS
*/
#define CAR_MASS 1000
#define MAX_ACCELERATION 1.0
#define MIN_ACCELERATION -1.0
#define MAX_SPEED 60

/*
	BEHAVIOUR CONSTANTS
*/
/*
	An object (junction, car, ...) is taken to be an obstacle, if the
	time in which it was reached is smaller than OBSTACLE_AVOIDANCE_TIME (In 
	this case the car tries to avoid the obstacle by changing lane, braking, 
	etc.). If the time is even smaller than CRASH_AVOIDANCE_TIME full braking
	is applied.
*/
#define OBSTACLE_AVOIDANCE_TIME 15
#define CRASH_AVOIDANCE_TIME 3



Car::Car(Road *r, double pos, double sp, int ID) {
	road = r;
	new_road = r;
	
	position = pos;
	new_position = pos;
	
	speed = sp;
	new_speed = sp;
	
	//TODO pass these as parameters
	acceleration = 0;
	new_acceleration = 0;
	
	id = ID;
}

void
Car::steer(double t) {
	/*
		position, speed and acceleration are the values which
		our car posesses NOW.		
	*/
	
	float length = road->get_length();	
	
	/*
		CHECK FOR OBSTACLES:
		Time to reach an obstacle:
		distance_to_obstacle/(own_speed - obstacle_speed)
	*/
	void *obstacle_obj = NULL;
	double obstacle_time = OBSTACLE_AVOIDANCE_TIME;
	double ot;
	
	ot = (length-position)/speed;
	//check end of road
	if (ot < obstacle_time) {
		//end of road is an obstacle
		obstacle_time = ot;
		obstacle_obj = road->get_end();
	}
	//check cars on road
	std::list<Car*>::iterator it;
	for (it=road->cars.begin(); it!=road->cars.end(); it++) {
		double car_pos = (*it)->get_position();
		if (car_pos>position) {
			double car_speed = (*it)->get_speed();
			ot = (car_pos-position)/(speed-car_speed);
			if (ot>0 && ot<obstacle_time) {
				//this car is an obstacle
				obstacle_time = ot;
				obstacle_obj = (*it);
			}
		}
	}
		
	/*
		Obstacle avoidance?
	*/
	if (obstacle_time<OBSTACLE_AVOIDANCE_TIME) {
		//Attention: Obstacle ahead!
		new_acceleration = -100;
		if (obstacle_time<CRASH_AVOIDANCE_TIME) {std::cout << "New speed = " << new_speed << std::endl;
			//Attention: Crash ahead!
			//TODO full braking
		} else {
			//TODO braking or lane changing						
		}
	} else {
		//Free way!		
	}
	
	
	/*
		Calculate next position
	*/		
	std::cout << "New acceleration = " << new_acceleration << std::endl;
	new_speed = MAX(0,MIN(speed + new_acceleration*t,MAX_SPEED));
	std::cout << "New speed = " << new_speed << std::endl;
	new_position = position + new_speed;
	std::cout << "New position = " << new_position << std::endl;
}

void
Car::commit() {	
	if (road != new_road) {
		road->cars.remove(this);
		new_road->cars.push_back(this);
		road = new_road;
	}	
	position = new_position;
	speed = new_speed;
	acceleration = new_acceleration;
}
