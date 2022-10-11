#pragma once

class gfx
{
public:
	enum class align_t : std::uint8_t
	{
		left,
		center,
		right
	};

	struct gfx_obj_t
	{
		bool forced;
	};

	//Forced means the gfx handler will not unload this texture from memory
	struct image_t : gfx_obj_t
	{
		Image src;
	};

	struct texture_t : gfx_obj_t
	{
		Texture2D src;
		bool forced;
	};

	static void register_image(std::string path, bool forced = false);
	static void load_texture(std::string path, bool forced = false);
	static void flush_textures();
	static void flush_textures_ram();
	static Image get_image(const std::string& path);
	static Texture2D get_texture(std::string path);

	//wrapper funcs
	static void init(Vector2 resolution, const std::string& window_title);
	static void set_target_fps(int fps);
	static void prepare();
	static void present();
	static void draw_fps(Vector2 pos);
	static void draw_texture(Texture2D texture, Rectangle src, Rectangle dest, bool scale, Vector2 origin = {FLT_MAX, FLT_MAX}, float rot = 0.0f, Color tint = WHITE);
	static void draw_texture(const std::string& key, Rectangle src, Rectangle dest, bool scale, Vector2 origin = { FLT_MAX, FLT_MAX }, float rot = 0.0f, Color tint = WHITE);
	static float get_frame_time();
	static void draw_rectangle(Rectangle rect, bool scale, Color color = WHITE);
	static void draw_rectangle_f(Rectangle rect, bool scale, Color color = WHITE);
	static void draw_rectangle_r(Rectangle rect, float rot, bool scale, Color color = WHITE, Vector2 origin = {});
	static void draw_text(const std::string& text, Vector2 pos, align_t alignment, bool scale, int pt_size = 24.0f, Color color = WHITE);
	static void draw_text(const char* text, Vector2 pos, align_t alignment, bool scale, int pt_size = 24.0f, Color color = WHITE);
	static void draw_ellipse(Vector2 center, float radius, bool scale, Color color = WHITE);
	static void draw_ellipse_f(Vector2 center, float radius, bool scale, Color color = WHITE);
	static void draw_line(Vector2 start, Vector2 end, Color color = WHITE);
	static void toggle_fullscreen();
	static int get_current_monitor();
	static float get_monitor_refresh_rate(int monitor);
	static int* get_monitor_res(int monitor);

	static Color reset_col;
	static Vector2 resolution;
	static bool show_fps;

	static std::vector<std::pair<std::string, image_t>> textures_ram;
	static std::vector<std::pair<std::string, texture_t>> textures;
};
