#include "input.hpp"

void input::set_exit_key(int key)
{
	SetExitKey(key);
}

bool input::window_should_close()
{
	return WindowShouldClose();
}
