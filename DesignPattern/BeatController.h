#pragma once
#include "Interface.h"

class BeatController : public ControllerInterface
{
public:
	BeatController(std::shared_ptr<BeatModelInterface> model);
	~BeatController();
	void setView(DJView* view) override;
	void start() override;
	void stop() override;
	void increaseBPM() override;
	void decreaseBPM() override;
	void setBPM(int bpm) override;
private:
	std::shared_ptr<BeatModelInterface> model;
	DJView* view;
	
};
