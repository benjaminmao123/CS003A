#include <string>

#include "Engine.h"

class Application
{
public:
	Application(int32_t width, int32_t height, const std::string &name)
		: engine(width, height, name)
	{

	}

	void Start()
	{
		
	}

private:
	bme::Engine engine;
};

int main()
{
	Application app(800, 600, "Predator and Prey");
	app.Start();

	return 0;
}