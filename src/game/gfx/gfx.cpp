#include "gfx/gfx.hpp"
#include "math/math.hpp"

void gfx::init(Vector2 resolution, const std::string& window_title)
{
	InitWindow(resolution.x, resolution.y, window_title.c_str());
}

void gfx::register_image(std::string path, bool forced)
{
	if (path == "") return;
	path = std::format("data/gfx/{}.png", path);

	if (!std::filesystem::exists(path))
	{
		std::printf("[ ERROR ] The image \"%s\" does not exist!\n", path.c_str());
		return;
	}

	if (gfx::get_image(path).data != 0)
	{
		std::printf("[ WARNING ] An image with the key \"%s\" already exists\n", path.c_str());
		return;
	}

	//Load into ram for quick access
	Image image = LoadImage(path.c_str());
	image_t new_image;
	new_image.src = image;
	new_image.forced = forced;
	gfx::textures_ram.emplace_back(path, new_image);
}

void gfx::load_texture(std::string path, bool forced)
{
	if (path == "") return;
	path = std::format("data/gfx/{}.png", path);

	if (gfx::get_image(path).data == 0)
	{
		std::printf("[ WARNING ] Image with key \"%s\" does not exist\n", path.c_str());
		return;
	}

	//Load into vram for drawing
	Texture2D texture = LoadTextureFromImage(gfx::get_image(path));
	texture_t new_texture;
	new_texture.src = texture;
	new_texture.forced = forced;
	gfx::textures.emplace_back(path, new_texture);
}

void gfx::flush_textures()
{
	//Wipe vram
	for (auto i = 0; i < gfx::textures.size(); ++i)
	{
		if (gfx::textures[i].second.forced) continue;
		UnloadTexture(gfx::textures[i].second.src);
		gfx::textures.erase(gfx::textures.begin() + i);
	}
}

void gfx::flush_textures_ram()
{
	//Wipe ram
	for (auto i = 0; i < gfx::textures_ram.size(); ++i)
	{
		if (gfx::textures_ram[i].second.forced) continue;
		UnloadImage(gfx::textures_ram[i].second.src);
		gfx::textures_ram.erase(gfx::textures_ram.begin() + i);
	}
}

Texture2D gfx::get_texture(std::string path)
{
	path = std::format("data/gfx/{}.png", path);

	for (auto texture : gfx::textures)
	{
		if (texture.first == path)
		{
			return texture.second.src;
		}
	}

	return Texture2D{};
}

Image gfx::get_image(const std::string& path)
{
	for (auto image : gfx::textures_ram)
	{
		if (image.first == path)
		{
			return image.second.src;
		}
	}

	return Image{};
}

//Wrapper funcs
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
	if (gfx::show_fps)
	{
		gfx::draw_fps({ 10, 10 });
	}

	EndDrawing();
}

void gfx::draw_fps(Vector2 pos)
{
	DrawFPS(pos.x, pos.y);
}

void gfx::draw_texture(Texture2D texture, Rectangle src, Rectangle dest, bool scale, Vector2 origin, float rot, Color tint)
{
	if (scale)
	{
		dest = math::scale_rect(dest);
	}

	if (src.width == 0 && src.height == 0)
	{
		src.width = texture.width;
		src.height = texture.height;
	}

	if (origin.x == FLT_MAX && origin.y == FLT_MAX)
	{
		origin.x = (dest.width / 2);
		origin.y = (dest.height / 2);
	}

	DrawTexturePro(texture, src, dest, origin, rot, tint);
}

void gfx::draw_texture(const std::string& key, Rectangle src, Rectangle dest, bool scale, Vector2 origin, float rot, Color tint)
{
	gfx::draw_texture(gfx::get_texture(key), src, dest, scale, origin, rot, tint);
}

float gfx::get_frame_time()
{
	return GetFrameTime();
}

void gfx::draw_rectangle(Rectangle rect, bool scale, Color color)
{
	if (scale)
	{
		rect = math::scale_rect(rect);
	}

	DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, color);
}

void gfx::draw_rectangle_f(Rectangle rect, bool scale, Color color)
{
	if (scale)
	{
		rect = math::scale_rect(rect);
	}

	DrawRectangleRec(rect, color);
}

void gfx::draw_rectangle_r(Rectangle rect, float rot, bool scale, Color color, Vector2 origin)
{
	if (scale)
	{
		rect = math::scale_rect(rect);
	}

	color.a -= 150;

	DrawRectanglePro(rect, origin, rot, color);
}

void gfx::draw_text(const std::string& text, Vector2 pos, align_t alignment, bool scale, int pt_size, Color color)
{
	switch (alignment)
	{
		case align_t::center:
			pos.x -= MeasureText(text.c_str(), pt_size) / 2;
			break;

		case align_t::right:
			pos.x -= MeasureText(text.c_str(), pt_size);
			break;
	}

	DrawText(text.data(), pos.x, pos.y, pt_size, color);
}

void gfx::draw_text(const char* text, Vector2 pos, align_t alignment, bool scale, int pt_size, Color color)
{
	switch (alignment)
	{
	case align_t::center:
		pos.x -= MeasureText(text, pt_size) / 2;
		break;

	case align_t::right:
		pos.x -= MeasureText(text, pt_size);
		break;
	}

	DrawText(text, pos.x, pos.y, pt_size, color);
}

void gfx::draw_ellipse(Vector2 center, float radius, bool scale, Color color)
{
	if (scale)
	{
		center = math::scale_vector2(center);
	}

	DrawCircleLines(center.x, center.y, radius, color);
}

void gfx::draw_ellipse_f(Vector2 center, float radius, bool scale, Color color)
{
	if (scale)
	{
		center = math::scale_vector2(center);
	}

	DrawCircleV(center, radius, color);
}

void gfx::draw_line(Vector2 start, Vector2 end, Color color)
{
	DrawLineV(start, end, color);
}

void gfx::toggle_fullscreen()
{
	ToggleFullscreen();
}

int gfx::get_current_monitor()
{
	return GetCurrentMonitor();
}

float gfx::get_monitor_refresh_rate(int monitor)
{
	return GetMonitorRefreshRate(monitor);
}

int* gfx::get_monitor_res(int monitor)
{
	int res[2];
	res[0] = GetMonitorWidth(monitor);
	res[1] = GetMonitorWidth(monitor);
	return res;
}

Color gfx::reset_col;
bool gfx::show_fps;

std::vector<std::pair<std::string, gfx::image_t>> gfx::textures_ram;
std::vector<std::pair<std::string, gfx::texture_t>> gfx::textures;
