#ifndef FLTK_H
#define FLTK_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Toggle_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Round_Button.H>

class Entity;

int createFLTKWindow(char*, std::vector<std::string>&, std::map<std::string, Entity*>&);
int checkFLTKWindow();
bool checkReset();
int checkLoad();
bool checkPause();
std::string checkToggleVis();
std::string checkToggleCol();
void resetVis();
void resetCol();


#endif // FLTK_H
