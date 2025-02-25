#pragma once
#include "Interface.h"
class BeatModel : public BeatModelInterface
{
	std::list<BeatObserver*> beatObservers;
	std::list<BPMObserver*> bpmObservers;
	int bpm;
	bool m_run;
	std::string path;
	FMOD::System* system;
	FMOD::Sound* sound;
	FMOD::Channel* channel;
	FMOD_RESULT result;
public:
	BeatModel();
	~BeatModel();
	void initialize() override;
	void on() override;
	void off() override;
	void run();
	void quit() override;
	void setBPM(const int& bpm) override;
	int	 getBPM() override;

	void updateBeat();

	void registerObserver(BeatObserver* o) override;
	void notifyBeatObserver();
	void removeObserver(BeatObserver* o) override;

	void registerObserver(BPMObserver* o) override;
	void notifyBPMObserver();
	void removeObserver(BPMObserver* o) override;

	void playBeat();
	void stopBeat();
	
};
