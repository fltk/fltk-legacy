// generated by Fast Light User Interface Designer (fluid) version 2.0001

#include "radio.h"

Fl_Light_Button* ttlb;

static void cb_ttlb(Fl_Light_Button*, void*) {
  Fl_Tooltip::enable(ttlb->value());
}

int main (int argc, char **argv) {

  Fl_Window* w;
   {Fl_Window* o = new Fl_Window(380, 274, "Radio buttons and Tooltips");
    w = o;
    o->tooltip("This is a window");
     {Fl_Button* o = new Fl_Button(20, 10, 160, 25, "Fl_Button");
      o->tooltip("This is a button");
    }
     {Fl_Return_Button* o = new Fl_Return_Button(20, 40, 160, 25, "Fl_Return_Button");
      o->shortcut(0xff0d);
      o->tooltip("This is a return button");
    }
     {Fl_Light_Button* o = new Fl_Light_Button(20, 70, 160, 25, "Fl_Light_Button");
      o->tooltip("This is a light button!  This particular light button has a very long tooltip\
.  This tooltip should demonstrate that very long tooltips are wrapped across \
multiple lines.");
    }
     {Fl_Check_Button* o = new Fl_Check_Button(20, 100, 160, 25, "Fl_Check_Button");
      o->tooltip("This is a check button");
    }
     {Fl_Round_Button* o = new Fl_Round_Button(20, 125, 160, 25, "Fl_Round_Button");
      o->tooltip("This is a round button");
    }
     {Fl_Group* o = new Fl_Group(190, 10, 70, 200);
      o->tooltip("This is a group");
       {Fl_Check_Button* o = new Fl_Check_Button(0, 0, 70, 25, "radio");
        o->type(Fl_Check_Button::RADIO);
        o->tooltip("This is a check button");
      }
       {Fl_Check_Button* o = new Fl_Check_Button(0, 25, 70, 25, "radio");
        o->type(Fl_Check_Button::RADIO);
        o->tooltip("This is a check button");
      }
       {Fl_Check_Button* o = new Fl_Check_Button(0, 50, 70, 25, "radio");
        o->type(Fl_Check_Button::RADIO);
        o->tooltip("This is a check button");
      }
       {Fl_Check_Button* o = new Fl_Check_Button(0, 75, 70, 25, "radio");
        o->type(Fl_Check_Button::RADIO);
        o->tooltip("This is a check button");
      }
       {Fl_Check_Button* o = new Fl_Check_Button(0, 100, 70, 25, "radio");
        o->type(Fl_Check_Button::RADIO);
        o->tooltip("This is a check button");
      }
       {Fl_Check_Button* o = new Fl_Check_Button(0, 125, 70, 25, "radio");
        o->type(Fl_Check_Button::RADIO);
        o->tooltip("This is a check button");
      }
       {Fl_Check_Button* o = new Fl_Check_Button(0, 150, 70, 25, "radio");
        o->type(Fl_Check_Button::RADIO);
        o->tooltip("This is a check button");
      }
       {Fl_Check_Button* o = new Fl_Check_Button(0, 175, 70, 25, "radio");
        o->type(Fl_Check_Button::RADIO);
        o->tooltip("This is a check button");
      }
      o->end();
    }
     {Fl_Group* o = new Fl_Group(270, 10, 90, 115);
      o->box(FL_THIN_UP_BOX);
      o->tooltip("This is a group");
       {Fl_Button* o = new Fl_Button(15, 10, 20, 20, "radio");
        o->type(Fl_Button::RADIO);
        o->align(FL_ALIGN_RIGHT);
        o->tooltip("This the first button of the group");
      }
       {Fl_Button* o = new Fl_Button(15, 35, 20, 20, "radio");
        o->type(Fl_Button::RADIO);
        o->align(FL_ALIGN_RIGHT);
        o->tooltip("This the second button of the group");
      }
       {Fl_Button* o = new Fl_Button(15, 60, 20, 20, "radio");
        o->type(Fl_Button::RADIO);
        o->align(FL_ALIGN_RIGHT);
        o->tooltip("This the third button of the group");
      }
       {Fl_Button* o = new Fl_Button(15, 85, 20, 20, "radio");
        o->type(Fl_Button::RADIO);
        o->align(FL_ALIGN_RIGHT);
        o->tooltip("This the fourth button of the group");
      }
      o->end();
    }
     {Fl_Light_Button* o = ttlb = new Fl_Light_Button(120, 230, 130, 30, "Show Tooltips");
      o->value(1);
      o->callback((Fl_Callback*)cb_ttlb);
      o->tooltip("This button enables or disables tooltips");
    }
    o->end();
    o->resizable(o);
  }
  w->show(argc, argv);
  return Fl::run();
}
