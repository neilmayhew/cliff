/*
 *	cliffwindow.h
 *
 *	gtkmm window for the cliff visualizer
 *
 *	Neil Mayhew - 2007-12-08
 *
 *	$Id: cliffwindow.h,v 1.1 2008-05-05 03:44:25 mayhewn Exp $
 */

#ifndef CLIFFWINDOW_H
#define CLIFFWINDOW_H

#include <gtkmm.h>

#include "cliffwidget.h"

class CliffWindow : public Gtk::Window
{
public:
	CliffWindow();
protected:
	Gtk::VBox m_VBox;
	Gtk::Frame m_Frame;
	Gtk::HButtonBox m_ButtonBox;
	Gtk::Button m_Button_Quit;

	CliffWidget m_CliffWidget;
};

#endif //CLIFFWINDOW_H
