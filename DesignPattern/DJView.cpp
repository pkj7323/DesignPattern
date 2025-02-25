#include "pch.h"
#include "DJView.h"

#include <utility>

DJView::DJView(std::shared_ptr<ControllerInterface> controller, std::shared_ptr<BeatModelInterface> model)
	: controller(std::move(controller)), model(model)
{
	model->registerObserver(static_cast<BeatObserver*>(this));
	model->registerObserver(static_cast<BPMObserver*>(this));
}

DJView::~DJView()
{
	model->removeObserver(static_cast<BeatObserver*>(this));
	model->removeObserver(static_cast<BPMObserver*>(this));
}

void DJView::updateBeat()
{
}

void DJView::updateBPM()
{
	displayBPM();
}

void DJView::start()
{
	controller->start();
	displayBPM();
	createWindow();
}

LRESULT DJView::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	DJView* view = nullptr;
	if (message == WM_CREATE)
	{
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		view = reinterpret_cast<DJView*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(view));
	}
	else
	{
		view = reinterpret_cast<DJView*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	if (view)
	{
		switch (message)
		{
		case WM_KEYDOWN:
			if (wParam == VK_RETURN)
			{
				view->processInput();
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void DJView::displayBPM()
{
	int bpm = model->getBPM();
	std::cout << "Current BPM: " << bpm << std::endl;
}


void DJView::processInput()
{
	int bpm;
	
	std::cout << "Enter new BPM (or -1 to quit): ";
	std::cin >> bpm;
	if (bpm == -1)
	{
		controller->stop();
		return;
	}
	controller->setBPM(bpm);
	
}

void DJView::createWindow()
{
	const wchar_t CLASS_NAME[] = L"DJViewWindowClass";

	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = CLASS_NAME;
	RegisterClass(&wc);

	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"DJView",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		this
	);

	if (hWnd == nullptr)
	{
		std::cerr << "Failed to create window" << std::endl;
		return;
	}

	ShowWindow(hWnd, SW_SHOW);
}

