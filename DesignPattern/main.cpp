#include <iostream>
#include <string>
#include <vector>

class Command
{
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};

class NoCommand : public Command
{
public:
	void execute() override {}
	void undo() override {}
};

class Light
{
	std::string location;
public:
	Light(std::string location) : location(location) {}
	std::string getLocation()
	{
		return location;
	}
	void on()
	{
		std::cout << "Light is on" << std::endl;
	}
	void off()
	{
		std::cout << "Light is off" << std::endl;
	}
};
class LightOnCommand : public Command
{
	Light* light;
public:
	LightOnCommand(Light* light) : light(light) {}
	void execute()
	{
		light->on();
	}
	void undo() override
	{
		light->off();
	}
};
class LightOffCommand : public Command
{
	Light* light;
public:
	LightOffCommand(Light* light) : light(light) {}
	void execute()
	{
		light->off();
	}
	void undo() override
	{
		light->on();
	}
};



class Stereo
{
	std::string location;
public:
	Stereo(std::string location) : location(location) {}
	std::string getLocation()
	{
		return location;
	}
	void on()
	{
		std::cout << "Stereo is on" << std::endl;
	}
	void off()
	{
		std::cout << "Stereo is off" << std::endl;
	}
	void setCD()
	{
		std::cout << "Stereo is set for CD input" << std::endl;
	}
	void setDVD()
	{
		std::cout << "Stereo is set for DVD input" << std::endl;
	}
	void setRadio()
	{
		std::cout << "Stereo is set for Radio" << std::endl;
	}
	void setVolume(int volume)
	{
		std::cout << "Stereo volume set to " << volume << std::endl;
	}
};
class StreoOnWithCDCommand : public Command
{
	Stereo* stereo;
public:
	StreoOnWithCDCommand(Stereo* streo) :stereo{ streo } {}
	void execute()
	{
		stereo->on();
		stereo->setCD();
		stereo->setVolume(11);
	}
	void undo() override
	{
		stereo->off();
	}
};
class StereoOffCommand : public Command
{
	Stereo* stereo;
public:
	StereoOffCommand(Stereo* stereo) : stereo(stereo) {}
	void execute()
	{
		stereo->off();
	}
	void undo() override
	{
		stereo->on();
		stereo->setCD();
		stereo->setVolume(11);
	}
};


class GarageDoor
{
	std::string location;
public:
	GarageDoor(std::string location) : location(location) {}
	void up()
	{
		std::cout << "Garage Door is Open" << std::endl;
	}
	void down()
	{
		std::cout << "Garage Door is Close" << std::endl;
	}
	void stop()
	{
		std::cout << "Garage Door is Stop" << std::endl;
	}
	void lightOn()
	{
		std::cout << "Garage Light is On" << std::endl;
	}
	void lightOff()
	{
		std::cout << "Garage Light is Off" << std::endl;
	}
	std::string getLocation()
	{
		return location;
	}
};
class GarageDoorOpenCommand : public Command
{
	GarageDoor* garageDoor;
public:
	GarageDoorOpenCommand(GarageDoor* garageDoor) : garageDoor(garageDoor) {}
	void execute()
	{
		garageDoor->up();
	}
	void undo() override
	{
		garageDoor->down();
	}
};
class GarageDoorCloseCommand : public Command
{
	GarageDoor* garageDoor;
public:
	GarageDoorCloseCommand(GarageDoor* garageDoor) : garageDoor(garageDoor) {}
	void execute()
	{
		garageDoor->down();
	}
	void undo() override
	{
		garageDoor->up();
	}
};
//선풍기 코드 삭제
class TV
{
	std::string location;
public:
	TV(std::string location) : location(location) {}
	void on()
	{
		std::cout << "TV is on" << std::endl;
	}
	void off()
	{
		std::cout << "TV is off" << std::endl;
	}
	void setInputChannel()
	{
		std::cout << "TV channel is set for DVD" << std::endl;
	}
	void setVolume(int volume)
	{
		std::cout << "TV volume set to " << volume << std::endl;
	}
};
class TVOnCommand : public Command
{
	TV* tv;
public:
	TVOnCommand(TV* tv) : tv(tv) {}
	void execute()
	{
		tv->on();
		tv->setInputChannel();
		tv->setVolume(11);
	}
	void undo() override
	{
		tv->off();
	}
};
class TVOffCommand : public Command
{
	TV* tv;
public:
	TVOffCommand(TV* tv) : tv(tv) {}
	void execute()
	{
		tv->off();
	}
	void undo() override
	{
		tv->on();
		tv->setInputChannel();
		tv->setVolume(11);
	}
};

class Hottub
{
public:
	void on()
	{
		std::cout << "Hottub is on" << std::endl;
	}
	void off()
	{
		std::cout << "Hottub is off" << std::endl;
	}
	void bubblesOn()
	{
		std::cout << "Hottub is bubbling!" << std::endl;
	}
	void bubblesOff()
	{
		std::cout << "Hottub is not bubbling" << std::endl;
	}
};
class HottubOnCommand : public Command
{
	Hottub* hottub;
public:
	HottubOnCommand(Hottub* hottub) : hottub(hottub) {}
	void execute()
	{
		hottub->on();
		hottub->bubblesOn();
	}
	void undo() override
	{
		hottub->off();
	}
};
class HottubOffCommand : public Command
{
	Hottub* hottub;
public:
	HottubOffCommand(Hottub* hottub) : hottub(hottub) {}
	void execute()
	{
		hottub->off();
	}
	void undo() override
	{
		hottub->on();
		hottub->bubblesOn();
	}
};



class RemoteControl
{
	std::vector<std::shared_ptr<Command>> onCommands;
	std::vector<std::shared_ptr<Command>> offCommands;
	std::shared_ptr<Command> undoCommand;
public:
	RemoteControl()
	{
		undoCommand = std::make_shared<NoCommand>();
		for (int i = 0; i < 7; i++)
		{
			onCommands.push_back(std::make_shared<NoCommand>());
			offCommands.push_back(std::make_shared<NoCommand>());
		}
	}
	void setCommand(unsigned int slot, std::shared_ptr<Command> onCommand, std::shared_ptr<Command> offCommand)
	{
		onCommands[slot] = std::move(onCommand);
		offCommands[slot] = std::move(offCommand);
	}
	void onButtonWasPressed(unsigned int slot)
	{
		onCommands[slot]->execute();
		undoCommand = onCommands[slot];
	}
	void offButtonWasPressed(unsigned int slot)
	{
		offCommands[slot]->execute();
		undoCommand = offCommands[slot];
	}
	void undoButtonWasPressed()
	{
		undoCommand->undo();
	}
    friend std::ostream& operator<<(std::ostream& os, const RemoteControl& remoteControl)
    {
		os << "리모컨\n";
		for (int i = 0; i < remoteControl.onCommands.size(); i++)
		{
    		os << "[슬롯 " << i << "] " << typeid(*remoteControl.onCommands[i]).name() << "    " << typeid(*remoteControl.
			    offCommands[i]).name() << std::endl;
		}
		os << "[취소] " << typeid(*remoteControl.undoCommand).name() << std::endl;
		return os;
    }
};

class MacroCommand : public Command
{
	std::vector<std::shared_ptr<Command>> commands;
public:
	MacroCommand(std::vector<std::shared_ptr<Command>> commands) : commands(commands) {}
	void execute() override
	{
		for (auto& command : commands)
		{
			command->execute();
		}
	}
	void undo() override
	{
		for (auto& command : commands)
		{
			command->undo();
		}
	}
};

int main()
{
	RemoteControl* remoteControl = new RemoteControl();

	TV* tv = new TV("Living Room");
	Light* light = new Light("Living Room");
	Stereo* stereo = new Stereo("Living Room");
	Hottub* hottub = new Hottub();

	auto TVon = std::make_shared<TVOnCommand>(tv);
	auto TVoff = std::make_shared<TVOffCommand>(tv);

	auto LightOn = std::make_shared<LightOnCommand>(light);
	auto LightOff = std::make_shared<LightOffCommand>(light);

	auto StereoOn = std::make_shared<StreoOnWithCDCommand>(stereo);
	auto StereoOff = std::make_shared<StereoOffCommand>(stereo);

	auto HottubOn = std::make_shared<HottubOnCommand>(hottub);
	auto HottubOff = std::make_shared<HottubOffCommand>(hottub);

	std::vector<std::shared_ptr<Command>> partyOn = { TVon, LightOn, StereoOn, HottubOn };
	std::vector<std::shared_ptr<Command>> partyOff = { TVoff, LightOff, StereoOff, HottubOff };

	auto partyOnMacro = std::make_shared<MacroCommand>(partyOn);
	auto partyOffMacro = std::make_shared<MacroCommand>(partyOff);

	remoteControl->setCommand(0, partyOnMacro, partyOffMacro);

	std::cout << *remoteControl << std::endl;
	std::cout << "----파티 시작----" << std::endl;
	remoteControl->onButtonWasPressed(0);
	std::cout << "----파티 끝?----" << std::endl;
	remoteControl->undoButtonWasPressed();
	std::cout << "----파티 끝----" << std::endl;
	remoteControl->offButtonWasPressed(0);


}