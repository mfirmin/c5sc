//
// "$Id: input.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// Input field test program for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

#include "controller.h"
#include "fltk.h"

Fl_Window* fltkWindow;


Fl_Choice* scriptsWindow;
Fl_Button *b;
Fl_Box *text;


bool reset;
bool pause_sim;
bool load;
int nextScriptNum;

std::string toggleVis;
std::string toggleCol;

std::vector<std::string> names;

bool checkPause()
{
    /*
    if (pause_sim)
    {
        pause_sim = false;
        return true;
    }
    return false;
    */
    return pause_sim;
}

int checkLoad()
{

    if (load)
    {
        load = false;
        return nextScriptNum;
    }
    
    return -1;
}

bool checkReset()
{
    if (reset)
    {
        reset = false;
        return true;
    }
    return false;
}


void cb(Fl_Widget *ob) {
  printf("Callback for %s '%s'\n",ob->label(),((Fl_Input*)ob)->value());
}

int when = 0;
/*
void toggle_cb(Fl_Widget *o, long v) {
  if (((Fl_Toggle_Button*)o)->value()) when |= v; else when &= ~v;
  for (int i=0; i<5; i++) input[i]->when(when);
}
*/
void test(Fl_Choice *i) {
  nextScriptNum = i->value();
}

void visible_button_cb(Fl_Widget *, long which)
{
    toggleVis = names.at(which);
}
void collidable_button_cb(Fl_Widget *, long which)
{
    toggleCol = names.at(which);
}

void pause_sim_button_cb(Fl_Widget *,void *) {
  pause_sim = !pause_sim;
}
void reset_button_cb(Fl_Widget *,void *) {
  reset = true;
}
void load_button_cb(Fl_Widget *,void *) {
  test(scriptsWindow);
  load = true;
}

std::string checkToggleVis()
{
    return toggleVis;
}
std::string checkToggleCol()
{
    return toggleCol;
}
void resetVis()
{
    toggleVis = "";
}
void resetCol()
{
    toggleCol = "";
}
/*
void color_cb(Fl_Widget* button, void* v) {
  Fl_Color c;
  switch ((fl_intptr_t)v) {
  case 0: c = FL_BACKGROUND2_COLOR; break;
  case 1: c = FL_SELECTION_COLOR; break;
  default: c = FL_FOREGROUND_COLOR; break;
  }
  uchar r,g,b; Fl::get_color(c, r,g,b);
  if (fl_color_chooser(0,r,g,b)) {
    Fl::set_color(c,r,g,b); Fl::redraw();
    button->labelcolor(fl_contrast(FL_BLACK,c));
    button->redraw();
  }
}

void tabnav_cb(Fl_Widget *w, void *v) {
  Fl_Light_Button *b = (Fl_Light_Button*)w;
  Fl_Multiline_Input *fmi = (Fl_Multiline_Input*)v;
  fmi->tab_nav(b->value() ? 1 : 0);
}

void arrownav_cb(Fl_Widget *w, void *v) {
  Fl_Light_Button *b = (Fl_Light_Button*)w;
  Fl::option(Fl::OPTION_ARROW_FOCUS, b->value() ? true : false);
}
*/
int checkFLTKWindow()
{



    Fl::wait(0);
    return 0;
}

int createFLTKWindow(char* title, std::vector<std::string>& s, std::map<std::string, Entity*>& entities)
{
  int argc = 0;
  char** argv;

  pause_sim = false;
  reset = false;
  load = false;
  nextScriptNum = 0;
  toggleVis = "";
  toggleCol = "";
  // the following two lines set the correct color scheme, so that 
  // calling fl_contrast below will return good results

  Fl::args(argc, argv);
  Fl::get_system_colors();
  fltkWindow = new Fl_Window(370,420, title);

  int y = 10;

  scriptsWindow = new Fl_Choice(70, y, 210, 20, "Script:   ");


  for (std::vector<std::string>::iterator iter = s.begin(); iter != s.end(); iter++)
  {
      scriptsWindow->add(iter->c_str());
  }

  y += 30;

  b = new Fl_Button(30,y,150,20,"RESET CURRENT");
  b->callback(reset_button_cb);
  b->tooltip("Reset character and use new script.");

  b = new Fl_Button(190,y,150,20,"LOAD AND RESET");
  b->callback(load_button_cb); 
  b->tooltip("Reset character and use new script.");

  y += 30;
   

  b = new Fl_Button(100,y,150,20,"PAUSE");
  b->callback(pause_sim_button_cb);
  b->tooltip("Pause the simulation.");

  y += 45;
  int i = 0;
  for (auto iter = entities.begin(); iter != entities.end(); iter++)
  {
      names.push_back(iter->first);
      text = new Fl_Box(FL_NO_BOX, 20, y, 30, 20, (iter->first).c_str());
      b = new Fl_Round_Button(80,y, 150,20, "Visible"); 
      b->callback(visible_button_cb, i);
      b = new Fl_Round_Button(160,y, 150,20, "Collisions"); 
      b->callback(collidable_button_cb, i);
      y += 25;
      i++;
  }


  fltkWindow->end();

  Fl::visual(FL_DOUBLE|FL_INDEX);

  fltkWindow->show(argc,argv);

      


  return 0;
}
//
// End of "$Id: input.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $".
//
