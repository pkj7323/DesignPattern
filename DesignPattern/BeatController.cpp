#include "pch.h"
#include "BeatController.h"

BeatController::BeatController(std::shared_ptr<BeatModelInterface> model) : model(model)
{
	model->initialize();
	view = nullptr;
}

BeatController::~BeatController()
{
	model->quit();
}

void BeatController::setView(DJView* view)
{
	this->view = view;
}

void BeatController::start()
{
	model->on();
}

void BeatController::stop()
{
	model->off();
}

void BeatController::increaseBPM()
{
	int bpm = model->getBPM();
	model->setBPM(bpm + 1);
}

void BeatController::decreaseBPM()
{
	int bpm = model->getBPM();
	model->setBPM(bpm - 1);
}

void BeatController::setBPM(int bpm)
{
	model->setBPM(bpm);
}
