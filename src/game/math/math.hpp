#pragma once

#include "gfx/gfx.hpp"
#include "input/input.hpp"
#define M_PI 3.14159265358979323846264338327950288

class math final
{
public:
	static float timestep(float framerate)
	{
		return (60.0f / framerate);
	}

	static float framelimit(std::uint32_t framelimit)
	{
		return 1000 / framelimit;
	}

	static float scale_width(float width, float render_width)
	{
		return (width / 1920.0f) * render_width;
	}

	static float scale_height(float height,float render_height)
	{
		return (height / 1080.0f) * render_height;
	}

	static float scale_width(float width)
	{
		return scale_width(width, gfx::resolution.x);
	}

	static float scale_height(float height)
	{
		return scale_height(height, gfx::resolution.y);
	}

	static Rectangle scale_rect(Rectangle rect)
	{
		rect.x = rect.x;
		rect.y = rect.y;
		rect.width = math::scale_width(rect.width);
		rect.height = math::scale_height(rect.height);
		return rect;
	}

	static Vector2 scale_vector2(Vector2 vec)
	{
		Vector2 retn;
		retn.x = scale_width(vec.x);
		retn.y = scale_height(vec.y);
		return retn;
	}

	static double rad2deg()
	{
		return 360.0 / (M_PI * 2.0);
	}

	static double deg2rad()
	{
		return (M_PI * 2) / 360;
	}

	static Vector2 normalize(Vector2 in)
	{
		return Vector2Normalize(in);
	}

	static float get_angle(Vector2 v1, Vector2 v2)
	{
		return Vector2Angle(v1, v2);
	}

	static float get_angle(Vector2 input)
	{
		return std::atan2(input.y, input.x) * rad2deg() + 90.0f;
	}

	static double length(double fx, double fy, double tx, double ty)
	{
		double a = std::abs(fx - tx);
		double b = std::abs(fy - ty);

		return std::sqrt((a * a) + (b * b));
	}

	static double length(Vector2 from, Vector2 to)
	{
		return length(from.x, from.y, to.x, to.y);
	}

	static Vector2 vector2_invert(Vector2 input)
	{
		return { input.y, input.x };
	}

	static Vector2 normalize_angle(float angle, bool to_rad = true)
	{
		if (to_rad) angle *= deg2rad();
		return {std::cos(angle), std::sin(angle)};
	}

	static Vector2 vector2_abs(Vector2 input)
	{
		return { std::abs(input.x), std::abs(input.y) };
	}

	static float length(Vector2 input)
	{
		return std::sqrt((input.x * input.x) + (input.y * input.y));
	}

	static float rotate_towards(Vector2 obj_0, Vector2 obj_1)
	{
		Vector2 angle = { 0.0f, 0.0f };

		angle.x = obj_1.x - obj_0.x;
		angle.y = obj_1.y - obj_0.y;

		return std::atan2(angle.y, angle.x) * 180 / 3.141;;
	}

	static void set_flag(std::uint32_t* storage, std::uint32_t flag)
	{
		if(!math::get_flag(storage, flag)) *storage |= flag;
	}

	static void unset_flag(std::uint32_t* storage, std::uint32_t flag)
	{
		if(math::get_flag(storage, flag)) *storage &= ~flag;
	}

	static bool get_flag(std::uint32_t* storage, std::uint32_t flag)
	{
		return (*storage & flag) == flag;
	}

	static char itoc(int start, int offset)
	{
		return '\0' + start + offset;
	}

	static bool is_uppercase(char c)
	{
		return (c >= 65 && c <= 90);
	}

	static bool is_lowercase(char c)
	{
		return (c >= 97 && c <= 122);
	}

	static bool collision(Rectangle item_0, Rectangle item_1)
	{
		bool x = (item_0.x - (item_0.width / 2) >= item_1.x - (item_1.width / 2)) &&
			(item_0.x + (item_0.width / 2) <= item_1.x + (item_1.width / 2));
		bool y = (item_0.y - (item_0.height / 2) >= item_1.y - (item_1.height / 2)) &&
			(item_0.y + (item_0.height / 2) <= item_1.y + (item_1.height / 2));

		return x && y;
	}

	static bool rotation_collision_cr(Vector2 circle, float size, Rectangle rect, float rotation)
	{
		float angle = -rotation * math::deg2rad();

		Vector2 unrotated =
		{
			std::cos(angle) * (circle.x - rect.x) - std::sin(angle) * (circle.y - rect.y) + rect.x,
			std::sin(angle) * (circle.x - rect.x) + std::cos(angle) * (circle.y - rect.y) + rect.y
		};

		Vector2 closest;
		if (unrotated.x < rect.x) closest.x = rect.x;
		else if (unrotated.x > rect.x + rect.width) closest.x = rect.x + rect.width;
		else closest.x = unrotated.x;

		if (unrotated.y < rect.y) closest.y = rect.y;
		else if (unrotated.y > rect.y + rect.height) closest.y = rect.y + rect.height;
		else closest.y = unrotated.y;

		if (math::length(unrotated, closest) < size)
		{
			return true;
		}

		return false;
	}

	static bool mouse_collision(Rectangle item)
	{
		Rectangle mouse;
		mouse.x = input::cursor_pos.x;
		mouse.y = input::cursor_pos.y;
		mouse.width = 1;
		mouse.height = 1;

		return collision(mouse, item);
	}

	static bool is_on_screen(Rectangle rect)
	{
		return !(rect.x < -rect.width * 4 || rect.x - rect.width * 4 > gfx::resolution.x || rect.y < -rect.height * 4 || rect.y - rect.height * 4 > gfx::resolution.y);
	}

	static bool is_on_screen(Vector2 loc, float size)
	{
		return !(loc.x < -size * 4 || loc.x - size * 4 > gfx::resolution.x || loc.y < -size * 4 || loc.y - size * 4 > gfx::resolution.y);
	}

	static bool is_on_screen(Vector2 loc, Vector2 size)
	{
		return !(loc.x < -size.x * 4 || loc.x - size.x * 4 > gfx::resolution.x || loc.y < -size.y * 4 || loc.y - size.y * 4 > gfx::resolution.y);
	}

	static int rectcmp(Rectangle rect_0, Rectangle rect_1)
	{
		if (
			rect_0.x == rect_1.x &&
			rect_0.y == rect_1.y &&
			rect_0.width == rect_1.width &&
			rect_0.height == rect_1.height
		)
		{
			return 0;
		}

		return 1;
	}

	static int vector2cmp(Vector2 vec_0, Vector2 vec_1)
	{
		if (
			vec_0.x == vec_1.x &&
			vec_0.y == vec_1.y
		)
		{
			return 0;
		}

		return 1;
	}

	static bool is_num(const std::string& input)
	{
		char* p;
		strtol(input.c_str(), &p, 10);
		return *p == 0;
	}
};
