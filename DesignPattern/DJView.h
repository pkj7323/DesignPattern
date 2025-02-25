#pragma once

#include "Interface.h"
class BeatModelInterface;
class ControllerInterface;

class DJView : public BeatObserver, public BPMObserver
{
	std::shared_ptr<ControllerInterface> controller;
	std::shared_ptr<BeatModelInterface> model;
	HWND hWnd;
public:
	DJView(std::shared_ptr<ControllerInterface> controller, std::shared_ptr<BeatModelInterface> model);
	~DJView();


	void updateBeat() override;
	void updateBPM() override;
	void start();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	void displayBPM();
	void processInput();
	void createWindow();
	
};
