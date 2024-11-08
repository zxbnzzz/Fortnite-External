#pragma once

class menu_drawing_t
{
public:
	fvector2d p;

	void SimpleBox(int x, int y, ImColor color, const char* str, const char* key, bool v)
	{
		ImFont a;
		std::string utf_8_2 = str;
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 1 + 15, p.y + y + 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_2.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x - 1 + 15, p.y + y - 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_2.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 1 + 15, p.y + y - 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_2.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x - 1 + 15, p.y + y + 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_2.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 15, p.y + y + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());

		std::string utf_8_22 = key;
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 1 - 5, p.y + y + 1 - 6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_22.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x - 1 - 5, p.y + y - 1 - 6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_22.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 1 - 5, p.y + y - 1 - 6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_22.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x - 1 - 5, p.y + y + 1 - 6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_22.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x - 5, p.y + y - 6), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_22.c_str());

		if (v) {
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 1 + 160, p.y + y + 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), "ON");
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x - 1 + 160, p.y + y - 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), "ON");
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 1 + 160, p.y + y - 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), "ON");
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x - 1 + 160, p.y + y + 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), "ON");
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 160, p.y + y - 6), ImGui::ColorConvertFloat4ToU32(ImColor(0, 255, 0, 255)), "ON");

		}
		if (!v) {
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 1 + 160, p.y + y + 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), "OFF");
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x - 1 + 160, p.y + y - 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), "OFF");
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 1 + 160, p.y + y - 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), "OFF");
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x - 1 + 160, p.y + y + 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), "OFF");
			ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 160, p.y + y - 6), ImGui::ColorConvertFloat4ToU32(ImColor(255, 0, 0, 255)), "OFF");
		}
	}

	void SimpleText(int x, int y, ImColor color, const char* str)
	{
		ImFont a;
		std::string utf_8_2 = str;
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 1 + 15, p.y + y + 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_2.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x - 1 + 15, p.y + y - 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_2.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 1 + 15, p.y + y - 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_2.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x - 1 + 15, p.y + y + 1 + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_2.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.x + x + 15, p.y + y + -6), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());
	}
}; menu_drawing_t menu_drawing;