#pragma once

class gfx
{
public:
	static void init(Vector2 resolution, const std::string& window_title);
	static void set_target_fps(int fps);
	static void prepare();
	static void present();
	static void draw_fps(Vector2 pos);

	static Color reset_col;
};
