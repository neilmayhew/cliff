/*
 *	cliffwidget.cc
 *
 *	gtkmm widget for the cliff visualizer
 *
 *	Neil Mayhew - 2007-12-08
 *
 *	$Id: cliffwidget.cc,v 1.2 2008-11-09 03:38:04 mayhewn Exp $
 */

#include "cliffwidget.h"

#include <gdkmm/drawable.h>
#include <gdkmm/general.h>

#include <cmath>
#include <iostream>
#include <sstream>

const double g = 9.80665; // Exact, defined 1901 by CGPM

inline double degrees(double x) { return x / M_PI * 180.0; }
inline double radians(double x) { return x * M_PI / 180.0; }

double ascent(double a, double v)
{
	v *= std::sin(a);

	return 0.5 * v * v / g;
}

double distance(double a, double v, double h)
{
	double c = std::cos(a);
	double s = std::sin(a);

	return v * v * c / g * (s + std::sqrt(s * s + 2.0 * g * h / (v * v)));
}

double optimum(double v, double h)
{
	return std::asin(v * std::sqrt(0.5 / (v * v + g * h)));
}

void trajectory(Cairo::RefPtr<Cairo::Context> cr,
	double v, double a, double max_x, double min_y)
{
	double vx = v * std::cos(a);
	double vy = v * std::sin(a);

	double x = 0.0;
	double y = 0.0;
	double t = 0.0;

	cr->move_to(x, -y);

	while (x <= max_x && y >= min_y)
	{
		t += (2.0 / v); // About every 2m
		x = vx * t;
		y = vy * t - 0.5 * g * t * t;
		cr->line_to(x, -y);
	}
}

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
	double angle = optimum(velocity, height); // radians
	double width = distance(angle, velocity, height);
	double upper = ascent(M_PI / 4, velocity);
	
	double min_y = -height * 1.5;
	double max_y = upper;
	double min_x = 0;
	double max_x = distance(angle, velocity, -min_y);

	double scale_x = (double)allocation.get_width()  / (max_x - min_x);
	double scale_y = (double)allocation.get_height() / (max_y - min_y);
	double scale = std::min(scale_x, scale_y);
	
	cr->translate(0, allocation.get_height());
	cr->scale(scale, scale);
	cr->translate(0, min_y);
	
	max_x = allocation.get_width() / scale;
	max_y = allocation.get_height() / scale + min_y;

	// Horizontals & verticals
	cr->move_to(0.0, 0.0);
	cr->line_to(max_x, 0.0);
	cr->move_to(0.0, height);
	cr->line_to(max_x, height);
	cr->move_to(width, -max_y);
	cr->line_to(width, -min_y);
	cr->set_source_rgb(0.5, 0.5, 0.5);
	cr->set_line_width(1.0 / scale); // One pixel
	cr->stroke();

	// Sidelines
	double spread = M_PI / 4 - angle;
	double step = spread / 5;
	for (double pval = spread; pval > 0.001; pval -= step)
	{
		trajectory(cr, velocity, angle - pval, max_x, min_y);
		cr->set_source_rgb(1.0, 0.0, 0.0);
		cr->set_line_width(1.0 / scale);
		cr->stroke();
		trajectory(cr, velocity, angle + pval, max_x, min_y);
		cr->set_source_rgb(0.0, 1.0, 0.0);
		cr->set_line_width(1.0 / scale);
		cr->stroke();
	}

	// Optimum
	trajectory(cr, velocity, angle, max_x, min_y);
	cr->set_source_rgb(0.0, 0.0, 1.0);
	cr->set_line_width(1.0 / scale); // One pixel
	cr->stroke();

#if 0
	// Chord
	cr->move_to(0, 0);
	cr->line_to(width, height);
	cr->set_source_rgb(0.25, 0.25, 0.867);
	cr->stroke();
#endif

	return true;
}
