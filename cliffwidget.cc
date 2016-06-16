/*
 *	cliffwidget.cc
 *
 *	gtkmm widget for the cliff visualizer
 *
 *	Neil Mayhew - 2007-12-08
 *
 *	$Id: cliffwidget.cc,v 1.4 2009-03-14 03:04:24 mayhewn Exp $
 */

#include "cliffwidget.h"
#include "cliffcairo.h"

#include <gdkmm/window.h>
#include <gdkmm/general.h>

CliffWidget::CliffWidget()
{
	set_size_request(100, 100);
}

bool CliffWidget::on_expose_event(GdkEventExpose* event)
{
	Glib::RefPtr<Gdk::Window> window = get_window();
    Gtk::Allocation allocation = get_allocation();

	if (!window)
		return true;

	Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

	double velocity = 20.0;      // m/s
	double height = 50.0;        // m
	double size_x = (double)allocation.get_width();
	double size_y = (double)allocation.get_height();

    cr->rectangle(0, 0, size_x, size_y);
    cr->set_source_rgb(1.0, 1.0, 1.0);
    cr->fill();

	render(cr, velocity, height, size_x, size_y);

	return true;
}
