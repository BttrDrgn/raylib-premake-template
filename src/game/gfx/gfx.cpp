#include "gfx.hpp"

void gfx::init(Vector2 resolution, const std::string& window_title)
{
	InitWindow(resolution.x, resolution.y, window_title.c_str());
}

void gfx::set_target_fps(int fps)
{
	SetTargetFPS(fps);
}

void gfx::prepare()
{
	BeginDrawing();
	ClearBackground(gfx::reset_col);
}

void gfx::present()
{
	EndDrawing();
}

void gfx::draw_fps(Vector2 pos)
{
	DrawFPS(pos.x, pos.y);
}

Color gfx::reset_col{};
