//
// "$Id: draw.cxx,v 1.1.2.1 2004/03/28 10:30:31 rokan Exp $"
//
// Text drawings for WIN32 GDI printing device for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2004 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to http://www.fltk.org/str.php
//

#include <FL/Fl_GDI_Printer.H>
#include "../win/Fl_Win_Display.H"
extern Fl_Win_Display fl_disp;

void Fl_GDI_Printer::draw(const char* str, int n, int x, int y){
  fl_disp.draw(str, n, x, y);
};

//
// End of "$Id: draw.cxx,v 1.1.2.1 2004/03/28 10:30:31 rokan Exp $"
//
