#include "pch.h"
#include "BeatModel.h"

BeatModel::BeatModel()
: bpm(90), m_run(false), system(nullptr), sound(nullptr), channel(nullptr), result(FMOD_OK)
{
	path = "../res/relaxing-guitar-loop.mp3";
}

BeatModel::~BeatModel()
{
}

void BeatModel::initialize()
{
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}

	result = system->init(512, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}

	result = system->createSound(path.c_str(), FMOD_LOOP_OFF, nullptr, &sound);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}

	
}

void BeatModel::on()
{
	bpm = 90;
	m_run = true;
	playBeat();
}

void BeatModel::off()
{
	stopBeat();
	m_run = false;
}

void BeatModel::run()
{
	//적중안됨
}

void BeatModel::quit()
{
	if (channel)
	{
		channel->stop();
	}
	if (sound)
	{
		sound->release();
	}
	if (system)
	{
		system->close();
		system->release();
	}
}

void BeatModel::setBPM(const int& bpm)
{
	this->bpm = bpm;
	if (m_run)
	{
		stopBeat();
		playBeat();
	}
	notifyBPMObserver();
}

int BeatModel::getBPM()
{
	return bpm;
}

void BeatModel::updateBeat()
{
	system->update();
}

void BeatModel::registerObserver(BeatObserver* o)
{
	beatObservers.push_back(o);
}

void BeatModel::notifyBeatObserver()
{
	for (auto& observer : beatObservers)
	{
		observer->updateBeat();
	}
}

void BeatModel::removeObserver(BeatObserver* o)
{
	beatObservers.remove(o);
}



void BeatModel::registerObserver(BPMObserver* o)
{
	bpmObservers.push_back(o);
}

void BeatModel::notifyBPMObserver()
{
	for (auto& observer : bpmObservers)
	{
		observer->updateBPM();
	}
}

void BeatModel::removeObserver(BPMObserver* o)
{
	bpmObservers.remove(o);
}

void BeatModel::playBeat()  
{
	if (channel)
	{
		bool isPlaying = false;
		channel->isPlaying(&isPlaying);
		if (isPlaying)
		{
			return;
		}
	}
	result = system->playSound(sound, nullptr, false, &channel);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}

	float frequency;
	result = sound->getDefaults(&frequency, nullptr);  
	if (result != FMOD_OK)  
	{  
		std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;  
		   exit(-1);  
	}  

	frequency = frequency * (static_cast<float>(bpm) / 60.0f);  
	result = channel->setFrequency(frequency);  
	if (result != FMOD_OK)  
	{  
	   std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;  
	   exit(-1);  
	}  
}

void BeatModel::stopBeat()
{
	if (channel)
	{
		channel->setPaused(true);
	}
}
