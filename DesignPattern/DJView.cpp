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
		case WM_COMMAND:
			if (HIWORD(wParam) == EN_UPDATE)
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
	InvalidateRect(hWnd, NULL, false);
	int bpm = model->getBPM();
	std::wstring bpmStr = L"Current BPM: " + std::to_wstring(bpm);
	SetWindowText(hWnd, bpmStr.c_str());
}


void DJView::processInput()
{
	wchar_t buffer[256];
	GetWindowText(hEdit, buffer, 256);
	int bpm = _wtoi(buffer);

	if (bpm == -1)
	{
		controller->stop();
		PostQuitMessage(-1);
		return;
	}
	controller->setBPM(bpm);
	
}

void DJView::createWindow()
{
	constexpr wchar_t CLASS_NAME[] = L"DJViewWindowClass";

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

	hEdit = CreateWindowEx(
		0,
		L"EDIT",
		nullptr,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		10, 10, 200, 20,
		hWnd,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);

	ShowWindow(hWnd, SW_SHOW);
}

