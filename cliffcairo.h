/*
 *	cliffcairo.h
 *
 *	Cairo renderer for the cliff visualizer
 *
 *	Neil Mayhew - 2007-12-08
 *
 *	$Id: cliffcairo.h,v 1.1 2009-03-14 02:23:10 mayhewn Exp $
 */

#ifndef CLIFFCAIRO_H
#define CLIFFCAIRO_H

#include <cairomm/context.h>

void render(
	Cairo::RefPtr<Cairo::Context> cr,
	double velocity, double height, // m/s, m
	double size_x, double size_y);  // pixels

#endif //CLIFFCAIRO_H
