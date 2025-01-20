#include <iostream>
class StreamingPlayer
{
	std::string name;
public:
	StreamingPlayer(std::string name)
	{
		this->name = name;
	}
	void on()
	{
		std::cout << "Streaming player on" << std::endl;
	}
	void off()
	{
		std::cout << "Streaming player off" << std::endl;
	}
	void play(std::string movie)
	{
		std::cout << "Streaming player playing " << movie << std::endl;
	}
	void stop()
	{
		std::cout << "Streaming player stopped" << std::endl;
	}
	friend std::ostream& operator<<(std::ostream& os, const StreamingPlayer& player)
	{
		return os << player.name << " Streaming player";
	}
};

class Amplifier
{
public:
	void on()
	{
		std::cout << "Amplifier on" << std::endl;
	}
	void off()
	{
		std::cout << "Amplifier off" << std::endl;
	}
	void setStreamingPlayer(StreamingPlayer player)
	{
		std::cout << "Amplifier setting streaming player to " << player << std::endl;
	}
	void setSurroundSound()
	{
		std::cout << "Amplifier setting surround sound" << std::endl;
	}
	void setVolume(int volume)
	{
		std::cout << "Amplifier setting volume to " << volume << std::endl;
	}
};
class Tuner
{
public:
	void on()
	{
		std::cout << "Tuner on" << std::endl;
	}
	void off()
	{
		std::cout << "Tuner off" << std::endl;
	}
};
class Projector
{
public:
	void on()
	{
		std::cout << "Projector on" << std::endl;
	}
	void off()
	{
		std::cout << "Projector off" << std::endl;
	}
	void wideScreenMode()
	{
		std::cout << "Projector in wide screen mode" << std::endl;
	}
};
class TheaterLights
{
public:
	void on()
	{
		std::cout << "Theater ceiling lights on" << std::endl;
	}
	void off()
	{
		std::cout << "Theater ceiling lights off" << std::endl;
	}
	void dim(int level)
	{
		std::cout << "Theater ceiling lights dimming to " << level << "%" << std::endl;
	}
};
class Screen
{
public:
	void up()
	{
		std::cout << "Theater screen going up" << std::endl;
	}
	void down()
	{
		std::cout << "Theater screen going down" << std::endl;
	}
};
class PopcornPopper
{
public:
	void on()
	{
		std::cout << "Popcorn popper on" << std::endl;
	}
	void off()
	{
		std::cout << "Popcorn popper off" << std::endl;
	}
	void pop()
	{
		std::cout << "Popcorn popper popping popcorn!" << std::endl;
	}
};
class HomeTheaterFacade
{
	Amplifier* amp;
	Tuner* tuner;
	StreamingPlayer* player;
	Projector* projector;
	TheaterLights* lights;
	Screen* screen;
	PopcornPopper* popper;
public:
	HomeTheaterFacade(Amplifier* amp, Tuner* tuner, StreamingPlayer* player
		, Projector* projector, TheaterLights* lights, Screen* screen, PopcornPopper* popper)
	{
		this->amp = amp;
		this->tuner = tuner;
		this->player = player;
		this->projector = projector;
		this->lights = lights;
		this->screen = screen;
		this->popper = popper;
	}
	void watchMovie(std::string movie)
	{
		std::cout << "Get ready to watch a movie..." << std::endl;
		popper->on();
		popper->pop();
		lights->dim(10);
		screen->down();
		projector->on();
		projector->wideScreenMode();
		amp->on();
		amp->setStreamingPlayer(*player);
		amp->setSurroundSound();
		amp->setVolume(5);
		player->on();
		player->play(movie);
	}
	void endMovie()
	{
		std::cout << "Shutting movie theater down..." << std::endl;
		popper->off();
		lights->on();
		screen->up();
		projector->off();
		amp->off();
		player->stop();
		player->off();
	}
};
int main()
{
	Amplifier* amp = new Amplifier();
	Tuner* tuner = new Tuner();
	StreamingPlayer* player = new StreamingPlayer("Netflix");
	Projector* projector = new Projector();
	TheaterLights* lights = new TheaterLights();
	Screen* screen = new Screen();
	PopcornPopper* popper = new PopcornPopper();
	HomeTheaterFacade* homeTheater = new HomeTheaterFacade(amp, tuner, player, projector, lights, screen, popper);
	homeTheater->watchMovie("The Avengers");
	std::cout << "\n\n\n";
	homeTheater->endMovie();

	return 0;
}