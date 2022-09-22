#include "system.hpp"
#include "input/input.hpp"
#include "gfx/gfx.hpp"

int system::init(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i)
	{
		system::args.emplace_back(argv[i]);
	}

	auto w = system::get_argument("w");
	auto h = system::get_argument("h");
	auto fps = system::get_argument("fps");
	if (w != "\0" && system::is_num(w))
	{
		system::resolution.x = std::stoi(w);
	}

	if (h != "\0" && system::is_num(h))
	{
		system::resolution.y = std::stoi(h);
	}

	if (fps != "\0" && system::is_num(fps))
	{
		gfx::set_target_fps(std::stoi(fps));
	}

	gfx::init(system::resolution, APPNAME);
	input::set_exit_key(KEY_NULL);

	system::main_loop();

	return 0; 
}

void system::main_loop()
{
	while (!input::window_should_close())
	{
		gfx::prepare();
		gfx::draw_fps({10, 10});
		gfx::present();
	}
}

std::string system::get_argument(const std::string& arg)
{
	std::string retn = "";

	for (auto i = 0; i < args.size(); ++i)
	{
		//Find the argument
		if (args[i] == "--" + arg)
		{
			//Check to see if theres something after it
			if (args.size() - 1 >= i + 1)
			{
				retn = args[i + 1];
			}
			else
			{
				retn = "\0";
			}
		}
	}

	return retn;
}

bool system::is_num(const std::string& input)
{
	char* p;
	strtol(input.c_str(), &p, 10);
	return *p == 0;
}

bool system::shutdown = false;
std::vector<std::string> system::args {};
Vector2 system::resolution {640, 480};
