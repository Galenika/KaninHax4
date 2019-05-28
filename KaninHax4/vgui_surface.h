#pragma once
#include "vector2.h"
struct vertex_t
{
	vector2_t position;
	vector2_t tex_coord;

	vertex_t() {}

	vertex_t(const vector2_t &pos, const vector2_t &coord = vector2_t(0, 0))
	{
		position = pos;
		tex_coord = coord;
	}

	void init(const vector2_t &pos, const vector2_t &coord = vector2_t(0, 0))
	{
		position = pos;
		tex_coord = coord;
	}
};

class vgui_surface_t
{
public:
	void draw_set_texture_rgba(int texture_id, unsigned char const* colors, int w, int h)
	{
		call_virtual_function<void, 37>(this, texture_id, colors, w, h);
	}
	void draw_set_texture(int texture_id)
	{
		call_virtual_function<void, 38>(this, texture_id);
	}
	int create_new_texture_id(bool procedural)
	{
		return call_virtual_function<int, 43>(this, procedural);
	}
	void draw_textured_polygon(int vertex_count, vertex_t *vtx, bool clip_vertices = true)
	{
		call_virtual_function<void, 106>(this, vertex_count, vtx, clip_vertices);
	}
	void get_screen_size(int* x, int* y)
	{
		call_virtual_function<void, 44>(this, x, y);
	}
	void draw_set_color(int r, int g, int b, int a)
	{
		call_virtual_function<void, 15>(this, r, g, b, a);
	}
	void draw_filled_rect(int x, int y, int xx, int yy)
	{
		call_virtual_function<void, 16>(this, x, y, xx, yy);
	}
	void draw_outlined_rect(int x, int y, int xx, int yy)
	{
		call_virtual_function<void, 18>(this, x, y, xx, yy);
	}
	void draw_line(int x, int y, int xx, int yy)
	{
		call_virtual_function<void, 19>(this, x, y, xx, yy);
	}
	void draw_polyline(int* x, int* y, int num_points)
	{
		call_virtual_function<void, 20>(this, x, y, num_points);
	}
	void draw_set_text_font(unsigned int font)
	{
		call_virtual_function<void, 23>(this, font);
	}
	void draw_set_text_color(int r, int g, int b, int a)
	{
		call_virtual_function<void, 25>(this, r, g, b, a);
	}
	void draw_set_text_pos(int x, int y)
	{
		call_virtual_function<void, 26>(this, x, y);
	}
	void draw_print_text(const wchar_t *text, int textLen)
	{
		call_virtual_function<void, 28>(this, text, textLen, 0);
	}
	unsigned int create_font()
	{
		return call_virtual_function<unsigned int, 71>(this);
	}
	bool set_font_glyph_set(unsigned int& font, const char *font_name, int tall, int weight, int blur, int scanlines, int flags, int range_min = 0, int range_max = 0)
	{
		return call_virtual_function<bool, 72>(this, std::reference_wrapper<unsigned int>(font), font_name, tall, weight, blur, scanlines, flags, range_min, range_max);
	}
	void get_text_size(unsigned int font, const wchar_t *text, int &wide, int &tall)
	{
		call_virtual_function<void, 79>(this, font, text, std::reference_wrapper<int>(wide), std::reference_wrapper<int>(tall));
	}
};