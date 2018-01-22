#include <boost/thread/thread.hpp>
#include "DataReceiver.hpp"
#include "sciter-x-window.hpp"
#include "resources.cpp"
#include "NotificationsController.hpp"
#include "MainView.hpp"

///
/// \brief Frame class
///
/// Additional description
class frame : public sciter::window {
public:
	///
	/// A constructor
  frame() : window(SW_TITLEBAR | SW_CONTROLS | SW_MAIN | SW_ENABLE_DEBUG) {}	///
};



int uimain(std::function<int()> run) {

	sciter::debug_output_console console;// - uncomment it if you will need console window

	std::shared_ptr<CPUData> cpu1 = make_shared<CPUData>();
	std::shared_ptr<DiskData> disk = make_shared<DiskData>();
	std::shared_ptr<RAMData> ram = make_shared<RAMData>();
	std::shared_ptr<NotificationsController> notifications_controller = make_shared<NotificationsController>();
	notifications_controller->setTwitterNotifier(make_unique<TwitterNotifier>());
	notifications_controller->setCPUData(cpu1);
	cpu1->addObserver(notifications_controller);


	DataReceiver dr("127.0.0.1", 8001, cpu1, disk, ram, console);
	dr.tryToConnect();
	boost::thread thrd1(ref(dr));

	

	sciter::archive::instance().open(aux::elements_of(resources)); // bind resources[] (defined in "resources.cpp") with the archive

	frame *pwin = new frame();

	// note: this:://app URL is dedicated to the sciter::archive content associated with the application
	pwin->load(WSTR("this://app/main.htm"));
	std::shared_ptr<MainView> mv = make_shared<MainView>(static_cast<sciter::window*>(pwin), cpu1, disk, ram);
	cpu1->addObserver(mv);
	
	pwin->expand();

	return run();
  
}