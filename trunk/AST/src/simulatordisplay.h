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
 
#ifndef _SIMULATORDISPLAY_H_
#define _SIMULATORDISPLAY_H_

#include <wx/wx.h>
#include <wx/window.h>

class Simulator;

/**
	This class is responsible for displaying the simulation.
*/

class SimulatorDisplay : public wxWindow {
	
	private:
		Simulator *simulator;
		wxTimer *timer;

	public:
		/**
			Default constructor. See wxWidgets documentation for the rest of
			the parameter documentation.
			\param	sim	The simulator to display.
		*/
		SimulatorDisplay(
			Simulator *sim,
			wxWindow *parent, 
			wxWindowID id,
			const wxPoint &pos = wxDefaultPosition,
			const wxSize &size = wxDefaultSize,
			long style = 0,
			const wxString& name = wxPanelNameStr
		);
	
		/**
			Custom paint event.
		*/
		void OnPaint(wxPaintEvent &event);
	
		/**
			Custom mouse event.
		*/
		void OnMouse(wxMouseEvent &event);
		
		/**
			Custom timer event.
		*/
		void OnTimer(wxTimerEvent &event);
	
	DECLARE_EVENT_TABLE()
};

#endif //_SIMULATORDISPLAY_H_
