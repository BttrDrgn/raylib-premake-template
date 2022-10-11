#include "input.hpp"
#include "system/system.hpp"

void input::init()
{
	input::set_exit_key(KEY_NULL);

	input::register_key("up", { KEY_W });
	input::register_key("down", { KEY_S });
	input::register_key("left", { KEY_A });
	input::register_key("right", { KEY_D });
	input::register_key("escape", { KEY_ESCAPE });
	input::register_key("alt", { KEY_LEFT_ALT, KEY_RIGHT_ALT });
	input::register_key("enter", { KEY_ENTER });

	input::register_mouse("left", { MOUSE_BUTTON_LEFT });
}

void input::begin()
{
	for (auto& key : input::keys)
	{
		if (key.second.check())
		{
			key.second.frames += system::frame_time;
		}
		else
		{
			key.second.frames = 0.0f;
		}

		if (key.second.frames == 0 && key.second.state != state_t::RELEASED)
		{
			key.second.state = state_t::RELEASED;
		}
		else if (key.second.frames > 0 && key.second.frames < key.second.considered_held && key.second.state != state_t::PRESSED)
		{
			key.second.state = state_t::PRESSED;
		}
		else if (key.second.frames > 0 && key.second.state != state_t::HELD)
		{
			key.second.state = state_t::HELD;
		}
	}

	for (auto& mouse : input::mouse_buttons)
	{
		if (mouse.second.check())
		{
			mouse.second.frames += system::frame_time;
		}
		else
		{
			mouse.second.frames = 0.0f;
		}

		if (mouse.second.frames == 0 && mouse.second.state != state_t::RELEASED)
		{
			mouse.second.state = state_t::RELEASED;
		}
		else if (mouse.second.frames > 0 && mouse.second.frames < mouse.second.considered_held && mouse.second.state != state_t::PRESSED)
		{
			mouse.second.state = state_t::PRESSED;
		}
		else if (mouse.second.frames > 0 && mouse.second.state != state_t::HELD)
		{
			mouse.second.state = state_t::HELD;
		}
	}

	input::cursor_pos = GetMousePosition();
}

void input::end()
{
	for (auto& key : input::keys)
	{
		key.second.previous_state = key.second.state;
	}

	for (auto& mouse : input::mouse_buttons)
	{
		mouse.second.previous_state = mouse.second.state;
	}

	input::prev_cursor_pos = input::cursor_pos;
}

void input::register_key(const std::string& key_key, std::vector<int> buttons)
{
	input::key_t new_key;
	new_key.buttons = buttons;
	input::keys.emplace(key_key, new_key);
}

void input::register_mouse(const std::string& mouse_key, std::vector<int> buttons)
{
	input::mouse_t new_mouse;
	new_mouse.buttons = buttons;
	input::mouse_buttons.emplace(mouse_key, new_mouse);
}

bool input::pressed(const std::string& key)
{
	return input::keys[key].state >= input::state_t::PRESSED && input::keys[key].previous_state == input::state_t::RELEASED;
}

//Wrapper funcs
void input::set_exit_key(int key)
{
	SetExitKey(key);
}

bool input::window_should_close()
{
	return WindowShouldClose();
}

Vector2 input::cursor_pos;
Vector2 input::prev_cursor_pos;
std::unordered_map<std::string, input::key_t> input::keys;
std::unordered_map<std::string, input::mouse_t> input::mouse_buttons;
