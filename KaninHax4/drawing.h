#pragma once
#include <imgui/imgui.h>
#include <imgui/examples/imgui_impl_dx9.h>
#include <imgui/imgui_internal.h>
#include "settings.h"
#include "sdk.h"
#include "math.h"
#include "remove_sight_blur.h"

bool show_menu = true;

namespace surface
{
	namespace fonts
	{
		unsigned int arial;
		void setup()
		{
			interfaces::vgui_surface->set_font_glyph_set(arial = interfaces::vgui_surface->create_font(), "Arial", 15, 10, 10, 0, 0);
		}
	}
	namespace drawing
	{
		void draw_outlined_rect(int x, int y, int xx, int yy, int r, int g, int b, int a)
		{
			interfaces::vgui_surface->draw_set_color(r, g, b, a);
			interfaces::vgui_surface->draw_outlined_rect(x, y, xx, yy);
		}
		void draw_filled_rect(int x, int y, int xx, int yy, int r, int g, int b, int a)
		{
			interfaces::vgui_surface->draw_set_color(r, g, b, a);
			interfaces::vgui_surface->draw_filled_rect(x, y, xx, yy);
		}
		void draw_line(int x, int y, int xx, int yy, int r, int g, int b, int a)
		{
			interfaces::vgui_surface->draw_set_color(r, g, b, a);
			interfaces::vgui_surface->draw_line(x, y, xx, yy);
		}
		void draw_string(int x, int y, unsigned int font, int r, int g, int b, int a, const wchar_t* text)
		{
			interfaces::vgui_surface->draw_set_text_pos(x, y);
			interfaces::vgui_surface->draw_set_text_color(r, g, b, a);
			interfaces::vgui_surface->draw_set_text_font(font);
			interfaces::vgui_surface->draw_print_text(text, std::wcslen(text));
		}
		void draw_textured_poly(int vertex_count, vertex_t* vertices, int r, int g, int b, int a)
		{
			static int texture_id = interfaces::vgui_surface->create_new_texture_id(true);
			static unsigned char buf[4] = { 255, 255, 255, 255 };
			interfaces::vgui_surface->draw_set_texture_rgba(texture_id, buf, 1, 1);
			interfaces::vgui_surface->draw_set_color(r, g, b, a);
			interfaces::vgui_surface->draw_set_texture(texture_id);
			interfaces::vgui_surface->draw_textured_polygon(vertex_count, vertices);
		}
		void draw_filled_circle(vector2_t center, int r, int g, int b, int a, float radius, int points)
		{
			std::vector<vertex_t> vertices;
			float step = pi * 2.0f / points;

			for (float a = 0; a < (pi * 2.0f); a += step)
				vertices.push_back(vertex_t(vector2_t(radius * cosf(a) + center.x, radius * sinf(a) + center.y)));

			draw_textured_poly((int)points, vertices.data(), r, g, b, a);
		}
		void draw_polyline(int* x, int* y, int r, int g, int b, int a, int num_points)
		{
			interfaces::vgui_surface->draw_set_color(r, g, b, a);
			interfaces::vgui_surface->draw_polyline(x, y, num_points);
		}
		void draw_outlined_circle(vector2_t centre, int r, int g, int b, int a, float radius, int points)
		{
			float step = (pi * 2) / float(points);
			std::vector<int> x_positions, y_positions;
			for (float i = 0; i < pi * 2; i += step)
			{
				x_positions.push_back(radius * cosf(i) + centre.x); //quick maths
				y_positions.push_back(radius * sinf(i) + centre.y); //quick maths 2
																	/*surface->draw_line(
																	radius * cosf(i) + centre.x,
																	radius * sinf(i) + centre.y,
																	radius * cosf(i + step) + centre.x,
																	radius * sinf(i + step) + centre.x);*/
			}
			draw_polyline(x_positions.data(), y_positions.data(), r, g, b, a, points);
		}
		class draw_object_t
		{
		public:
			virtual void draw()//replace this in derived classes :)
			{
				std::cout << "[draw_object_t::draw()] original called!" << std::endl;
			}
		};
		class draw_outlined_box_t : public draw_object_t
		{
		public:
			int x, y, xx, yy, r, g, b, a;
			virtual void draw() override
			{
				std::cout << "[draw_outlined_box_t::draw()] drawing box..." << std::endl;
				draw_outlined_rect(x, y, xx, yy, r, g, b, a);
			}
			draw_outlined_box_t(int _x, int _y, int _xx, int _yy, int _r, int _g, int _b, int _a)
			{
				this->x = _x;
				this->y = _y;
				this->xx = _xx;
				this->yy = _yy;
				this->r = _r;
				this->g = _g;
				this->b = _b;
				this->a = _a;
			}
		};
		class draw_filled_box_t : public draw_object_t
		{
		public:
			int x, y, xx, yy, r, g, b, a;
			virtual void draw() override
			{
				draw_filled_rect(x, y, xx, yy, r, g, b, a);
			}
			draw_filled_box_t(int _x, int _y, int _xx, int _yy, int _r, int _g, int _b, int _a)
			{
				this->x = _x;
				this->y = _y;
				this->xx = _xx;
				this->yy = _yy;
				this->r = _r;
				this->g = _g;
				this->b = _b;
				this->a = _a;
			}
		};
		class draw_line_t : public draw_object_t
		{
		public:
			int x, y, xx, yy, r, g, b, a;
			virtual void draw() override
			{
				draw_line(x, y, xx, yy, r, g, b, a);
			}
			draw_line_t(int _x, int _y, int _xx, int _yy, int _r, int _g, int _b, int _a)
			{
				this->x = _x;
				this->y = _y;
				this->xx = _xx;
				this->yy = _yy;
				this->r = _r;
				this->g = _g;
				this->b = _b;
				this->a = _a;
			}
		};
		class draw_text_t : public draw_object_t
		{
		public:
			int x, y, r, g, b, a;
			virtual void draw() override
			{

			}
		};
		class draw_circle_t : public draw_object_t
		{
		public:
			int x, y, r, g, b, a;
			virtual void draw() override
			{

			}
		};
		class draw_textured_poly_t : public draw_object_t
		{
		public:
			vertex_t* vertices;
			int num_of_points;
			int r, g, b, a;
			virtual void draw() override
			{
				draw_textured_poly(num_of_points, vertices, r, g, b, a);
			}
			draw_textured_poly_t(vertex_t* _vertices, int _num_of_points, int _r, int _g, int _b, int _a)
			{
				this->vertices = _vertices;
				this->num_of_points = _num_of_points;
				this->r = _r;
				this->g = _g;
				this->b = _b;
				this->a = _a;
			}

		};
		class draw_polyline_t : public draw_object_t
		{
		public:
			std::vector<int> x, y;
			int num_of_points;
			int r, g, b, a;
			virtual void draw() override
			{
				draw_polyline(x.data(), y.data(), r, g, b, a, num_of_points);
			}
			draw_polyline_t(std::vector<int> _x, std::vector<int> _y, int _num_of_points, int _r, int _g, int _b, int _a)
			{
				_x = x;
				_y = y;
				this->num_of_points = _num_of_points;
				this->r = _r;
				this->g = _g;
				this->b = _b;
				this->a = _a;
			}

		};
		std::deque<draw_object_t*> drawing_queue = {};
		void on_paint_traverse()
		{
			int queued_objects = drawing_queue.size();
			while (queued_objects)
			{
				queued_objects--; //index == size - 1. subtract so first index isn't first + 1
				auto item_to_draw = drawing_queue[queued_objects];
				item_to_draw->draw();
				delete item_to_draw;
				drawing_queue.pop_back();
			}
		}
	}
}

namespace directx
{
	namespace fonts
	{
		LPD3DXFONT arial;
		LPD3DXFONT times_new_roman;
		void create()
		{
			D3DXCreateFont(interfaces::d3d_device, 16, 0, FW_DONTCARE, 1, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &arial);
			D3DXCreateFont(interfaces::d3d_device, 16, 0, FW_DONTCARE, 1, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Times New Roman", &times_new_roman);
		}
	}
	namespace lines
	{
		ID3DXLine *line;
		void create()
		{
			D3DXCreateLine(interfaces::d3d_device, &line);
		}
	}
	namespace drawing
	{
		void draw_string(int _x, int _y, D3DCOLOR _color, const char *_text, LPD3DXFONT _font)
		{
			if (!_font)
				return;
			RECT rect;
			SetRect(&rect, _x, _y, _x, _y);
			_font->DrawTextA(NULL, _text, -1, &rect, DT_NOCLIP | DT_CENTER, _color);
		}
		void draw_line(int _x, int _y, int _xx, int _yy, float _width, D3DCOLOR _color)
		{
			D3DXVECTOR2 pos[] = { D3DXVECTOR2(_x, _y), D3DXVECTOR2(_xx, _yy) };
			lines::line->Begin();
			lines::line->Draw(pos, 2, _color);
			lines::line->End();
			lines::line->Release();
		}
		void draw_box(int _x, int _y, int _height, int _width, D3DCOLOR _color)
		{
			D3DXVECTOR2 pos[] = { D3DXVECTOR2(_x, _y), D3DXVECTOR2(_x, _y + _height), D3DXVECTOR2(_x + _width, _y + _height), D3DXVECTOR2(_x + _width, _y) };
			lines::line->Begin();
			lines::line->Draw(pos, 4, _color);
			lines::line->End();
			lines::line->Release();
		}
		void draw_cursor(int _size, D3DCOLOR _color)
		{
			POINT pos;
			GetCursorPos(&pos);
			draw_line(pos.x - _size, pos.y, pos.x + _size, pos.y, 1, _color);
			draw_line(pos.x, pos.y - _size, pos.x, pos.y + _size, 1, _color);
		}
	}
	void on_lost()
	{
		if (fonts::arial)
			fonts::arial->OnLostDevice();
		if (fonts::times_new_roman)
			fonts::times_new_roman->OnLostDevice();
		if (lines::line)
			lines::line->OnLostDevice();
	}
	void on_reset()
	{
		if (fonts::arial)
			fonts::arial->OnResetDevice();
		if (fonts::times_new_roman)
			fonts::times_new_roman->OnResetDevice();
		if (lines::line)
			lines::line->OnResetDevice();
	}
	namespace im_gui
	{
		namespace styles
		{
			std::unordered_map<std::string, ImGuiStyle> styles = {};
			void setup()
			{
				styles["extasy"].WindowPadding = ImVec2(15, 15);
				styles["extasy"].WindowRounding = 5.0f;
				styles["extasy"].FramePadding = ImVec2(5, 5);
				styles["extasy"].FrameRounding = 4.0f;
				styles["extasy"].ItemSpacing = ImVec2(12, 8);
				styles["extasy"].ItemInnerSpacing = ImVec2(8, 6);
				styles["extasy"].IndentSpacing = 25.0f;
				styles["extasy"].ScrollbarSize = 15.0f;
				styles["extasy"].ScrollbarRounding = 9.0f;
				styles["extasy"].GrabMinSize = 5.0f;
				styles["extasy"].GrabRounding = 3.0f;
				styles["extasy"].Colors[ImGuiCol_Text] = ImVec4(0.8f, 0.f, 0.5f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_WindowBg] = ImVec4(1.f, 1.f, 1.f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.f, 1.f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 1.f, 0.88f);
				styles["extasy"].Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
				styles["extasy"].Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 1.f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.7f, 0.23f, 1.f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.7f, 1.f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 1.f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 1.f, 0.75f);
				styles["extasy"].Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 1.f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 1.f, 0.31f);
				styles["extasy"].Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 1.f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 1.f, 1.00f);
				//styles["extasy"].Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 1.f, 0.21f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
				styles["extasy"].Colors[ImGuiCol_SliderGrab] = ImVec4(1.f, 0.80f, 0.83f, 0.31f);
				styles["extasy"].Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.f, 1.f, 0.07f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 1.f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 1.f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 1.f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				styles["extasy"].Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
				//styles["extasy"].Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
				//styles["extasy"].Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
				//styles["extasy"].Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
				styles["extasy"].Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
				styles["extasy"].Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
				styles["extasy"].Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
				styles["extasy"].Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
			}
		}
	}
}

const char* aimbot_targeting_methods[] = { "closest to crosshair", "closest to me" };
const char* esp_line_starting_points[] = { "top", "bot", "left", "right", "crosshair"};
const char* anti_aim_names_y[] = { "slow spin", "fast spin", "fake backwards" };
const char* anti_aim_names_x[] = { "up", "down" };
char client_ip[20] = "192.168.0.40";

void draw_menu()
{
	if (!show_menu)
		return;
	ImGui_ImplDX9_NewFrame();

	ImGui::GetIO().MouseDrawCursor = true;

	ImGui::Begin("behead niggers v4");
	{
		ImGui::Checkbox("esp", &menu_tabs::show_esp_menu);
		ImGui::Checkbox("aimbot", &menu_tabs::show_aimbot_menu);
		ImGui::Checkbox("misc", &menu_tabs::show_misc_menu);
		ImGui::Checkbox("anti aim", &menu_tabs::show_anti_aim_menu);
		ImGui::Checkbox("triggerbot", &menu_tabs::show_triggerbot_menu);
	}
	ImGui::End();

	if (menu_tabs::show_esp_menu)
	{
		ImGui::Begin("esp");
		{
			ImGui::Checkbox("esp enabled", &current_settings.esp_enabled);
			ImGui::Checkbox("boxes", &current_settings.esp_boxes);
			ImGui::Checkbox("lines", &current_settings.esp_lines);
			ImGui::Checkbox("health", &current_settings.esp_health);
			ImGui::Checkbox("esp visibility check", &current_settings.esp_visibility_check);
			ImGui::Checkbox("item names", &current_settings.esp_prop_names);
			ImGui::ListBox("esp line starting point", &current_settings.esp_line_start, esp_line_starting_points, 5);
			ImGui::ColorEdit3("enemy box color", current_settings.esp_enemy_box_color);
			ImGui::ColorEdit3("enemy line color", current_settings.esp_enemy_line_color);
			ImGui::ColorEdit3("team box color", current_settings.esp_team_box_color);
			ImGui::ColorEdit3("team line color", current_settings.esp_team_line_color);
			ImGui::ColorEdit3("enemy box visible color", current_settings.esp_enemy_box_visible_color);
			ImGui::ColorEdit3("enemy line visible color", current_settings.esp_enemy_line_visible_color);
			ImGui::ColorEdit3("team box visible color", current_settings.esp_team_box_visible_color);
			ImGui::ColorEdit3("team line visible color", current_settings.esp_team_line_visible_color);
		}
		ImGui::End();
	}

	if (menu_tabs::show_aimbot_menu)
	{
		ImGui::Begin("aimbot");
		{
			ImGui::Checkbox("aimbot enabled", &current_settings.aimbot_enabled);
			ImGui::Checkbox("aimbot smoothing enabled", &current_settings.aimbot_smoothing_enabled);
			ImGui::Checkbox("aimbot recoil control enabled", &current_settings.aimbot_rcs_enabled);
			ImGui::Checkbox("aimbot visibility check", &current_settings.aimbot_visibility_check);
			ImGui::Checkbox("target teammates", &current_settings.aimbot_target_team);
			ImGui::Checkbox("only aim when shooting", &current_settings.aimbot_aim_when_holding_shoot);
			ImGui::Checkbox("only aim when can shoot", &current_settings.aimbot_only_aim_when_can_shoot);
			ImGui::Checkbox("draw target", &current_settings.aimbot_draw_target);
			ImGui::SliderFloat("smoothing percent", &current_settings.aimbot_smooth_percent, 0.f, 100.f);
			ImGui::SliderFloat("aimbot recoil control percent", &current_settings.aimbot_rcs_percent, 0.f, 100.f);
			ImGui::SliderFloat("aimbot field of view", &current_settings.aimbot_fov, 0.f, 35.f);
			ImGui::ListBox("aimbot targeting method", &current_settings.aimbot_targeting_method, aimbot_targeting_methods, 2);
		}
		ImGui::End();
	}

	if (menu_tabs::show_misc_menu)
	{
		ImGui::Begin("misc");
		{
			ImGui::Checkbox("bunny hop", &current_settings.misc_bunnyhop);
			ImGui::Checkbox("silent aim", &current_settings.misc_silent_aim);
			ImGui::Checkbox("recoil control enabled", &current_settings.misc_rcs);
			ImGui::Checkbox("custom viewmodel fov", &current_settings.misc_viewmodel_fov_enabled);
			ImGui::Checkbox("custom fov", &current_settings.misc_fov_enabled);
			ImGui::Checkbox("fake lag enabled", &current_settings.misc_fake_lag_enabled);
			ImGui::Checkbox("radar enabled", &current_settings.misc_radar_enabled);
			ImGui::Checkbox("teleport", &current_settings.misc_teleport);
			ImGui::Checkbox("movement fix", &current_settings.misc_movementfix);

			ImGui::Text("screen size x: %d", screen_size_x);
			ImGui::Text("screen size y: %d", screen_size_y);

			ImGui::InputInt("screen size x", &screen_size_x);
			ImGui::InputInt("screen ¨size y", &screen_size_y);
			if (ImGui::Button("get screen size"))
				interfaces::vgui_surface->get_screen_size(&screen_size_x, &screen_size_y);
			if (ImGui::Button("remove sight blur"))
				remove_sight_blur();
			if (ImGui::Button("get local player"))
				local_player = reinterpret_cast<entity_t*>(interfaces::client_entity_list->get_client_entity(interfaces::engine_client->get_local_player_id()));
			ImGui::InputText("client ip", client_ip, 50);
			if (ImGui::Button("connect to cheat client"))
				hack_server::wait_for_connection(client_ip);
			if (hack_server::number_of_connections)
			{
				static char buf[256];
				ImGui::InputText("message to send", buf, 256);
				if (ImGui::Button("send message to server", ImVec2(200, 40)))
				{
					hack_server::server_print(std::string(buf));
				}
				ImGui::Checkbox("send closest enemy distance to cheat client", &current_settings.misc_client_recieve_closest_enemy_distance);
		
				if(current_settings.misc_client_recieve_closest_enemy_distance)
					ImGui::SliderFloat("interval", &current_settings.misc_client_recieve_closest_enemy_distance_interval, 0.f, 500.f);
				
				if (ImGui::Button("[test] ask cheat client to recieve closest enemy information"))
				{
					hack_server::server_print("recieve closest enemy data? (yes/no)");
					static bool is_waiting_for_client_answer = true;
					if (is_waiting_for_client_answer)
					{
						int buffer_size;
						recv(hack_server::client_socket, (char*)&buffer_size, sizeof(int), NULL);
						char* recv_buffer = new char[buffer_size + 1];
						recv(hack_server::client_socket, recv_buffer, buffer_size, NULL);
						recv_buffer[buffer_size] = '\0';

						if (!strcmp(recv_buffer, "yes"))
							current_settings.misc_client_recieve_closest_enemy_distance = true;
						else if (!strcmp(recv_buffer, "no"))
							current_settings.misc_client_recieve_closest_enemy_distance = false;
						else
							std::cout << "unknown option..." << std::endl;
					}
				}
			}
			if (ImGui::Button("unload cheat"))
				unload_cheat();
			if (ImGui::Button("[test] queue box to drawing list"))
			{
				surface::drawing::drawing_queue.push_back(new surface::drawing::draw_outlined_box_t(0, 0, 100, 500, 255, 0, 255, 255));
			}

			ImGui::SliderFloat("field of view", &current_settings.misc_fov, 0.f, 130.f);
			ImGui::SliderFloat("viewmodel field of view", &current_settings.misc_viewmodel_fov, 0.f, 130.f);
			ImGui::SliderFloat("recoil control percent", &current_settings.misc_rcs_amount, 0.f, 100.f);
			ImGui::SliderInt("fake lag amount", &current_settings.misc_fake_lag_amount, 0, 100);
			ImGui::SliderInt("radar X", &current_settings.misc_radar_x, 0, screen_size_x);
			ImGui::SliderInt("radar Y", &current_settings.misc_radar_y, 0, screen_size_y);
			ImGui::SliderFloat("radar radius", &current_settings.misc_radar_radius, 0, 500.f);
		}
		ImGui::End();
	}

	if (menu_tabs::show_anti_aim_menu)
	{
		ImGui::Begin("anti aim");
		{
			ImGui::Checkbox("anti aim enabled", &current_settings.anti_aim_enabled);
			ImGui::Checkbox("disable when shooting", &current_settings.anti_aim_disabled_when_shooting);
			ImGui::ListBox("anti aim y", &current_settings.anti_aim_y, anti_aim_names_y, 3);
			ImGui::ListBox("anti aim x", &current_settings.anti_aim_x, anti_aim_names_x, 2);
		}
		ImGui::End();
	}

	if (menu_tabs::show_triggerbot_menu)
	{
		ImGui::Begin("triggerbot");
		{
			ImGui::Checkbox("triggerbot enabled", &current_settings.triggerbot_enabled);
			ImGui::Checkbox("triggerbot target team", &current_settings.triggerbot_target_team);
			ImGui::SliderFloat("triggerbot scan lenght", &current_settings.triggerbot_scan_lenght, 0.f, 16384.f, "%.0f");
		}
		ImGui::End();
	}
	ImGui::Render();
}