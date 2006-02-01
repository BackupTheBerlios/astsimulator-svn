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
 
#include <cmath>
 
#include "road.h"
#include "car.h"
#include "junction.h"


Road::Road(Junction *start, Junction *end, int ID) {
	start_junction = start;
	end_junction = end;
	id = ID;	
	
	length = sqrt( 
		pow(end->get_x()-start->get_x(),2) + pow(end->get_y()-start->get_y(),2)
	);
}

Road::~Road() {
}
