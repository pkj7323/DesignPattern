#include "pch.h"

#include "BeatController.h"
#include "BeatModel.h"
#include "Interface.h"
#include "DJView.h"
#include "iostream"


int main()
{
	std::shared_ptr<BeatModelInterface> model = std::make_shared<BeatModel>();
	std::shared_ptr<BeatController>controller = std::make_shared<BeatController>(model);
	std::shared_ptr<DJView> view = std::make_shared<DJView>(controller, model);
	model->updateBeat();

	controller->setView(view.get());
	view->start();

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return 0;
}