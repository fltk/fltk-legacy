//
// "$Id: Fl_Choice.cxx,v 1.56 2001/07/23 09:50:04 spitzak Exp $"
//
// Choice widget for the Fast Light Tool Kit (FLTK).
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

#include <fltk/Fl.h>
#include <fltk/Fl_Choice.h>
#include <fltk/fl_draw.h>

// Set this to 1 for "classic fltk" rather than Windows style:
#define MOTIF_STYLE 0

// The dimensions for the glyph in this and the Fl_Menu_Button are exactly
// the same, so that glyphs may be shared between them.

extern bool fl_hide_shortcut;

void Fl_Choice::draw() {
  int X=0; int Y=0; int W=w(); int H=h();
#if MOTIF_STYLE
  draw_button();
  box()->inset(X,Y,W,H);
  int w1 = H*4/5;
#else
  draw_text_frame();
  text_box()->inset(X,Y,W,H);
  int w1 = H*4/5;
  fl_color(text_background());
  fl_rectf(X,Y,W-w1,H);
  if (focused()) {
    fl_color(selection_color());
    fl_rectf(X+2, Y+2, W-w1-4, H-4);
  }
#endif
  Fl_Widget* o = item();
  if (!o) o = child(0);
  if (o) {
#if MOTIF_STYLE
    o->clear_flag(FL_SELECTED);
#else
    if (focused()) o->set_flag(FL_SELECTED);
    else o->clear_flag(FL_SELECTED);
#endif
    fl_push_clip(X+2, Y+2, W-w1-2, H-4);
    int save_x = fl_x_; fl_x_ += X;
    int save_y = fl_y_; fl_y_ += Y+(H-o->height())/2;
    int save_w = o->w(); o->w(W-w1);
    fl_hide_shortcut = true;
    o->draw();
    fl_hide_shortcut = false;
    o->w(save_w);
    fl_y_ = save_y;
    fl_x_ = save_x;
    fl_pop_clip();
  }
  // draw the little mark at the right:
  Fl_Flags flags = this->flags();
  if (!active_r())
    flags |= FL_INACTIVE;
  else if (belowmouse())
    flags |= FL_HIGHLIGHT;
#if MOTIF_STYLE
  // draw the little mark at the right:
  draw_glyph(FL_GLYPH_CHOICE, X+W-w1-2, Y, w1, H, flags);
#else
#if 1
  draw_glyph(FL_GLYPH_DOWN_BUTTON, X+W-w1, Y, w1, H, flags);
#else
  // attempt to draw an up/down arrow like the Mac uses, since the
  // popup menu is more like how the Mac works:
  draw_glyph(0, X+W-w1, Y, w1, H, flags);
  int x = X+W-w1+2;
  int w = w1-4;
  int h = (w+1)/2;
  int y = Y+H/2;
  draw_glyph(FL_GLYPH_UP, x, y-h-1, w, h, flags);
  draw_glyph(FL_GLYPH_DOWN, x, y+1, w, h, flags);
#endif
#endif
}

int Fl_Choice::value(int v) {
  if (goto_item(&v, 0)) {
    redraw(); return true;
  }
  return false;
}

#if 0
int Fl_Choice::goto_item(const int* indexes, int level) {
  // rather annoying kludge to try to detect if the item from an Fl_List
  // has changed by looking for the label and user data to change:
  Fl_Widget* save_item = item();
  const char* save_label = 0;
  void* save_data = 0;
  if (save_item) {
    save_label = save_item->label();
    save_data = save_item->user_data();
  }
  Fl_Menu_::goto_item(indexes, level);
  if (item() == save_item) {
    if (!save_item) return 0;
    if (save_label == save_item->label() && save_data==save_item->user_data())
      return 0;
  }
  redraw();
  return 1;
}
#endif

static bool try_item(Fl_Choice* choice, int i) {
  Fl_Widget* w = choice->child(i);
  if (!w->takesevents()) return false;
  choice->focus(i);
  choice->execute(w);
  choice->redraw();
  return true;
}  

int Fl_Choice::handle(int e) {
  int children = this->children(0,0);
  if (!children) return 0;
  switch (e) {

  case FL_FOCUS:
  case FL_UNFOCUS:
    damage(FL_DAMAGE_HIGHLIGHT);
    return 1;

  case FL_ENTER:
  case FL_LEAVE:
    if (highlight_color() && takesevents()) damage(FL_DAMAGE_HIGHLIGHT);
  case FL_MOVE:
    return 1;

  case FL_PUSH:
    // Normally a mouse click pops up the menu. If you uncomment this line
    // (or make a subclass that does this), a mouse click will re-pick the
    // current item (it will popup the menu and immediately dismiss it).
    // Depending on the size and usage of the menu this may be more
    // user-friendly.
//  Fl::event_is_click(0);
    take_focus();
  EXECUTE:
    if (popup(0, 0, w(), h(), 0)) redraw();
    return 1;

  case FL_SHORTCUT:
    if (test_shortcut()) goto EXECUTE;
    if (handle_shortcut()) {redraw(); return 1;}
    return 0;

  case FL_KEYBOARD:
    switch (Fl::event_key()) {

    case FL_Enter:
    case ' ':
      goto EXECUTE;

    case FL_Up: {
      int i = value(); if (i < 0) i = children;
      while (i > 0) {--i; if (try_item(this, i)) return 1;}
      return 1;}
    case FL_Down: {
      int i = value();
      while (++i < children) if (try_item(this,i)) return 1;
      return 1;}
    }
    return 0;

  default:
    return 0;
  }
}

static void revert(Fl_Style* s) {
  s->leading = 4;
#if MOTIF_STYLE
  s->text_background = FL_GRAY;
#endif
}
static Fl_Named_Style style("Choice", revert, &Fl_Choice::default_style);
Fl_Named_Style* Fl_Choice::default_style = &::style;

Fl_Choice::Fl_Choice(int x,int y,int w,int h, const char *l) : Fl_Menu_(x,y,w,h,l) {
  value(0);
  style(default_style);
  clear_flag(FL_ALIGN_MASK);
  set_flag(FL_ALIGN_LEFT);
  when(FL_WHEN_RELEASE);
}

//
// End of "$Id: Fl_Choice.cxx,v 1.56 2001/07/23 09:50:04 spitzak Exp $".
//
