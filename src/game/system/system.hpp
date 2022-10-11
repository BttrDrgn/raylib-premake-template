#pragma once

class system final
{
public:
	static int init(int, char* []);
	static void main_loop();
	static std::string get_argument(const std::string& arg);

	static bool shutdown;
	static std::vector<std::string> args;
	static Vector2 resolution;
	static float frame_time;
};
