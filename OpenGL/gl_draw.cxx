//
// "$Id: gl_draw.cxx,v 1.14 2001/07/23 09:50:03 spitzak Exp $"
//
// OpenGL drawing support routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

// Functions from <fltk/gl.h>
// See also Fl_Gl_Window and gl_start.C

#include <config.h>
#if HAVE_GL

#include <fltk/fl_draw.h>
#include <fltk/gl.h>
#include "Fl_Gl_Choice.h"
#include "../src/Fl_FontSize.h"
#include <string.h>

int gl_height() {return fl_height();}
int gl_descent() {return fl_descent();}
int gl_width(const char* s) {return fl_width(s);}
int gl_width(const char* s, int n) {return fl_width(s,n);}
int gl_width(uchar c) {return fl_width(c);}

void  gl_font(Fl_Font pFont, int size) {
  fl_font(pFont, size);
  if (!fl_fontsize->listbase) {
#ifdef WIN32
    int base = fl_fontsize->metr.tmFirstChar;
    int size = fl_fontsize->metr.tmLastChar-base+1;
    HFONT oldFid = (HFONT)SelectObject(fl_gc, (HFONT)fl_fontsize->font);
    fl_fontsize->listbase = glGenLists(256);
    wglUseFontBitmaps(fl_gc, base, size, fl_fontsize->listbase+base); 
    SelectObject(fl_gc, oldFid);
#else
    // CET - FIXME - this won't work if not using the normal X font renderer--
    // CET - FIXME - that is, if using the Xft library renderer plugin!
    // WAS: probably the fix is to have the above fl_font call call the
    // non-Xft (ie older) implementation directly.
    int base = ((XFontStruct*)fl_xfont)->min_char_or_byte2;
    int size = ((XFontStruct*)fl_xfont)->max_char_or_byte2-base+1;
    fl_fontsize->listbase = glGenLists(256);
    glXUseXFont(((XFontStruct*)fl_xfont)->fid, base, size, fl_fontsize->listbase+base);
#endif
  }
  glListBase(fl_fontsize->listbase);
}

void  gl_font(int fontid, int size) {
  Fl_Font pFont = fl_fonts + (fontid % 16);
  gl_font(pFont,size);
}

void gl_draw(const char* str, int n) {
  glCallLists(n, GL_UNSIGNED_BYTE, str);
}

void gl_draw(const char* str, int n, int x, int y) {
  glRasterPos2i(x, y);
  gl_draw(str, n);
}

void gl_draw(const char* str, int n, double x, double y) {
  glRasterPos2f((float)x, (float)y);
  gl_draw(str, n);
}

void gl_draw(const char* str) {
  gl_draw(str, strlen(str));
}

void gl_draw(const char* str, int x, int y) {
  gl_draw(str, strlen(str), x, y);
}

void gl_draw(const char* str, double x, double y) {
  gl_draw(str, strlen(str), x, y);
}

#if 0
static void gl_draw_invert(const char* str, int n, int x, int y) {
  glRasterPos2i(x, -y);
  gl_draw(str, n);
}

// This is unimplemented because the fl_draw that takes a function to
// call has been eliminated. The plan is to use Fl_Renderer and make
// an OpenGL one.
void gl_draw(
  const char* str, 	// the (multi-line) string
  int x, int y, int w, int h, 	// bounding box
  Fl_Align align) {
  fl_draw(str, x, -y-h, w, h, align, gl_draw_invert);
}
#endif

void gl_measure(const char* str, int& x, int& y) {fl_measure(str,x,y,0);}

void gl_rect(int x, int y, int w, int h) {
  if (w < 0) {w = -w; x = x-w;}
  if (h < 0) {h = -h; y = y-h;}
  glBegin(GL_LINE_STRIP);
  glVertex2i(x+w-1, y+h-1);
  glVertex2i(x+w-1, y);
  glVertex2i(x, y);
  glVertex2i(x, y+h-1);
  glVertex2i(x+w, y+h-1);
  glEnd();
}

#if HAVE_GL_OVERLAY
extern bool fl_overlay;
#ifdef WIN32
extern int fl_overlay_depth;
#endif
#endif

void gl_color(Fl_Color i) {
#if HAVE_GL_OVERLAY
#ifndef WIN32
  if (fl_overlay) {glIndexi(int(fl_xpixel(i))); return;}
#else
  if (fl_overlay && fl_overlay_depth) {
    i = fl_nearest_color(i); // convert to 8-bit color
    if (fl_overlay_depth < 8) {
      // only black & white produce the expected colors.  This could
      // be improved by fixing the colormap set in Fl_Gl_Overlay.cxx
      unsigned size = 1<<fl_overlay_depth;
      if (!i) glIndexi(size-2);
      else if (i >= size-2) glIndexi(size-1);
      else glIndexi(i);
    } else {
      glIndexi(i ? i : FL_GRAY_RAMP);
    }
    return;
  }   
#endif
#endif
  Fl_Color c = fl_get_color(i);
  glColor3ub((uchar)(c>>24), (uchar)(c>>16), (uchar)(c>>8));
}
  
void gl_draw_image(const uchar* b, int x, int y, int w, int h, int d, int ld) {
  if (!ld) ld = w*d;
  glPixelStorei(GL_UNPACK_ROW_LENGTH, ld/d);
  glRasterPos2i(x,y);
  glDrawPixels(w,h,d<4?GL_RGB:GL_RGBA,GL_UNSIGNED_BYTE,(const ulong*)b);
}

#endif

//
// End of "$Id: gl_draw.cxx,v 1.14 2001/07/23 09:50:03 spitzak Exp $".
//
