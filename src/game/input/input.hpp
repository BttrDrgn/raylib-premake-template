#pragma once

class input
{
public:
	enum class state_t : std::uint8_t
	{
		RELEASED,
		PRESSED,
		HELD,
	};

	struct button_t
	{
		std::vector<int> buttons;
		state_t state = state_t::RELEASED;
		state_t previous_state = state_t::RELEASED;
		float frames = 0;
		float considered_held = 0.05f;
	};

	struct key_t : button_t
	{
		bool check()
		{
			for (const auto button : this->buttons)
			{
				if (IsKeyDown(button))
				{
					return true;
				}
			}

			return false;
		};
	};

	struct mouse_t : button_t
	{
		bool check()
		{
			for (const auto button : this->buttons)
			{
				if (IsMouseButtonDown(button))
				{
					return true;
				}
			}

			return false;
		};
	};

	static void init();
	static void begin();
	static void end();
	static void register_key(const std::string& key_key, std::vector<int> buttons);
	static void register_mouse(const std::string& mouse_key, std::vector<int> buttons);
	static bool pressed(const std::string& key);

	//Wrapper funcs
	static void set_exit_key(int key);
	static bool window_should_close();

	static Vector2 cursor_pos;
	static Vector2 prev_cursor_pos;

	static std::unordered_map<std::string, input::key_t> keys;
	static std::unordered_map<std::string, input::mouse_t> mouse_buttons;
};
