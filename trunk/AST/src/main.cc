/* Created by Anjuta version 1.2.4 */
/*	This file will not be overwritten */

#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif //HAVE_CONFIG_H
#include <wx/wx.h>

#include <iostream>
#include <fstream>
#include <string>

#include "simulatordisplay.h"
#include "simulator.h"



class MyApp : public wxApp {
	private:
		Simulator *simulator;
	
	public:
		virtual bool OnInit();		
		virtual int OnExit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
	
	simulator = new Simulator;
	simulator->load_from_file("/home/jreinhardt/sources/ast/AST/data/test01.ast");
	
	wxFrame *frame = new wxFrame(NULL,-1,"AST",wxPoint(-1,-1),wxSize(400,400));
	
	SimulatorDisplay *display = new SimulatorDisplay(
		simulator,
		frame,
		-1,
		wxPoint(0,0),
		wxSize(300,300)
	);
	
	frame->Show(true);
	SetTopWindow(frame);
	
	return true;
}

int MyApp::OnExit() {
	delete simulator;
	
	return 0;
}

/*
#include "simulator.h"

int main(int argc, char* argv[]) {
	std::cout << "It's running" << std::endl;
	Simulator simulator;
	simulator.load_from_file("/home/torf/coding/anjuta/AST/data/test01.ast");
}
*/
