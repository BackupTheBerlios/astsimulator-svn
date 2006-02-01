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
 
#include "simulatordisplay.h"
#include "simulator.h"

#include <list>
#include <iostream>

BEGIN_EVENT_TABLE(SimulatorDisplay,wxWindow)
	EVT_PAINT(SimulatorDisplay::OnPaint)
	EVT_MOUSE_EVENTS(SimulatorDisplay::OnMouse)
	EVT_TIMER(1,SimulatorDisplay::OnTimer)
END_EVENT_TABLE()

SimulatorDisplay::SimulatorDisplay(
	Simulator *sim,
	wxWindow *parent, 
	wxWindowID id,
	const wxPoint &pos,
	const wxSize &size,
	long style,
	const wxString& name
) : wxWindow(parent,id,pos,size,style,name) {
		
	simulator = sim;
	timer = new wxTimer(this,1);
	timer->Start(200,wxTIMER_CONTINUOUS);
}
	

void
SimulatorDisplay::OnPaint(wxPaintEvent &event) {	
	
	wxPaintDC dc(this);
	
	//draw roads and cars
	dc.SetBrush(*wxRED_BRUSH);
	std::list<Road*>::iterator r_it = simulator->roads.begin();
	for (; r_it!=simulator->roads.end(); r_it++) {		
		Junction *start = (*r_it)->get_start();
		Junction *end = (*r_it)->get_end();
		
		int start_x = start->get_x();
		int start_y = start->get_y();
		int end_x = end->get_x();
		int end_y = end->get_y();
	
		//draw road
		dc.SetPen(*wxBLACK_PEN);
		dc.DrawLine(start_x,start_y,end_x,end_y);
		
		//draw cars
		dc.SetPen(*wxRED_PEN);		
		std::list<Car*>::iterator c_it = (*r_it)->cars.begin();
		float length = (*r_it)->get_length();
		for (; c_it!=(*r_it)->cars.end(); c_it++) {
			double pos = (*c_it)->get_position()/length;
			int x = (int)(start_x + pos*(end_x - start_x));
			int y = (int)(start_y + pos*(end_y - start_y));
			dc.DrawCircle(x,y,2);
		}
	}
	
	//draw junctions
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(*wxBLACK_BRUSH);
	std::list<Junction*>::iterator j_it = simulator->junctions.begin();
	for (; j_it!=simulator->junctions.end(); j_it++) {
		dc.DrawRectangle((*j_it)->get_x()-2,(*j_it)->get_y()-2,4,4);
	}
}

void
SimulatorDisplay::OnMouse(wxMouseEvent &event) {
}

void
SimulatorDisplay::OnTimer(wxTimerEvent &event) {
	simulator->step(0.1);
	Refresh();
}
