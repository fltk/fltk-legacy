// "$Id: ReturnButton.h,v 1.4 2004/11/12 06:50:13 spitzak Exp $"
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".

#ifndef fltk_ReturnButton_h
#define fltk_ReturnButton_h

#include "Button.h"

namespace fltk {

class FL_API ReturnButton : public Button {
public:
  ReturnButton(int x,int y,int w,int h,const char *l=0);
  static NamedStyle* default_style;
protected:
  void draw();
};

}

#endif

// End of "$Id: ReturnButton.h,v 1.4 2004/11/12 06:50:13 spitzak Exp $".