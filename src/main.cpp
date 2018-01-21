//// WindowsCollector.cpp : Defines the entry point for the console application.
////
//
//#include <boost/thread/thread.hpp>
//#include <iostream>
//#include "DataSender.hpp"
//#include "WindowsCollector.hpp"
//
//using namespace std;
//
//int main()
//{
//	CPUData cpu1;
//	DiskData disk;
//	RAMData ram;
//	DataSender ds(cpu1, disk, ram);
//	
//	WindowsCollector w(&cpu1, &ram, &disk);
//	w.fillModelWithData();
//	boost::thread thrd1(ref(ds));
//
//	for (;;)
//	{
//		w.fillModelWithData();
//	}
//
//
//	thrd1.join();
//
//	cin.get();
//	return 0;
//}
//


// HelloWorld.cpp : Defines the entry point for the application.
//

//
//#include "sciter-x-window.hpp"
//
//class frame : public sciter::window {
//public:
//	frame() : window(SW_TITLEBAR | SW_RESIZEABLE | SW_CONTROLS | SW_MAIN | SW_ENABLE_DEBUG) {}
//};
//
//#include "resources.cpp"
//
//int uimain(std::function<int()> run) {
//
//	//sciter::debug_output_console console; - uncomment it if you will need console window
//
//	sciter::archive::instance().open(aux::elements_of(resources)); // bind resources[] (defined in "resources.cpp") with the archive
//
//	frame *pwin = new frame();
//
//	// note: this:://app URL is dedicated to the sciter::archive content associated with the application
//	pwin->load(WSTR("this://app/main.htm"));
//
//	pwin->expand();
//
//	return run();
//
//}
#include "CPUData.hpp"
#include "RAMData.hpp"
#include "DiskData.hpp"
#include "TwitterNotifier.hpp"
#include "NotificationsController.hpp"
#include "WindowsCollector.hpp"

int main() {

	CPUData* c = new CPUData();
	RAMData* r = new RAMData();
	DiskData* d = new DiskData();
	WindowsCollector* collector = new WindowsCollector(c, r, d);

	TwitterNotifier* t = new TwitterNotifier();
	NotificationsController* n = new NotificationsController();
	n->setTwitterNotifier(t);
	n->setCPUData(c);
	c->add(n);

	while (true) {
		collector->fillModelWithData();
		c->notify();
	}

	return 0;
}