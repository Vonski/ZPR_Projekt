#include "sciter-x-window.hpp"
#include "resources.cpp"

class frame : public sciter::window {
public:
  frame() : window(SW_TITLEBAR | SW_RESIZEABLE | SW_CONTROLS | SW_MAIN | SW_ENABLE_DEBUG) {}
};


int uimain(std::function<int()> run) {

  //sciter::debug_output_console console; - uncomment it if you will need console window

  sciter::archive::instance().open(aux::elements_of(resources)); // bind resources[] (defined in "resources.cpp") with the archive

  frame *pwin = new frame();

  // note: this:://app URL is dedicated to the sciter::archive content associated with the application
  pwin->load(WSTR("this://app/main.htm"));

  pwin->expand();

  return run();

}