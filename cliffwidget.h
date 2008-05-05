/*
 *	cliffwidget.h
 *
 *	gtkmm widget for the cliff visualizer
 *
 *	Neil Mayhew - 2007-12-08
 *
 *	$Id: cliffwidget.h,v 1.1 2008-05-05 03:44:25 mayhewn Exp $
 */

#ifndef CLIFFWIDGET_H
#define CLIFFWIDGET_H

#include <gtkmm/drawingarea.h>

class CliffWidget : public Gtk::DrawingArea
{
public:
	CliffWidget();
protected:

	bool on_expose_event(GdkEventExpose*);
};

#endif //CLIFFWIDGET_H
