#pragma once
class DJView;

class BeatObserver
{
public:
	virtual ~BeatObserver() {}
	virtual void updateBeat() = 0;
};
class BPMObserver
{
public:
	virtual ~BPMObserver() {}
	virtual void updateBPM() = 0;
};
class BeatModelInterface
{
public:
	virtual void initialize() = 0;
	virtual void on() = 0;
	virtual void off() = 0;
	virtual void quit() = 0;
	virtual void setBPM(const int& bpm) = 0;
	virtual int getBPM() = 0;
	virtual void updateBeat() = 0;

	virtual void registerObserver(BeatObserver* o) = 0;
	virtual void removeObserver(BeatObserver* o) = 0;
	virtual void registerObserver(BPMObserver* o) = 0;
	virtual void removeObserver(BPMObserver* o) = 0;
};
class HeartModelInterface
{
public:
	virtual ~HeartModelInterface() {}

	virtual int getHeartRate() = 0;
	virtual void registerObserver(BeatObserver* o) = 0;
	virtual void removeObserver(BeatObserver* o) = 0;
	virtual void registerObserver(BPMObserver* o) = 0;
	virtual void removeObserver(BPMObserver* o) = 0;

};
class ControllerInterface
{
public:
	virtual ~ControllerInterface() {}

	virtual void setView(DJView* view) = 0;
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void increaseBPM() = 0;
	virtual void decreaseBPM() = 0;
	virtual void setBPM(int bpm) = 0;
};