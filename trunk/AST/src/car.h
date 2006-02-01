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
 
/**
	The Car class will be the base class for any vehicle which can be placed
	in the system.
*/

#ifndef _CAR_H_
#define _CAR_H_

class Road;

class Car {
	private:
		Road *road;	/** The road we're driving on */				
		double position;	/** Position on street. */
		double speed;	/** Speed on street. */
		double acceleration;	/** Current acceleration */
		int id;		/** Global ID **/
	
		//Result of steering is saved here
		Road *new_road;
		double new_position, new_speed, new_acceleration;
	
	public:
	
		/**
			Standard constructor.
			\param	r	The road the car is driving on.
			\param	pos	Position on the road.
			\param	sp	Spped on the road.
			\param	ID	Global ID. No collision detecion is done.
		*/
		Car(Road *r, double pos, double sp, int ID);
	
		/**
			Performs the steering logic. The result of this will be saved
			internally and is committed back into the simulator system by
			calling commit().
			\param	t	Time interval
		*/
		void steer(double t);
	
		/**
			Commits new location computed by steer() into the simulator system.
			Calling this function without calling steer() before is safe
			(nothing will be done).
		*/
		void commit();
	
		
		/**
			\returns the car's position.
		*/
		double get_position() { return position; }
				
		/**
			\returns the road the car is driving on.
		*/
		Road *get_road() { return road; }		
		
		/**
			\returns the speed of the car.
		*/
		double get_speed() { return speed; }
		
};

#endif //_CAR_H_
