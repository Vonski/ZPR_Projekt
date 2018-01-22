#include <boost/thread/thread.hpp>
#include "DataReceiver.hpp"
#include "sciter-x-window.hpp"
#include "resources.cpp"
#include "NotificationsController.hpp"
#include "ViewController.hpp"

///
/// \brief Frame class
///
/// Additional description
class frame : public sciter::window {
public:
	///
	/// A constructor
	frame() : window(SW_TITLEBAR | SW_CONTROLS | SW_MAIN | SW_ENABLE_DEBUG) {}	///
	
	void setViewController(std::shared_ptr<CPUData> cpu1, std::shared_ptr<DiskData> disk, std::shared_ptr<RAMData> ram)
	{
		vc = make_shared<ViewController>(static_cast<sciter::window*>(this), cpu1, disk, ram);
	}

BEGIN_FUNCTION_MAP
	FUNCTION_1("getSomeData", getSomeData);
END_FUNCTION_MAP
	json::value getSomeData(json::value nextView) 
	{ 
		int tmp = nextView.get<int>();
		vc->changeView(tmp);
		return true;
	}

	std::shared_ptr<ViewController> vc;
	sciter::debug_output_console console;
};


int uimain(std::function<int()> run) {

	//sciter::debug_output_console console;// - uncomment it if you will need console window

	std::shared_ptr<CPUData> cpu1 = make_shared<CPUData>();
	std::shared_ptr<DiskData> disk = make_shared<DiskData>();
	std::shared_ptr<RAMData> ram = make_shared<RAMData>();
	std::shared_ptr<NotificationsController> notifications_controller = make_shared<NotificationsController>();
	notifications_controller->setTwitterNotifier(make_unique<TwitterNotifier>());
	notifications_controller->setCPUData(cpu1);
	cpu1->addObserver(notifications_controller);

	sciter::archive::instance().open(aux::elements_of(resources)); // bind resources[] (defined in "resources.cpp") with the archive

	frame *pwin = new frame();

	// note: this:://app URL is dedicated to the sciter::archive content associated with the application
	pwin->load(WSTR("this://app/main.htm"));
	
	DataReceiver dr("127.0.0.1", 8001, cpu1, disk, ram, pwin->console);
	dr.tryToConnect();
	boost::thread thrd1(ref(dr));
	pwin->setViewController(cpu1, disk, ram);

	pwin->expand();

	return run();
  
}