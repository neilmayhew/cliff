/*
 *	cliffwindow.cc
 *
 *	gtkmm window for the cliff visualizer
 *
 *	Neil Mayhew - 2007-12-08
 *
 *	$Id: cliffwindow.cc,v 1.1 2008-05-05 03:44:25 mayhewn Exp $
 */

#include "cliffwindow.h"

CliffWindow::CliffWindow() :
	m_Button_Quit("Quit")
{
	set_title("Cliff Visualizer");
	set_default_size(600, 650);

	add(m_VBox);
	
	m_VBox.set_spacing(6);
	m_VBox.set_border_width(6);

	m_VBox.pack_start(m_Frame, Gtk::PACK_EXPAND_WIDGET);
	m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);
	
	m_Frame.add(m_CliffWidget);
	m_Frame.set_shadow_type(Gtk::SHADOW_IN);

	m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
	m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);

	m_Button_Quit.signal_clicked().connect(
		sigc::mem_fun(*this, &CliffWindow::hide));

	show_all_children();
}
