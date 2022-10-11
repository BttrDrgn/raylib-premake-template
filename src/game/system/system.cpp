#include "system.hpp"
#include "input/input.hpp"
#include "gfx/gfx.hpp"
#include "math/math.hpp"

int system::init(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i)
	{
		system::args.emplace_back(argv[i]);
	}

	auto w = system::get_argument("w");
	auto h = system::get_argument("h");
	auto fps = system::get_argument("fps");
	if (w != "\0" && math::is_num(w))
	{
		system::resolution.x = std::stoi(w);
	}

	if (h != "\0" && math::is_num(h))
	{
		system::resolution.y = std::stoi(h);
	}

	if (fps != "\0" && math::is_num(fps))
	{
		gfx::set_target_fps(std::stoi(fps));
	}
	else
	{
		gfx::set_target_fps(300);
	}

	gfx::init(system::resolution, APPNAME);
	input::init();

	system::main_loop();

	return 0; 
}

void system::main_loop()
{
	while (!system::shutdown)
	{
		gfx::prepare();
		input::begin();

		if (input::pressed("alt")) gfx::show_fps = !gfx::show_fps;

		input::end();
		gfx::present();

		system::frame_time = gfx::get_frame_time();
		system::shutdown = input::window_should_close();
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

bool system::shutdown = false;
std::vector<std::string> system::args {};
Vector2 system::resolution {640, 480};
float system::frame_time;
