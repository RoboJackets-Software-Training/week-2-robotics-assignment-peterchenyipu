#include <iostream> // Gives us access to std::cin and std::cout
#include <string>	// Gives us access to std::string and std::getline()

struct LightOutputs
{
	bool red_ns;
	bool yellow_ns;
	bool green_ns;
	bool red_ew;
	bool yellow_ew;
	bool green_ew;
};

struct LightInputs
{
	int time;
	bool car_sensor_n;
	bool car_sensor_s;
};

// TODO Define your light controller state machine class here
class LightController
{
public:
	LightOutputs step(LightInputs lightInputs)
	{
		//std::cout << "curr state:" << curr_state << std::endl;
		//std::cout << "state time:" << stateTime << std::endl;
		//std::cout << "input 1: " << lightInputs.car_sensor_n << "\n";
		//std::cout << "input 2: " << lightInputs.car_sensor_s << "\n";
		switch (curr_state)
		{
		case EW_GREEN:
			if (stateTime != 4)
			{
				// state just began
				stateTime++;
			}
			else if (stateTime == 4)
			{
				curr_state = EW_YELLO;
				stateTime = 0;
			}
			break;
		case EW_YELLO:
			if (stateTime != 1)
			{
				stateTime++;
			}
			else if (stateTime == 1)
			{
				curr_state = ALL_RED;
				stateTime = 0;
			}
			break;
		case NS_GREEN:
			if (stateTime != 4) {
				stateTime++;
			} else if (stateTime == 4) {
				curr_state = NS_YELLO;
				stateTime = 0;
			}
			break;
		case NS_YELLO:
			if (stateTime != 1) {
				stateTime++;
			} else if (stateTime == 1) {
				curr_state = ALL_RED;
				stateTime = 0;
			}
			break;
		case ALL_RED:
			if (lightInputs.car_sensor_n || lightInputs.car_sensor_s) {
				curr_state = NS_GREEN;
			} else {
				curr_state = EW_GREEN;
			}
			break;
		}
		return returnState();
	}

	LightOutputs returnState()
	{
		switch (curr_state)
		{
		case ALL_RED:
			return {true, false, false, true, false, false};
		case NS_GREEN:
			return {false, false, true, true, false, false};
		case NS_YELLO:
			return {false, true, false, true, false, false};
		case EW_GREEN:
			return {true, false, false, false, false, true};
		case EW_YELLO:
			return {true, false, false, false, true, false};
		}
	}

private:
	enum state
	{
		ALL_RED,
		NS_GREEN,
		NS_YELLO,
		EW_GREEN,
		EW_YELLO
	};
	int stateTime = 0;
	state curr_state = ALL_RED;
};

int main()
{
	int time = 0;
	// TODO Initialize your state machine class here
	LightController controller1;
	while (true)
	{
		std::string input;
		std::getline(std::cin, input);
		if (input.size() != 2)
			break;
		// TODO Parse the input digits
		LightInputs newInput;
		newInput.car_sensor_n = (input[0] == '1');
		newInput.car_sensor_s = (input[1] == '1');
		newInput.time = time;

		// TODO Update your state machine based on input
		LightOutputs output = controller1.step(newInput);
		// TODO Output your state machine's light controls to std::cout
		std::cout << output.red_ns << output.yellow_ns << output.green_ns
                  << output.red_ew << output.yellow_ew << output.green_ew
                  << "\n";
	}
	return 0;
}
