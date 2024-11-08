#include <list>
#include <string>
#include "../utils/offsets.h"
#include <string.h>
#include "../../game/render/functions.h"
#include <iostream>
#include "../../game/aimbot/aimbot.h"
#include <vector>
#include <immintrin.h>
#include "../utils/utils.h"
#include "../../framework/protection/xorstr.hpp"
#include "../../console/console.h"

inline void DrawString3(float fontSize, int x, int y, ImVec4 color, bool bCenter, bool stroke, const char* pText, ...)
{
	ImU32 converted_color = ImGui::ColorConvertFloat4ToU32(color);
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
	}
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), converted_color, text.c_str());
}

inline void DrawString2(float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, const char* pText, ...)
{

	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		/*ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());*/
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
	}
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), color, text.c_str());
}


void Draw_Text(const std::string& text, const ImVec2& pos, float size, uint32_t color, bool center)
{

	constexpr float fStrokeVal1 = 1.0f;
	uint32_t EdgeColor = 0xFF000000;

	float Edge_a = (EdgeColor >> 24) & 0xff;
	float Edge_r = (EdgeColor >> 16) & 0xff;
	float Edge_g = (EdgeColor >> 8) & 0xff;
	float Edge_b = (EdgeColor) & 0xff;
	std::stringstream steam(text);
	std::string line;
	float y = 0.0f;
	int i = 0;
	while (std::getline(steam, line))
	{
		ImVec2 textSize = ImGui::GetFont()->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());
		if (center)
		{
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x - textSize.x / 2.0f) - fStrokeVal1, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x - textSize.x / 2.0f) + fStrokeVal1, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x - textSize.x / 2.0f), (pos.y + textSize.y * i) - fStrokeVal1), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x - textSize.x / 2.0f), (pos.y + textSize.y * i) + fStrokeVal1), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), color, line.c_str());
		}
		else
		{
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x) - fStrokeVal1, (pos.y + textSize.y * i)), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x) + fStrokeVal1, (pos.y + textSize.y * i)), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x), (pos.y + textSize.y * i) - fStrokeVal1), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x), (pos.y + textSize.y * i) + fStrokeVal1), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2(pos.x, pos.y + textSize.y * i), color, line.c_str());
		}
		y = pos.y + textSize.y * (i + 1);
		i++;
	}
}


ImVec2 ScreenCenter(globals.ScreenWidth / 2, globals.ScreenHeight / 2);

enum MenuTab : int
{
	Combat = 0,
	Visuals = 1,
	Radarington = 2,
	Misc = 3,
	Settings = 4
};
MenuTab eMenuTab;

void ModuleArrayList()
{
	float fSpacing = 0.f;

	struct Module {
		std::string name;
		bool status;
	};

	std::vector<Module> modules;

	auto AddModule = [&](std::string sModuleName, bool bStatus) -> void
		{
			if (bStatus)
			{
				modules.push_back({ sModuleName, bStatus });
			}
		};

	// Combat tab
	AddModule("Aimbot", aimbot.enable);
	AddModule("Draw Fov", aimbot.drawfov);
	AddModule("Prediction", aimbot.prediction);
	AddModule("Prediction Dot", aimbot.predictiondot);
	// Visuals
	AddModule("Visuals", visuals.enable);
	AddModule("Box", visuals.box);
	AddModule("Filled Box", visuals.filled);
	AddModule("Skeleton", visuals.skeleton);
	AddModule("Distance", visuals.distance);
	AddModule("Username", visuals.username);
	AddModule("Platform", visuals.platform);
	AddModule("Weapon", visuals.weapon);
	AddModule("Rank", visuals.rank);
	AddModule("Box Outline", visuals.box_outline);
	AddModule("Skeleton Outline", visuals.skel_outline);
	// Misc
	AddModule("Menu Crosshair", menu.menu_cursor);

	// Sort the modules by name length in descending order
	std::sort(modules.begin(), modules.end(), [](const Module& a, const Module& b) {
		return a.name.length() > b.name.length(); // Descending order
		});

	for (const auto& module : modules)
	{
		auto Size = ImGui::CalcTextSize(module.name.c_str());
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(1920 - (Size.x + 10), fSpacing), ImVec2(1920, fSpacing + 20), ImColor(0, 0, 0, 160));
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(1920 - (Size.x + 10), fSpacing), ImVec2((1920 - (Size.x + 10)) + 3, fSpacing + 20), ImColor(255, 0, 0));
		ImGui::GetForegroundDrawList()->AddText(ImVec2(1920 - (Size.x + 5), fSpacing + 1), ImColor(255, 255, 255), module.name.c_str());
		fSpacing += 20.f;
	}
}

std::mutex base;

float TargetDistance = FLT_MAX;
uintptr_t TargetEntity = NULL;
uintptr_t DesyncTargetEntity = NULL;

void render_elements()
{
	// Watermark
	if (watermark.enable)
	{
		Draw_Text("athena | ud (ultra detected)", ImVec2(watermark.watermark_pos_x, watermark.watermark_pos_y), watermark.watermark_size, ImColor(255, 255, 255), watermark.center);
	}

	if (aimbot.drawfov)
	{
		bool isTargeting = read<bool>((uintptr_t)CachePointers.AcknownledgedPawn + 0x1e34);
		aimbot.fov_drawdistance = isTargeting ? aimbot.ADS_Fov_Size : aimbot.fovsize;

		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(globals.ScreenWidth / 2, globals.ScreenHeight / 2), aimbot.fovsize, ImColor(0, 0, 0), 200, 1);
	}
}

static auto RootC(uintptr_t actor) {
	return read<uintptr_t>(actor + offsets::RootComponent);
}

static auto GetLocation(uintptr_t actor) {
	return read<fvector>(RootC(actor) + offsets::RelativeLocation);
}

void CacheLevels()
{
	for (;;)
	{
		if (!world.pickups or !world.chests) continue;
		if (!CachePointers.UWorld) continue;
		std::vector<item> mrxd;
		uintptr_t ItemLevels = read<uintptr_t>(CachePointers.UWorld + world_offsets::levels); // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=Uworldnigga&member=Levels

		std::cout << "Levels - " << ItemLevels << std::endl;

		for (int i = 0; i < read<DWORD>(CachePointers.UWorld + (world_offsets::levels + sizeof(PVOID))); ++i)
		{
			uintptr_t ItemLevel = read<uintptr_t>(ItemLevels + (i * sizeof(uintptr_t)));
			
			std::cout << "ItemLevel - " << ItemLevel << std::endl;

			for (int i = 0; i < read<DWORD>(ItemLevel + (world_offsets::aactor + sizeof(PVOID))); ++i) {

				uintptr_t ItemsPawns = read<uintptr_t>(ItemLevel + world_offsets::aactor);

				std::cout << "ItemsPawns - " << ItemsPawns << std::endl;

				uintptr_t CurrentItemPawn = read<uintptr_t>(ItemsPawns + (i * sizeof(uintptr_t)));
				std::cout << "CurrentItemPawn - " << CurrentItemPawn << std::endl;

				fvector ItemPosition = GetLocation(CurrentItemPawn);

				float ItemDist = camera_postion.location.distance(ItemPosition) / 100;

				int ItemIndex = read<int>(CurrentItemPawn + 0x18);

				auto CurrentItemPawnName = decryption.get_fname(ItemIndex);

				bool shouldUpdate;
				bool bIsPickup;

				if (is_valid(CurrentItemPawn))
				{

					if (world.pickups or world.chests)
					{
						bIsPickup = true;
						shouldUpdate = true;
					}
				}

				if (shouldUpdate)
				{
					item Item{ };
					Item.Actor = CurrentItemPawn;
					Item.Name = CurrentItemPawnName;
					Item.isPickup = bIsPickup;
					Item.distance = ItemDist;

					mrxd.push_back(Item);

				}
			}
		}

		item_pawns.clear();
		item_pawns = mrxd;
		std::this_thread::sleep_for(std::chrono::seconds(world.cache_update_speed));
	}
}

enum class EFortRarity : uint8_t
{
	EFortRarity__Common = 0,
	EFortRarity__Uncommon = 1,
	EFortRarity__Rare = 2,
	EFortRarity__Epic = 3,
	EFortRarity__Legendary = 4,
	EFortRarity__Mythic = 5,
	EFortRarity__Transcendent = 6,
	EFortRarity__Unattainable = 7,
	EFortRarity__NumRarityValues = 8,
};

inline ImVec4 get_loot_color(EFortRarity tier) {
	if (tier == EFortRarity::EFortRarity__Common)
		return ImVec4(123 / 255.0f, 123 / 255.0f, 123 / 255.0f, 1.f);
	else if (tier == EFortRarity::EFortRarity__Uncommon)
		return ImVec4(58 / 255.0f, 121 / 255.0f, 19 / 255.0f, 1.f);
	else if (tier == EFortRarity::EFortRarity__Rare)
		return ImVec4(18 / 255.0f, 88 / 255.0f, 162 / 255.0f, 1.f);
	else if (tier == EFortRarity::EFortRarity__Epic)
		return ImVec4(189 / 255.0f, 63 / 255.0f, 250 / 255.0f, 1.f);
	else if (tier == EFortRarity::EFortRarity__Legendary)
		return ImVec4(255 / 255.0f, 118 / 255.0f, 5 / 255.0f, 1.f);
	else if (tier == EFortRarity::EFortRarity__Mythic)
		return ImVec4(220 / 255.0f, 160 / 255.0f, 30 / 255.0f, 1.f);
	else if (tier == EFortRarity::EFortRarity__Transcendent)
		return ImVec4(0 / 255.0f, 225 / 255.0f, 252 / 255.0f, 1.f);

	return ImVec4(123 / 255.0f, 123 / 255.0f, 123 / 255.0f, 1.f);
}

void leveldrawing()
{
	auto levelListCopy = item_pawns;

	for (auto entity : levelListCopy)
	{
		if (entity.Actor)
		{
			if (world.pickups && strstr(entity.Name.c_str(), ("FortPickupAthena")) or strstr(entity.Name.c_str(), ("Fort_Pickup_Creative_C")))
			{
				if (entity.distance <= world.loot_distace)
				{
					auto definition = read<uint64_t>(entity.Actor + 0x348 + 0x18);

					std::cout << "Def - " << definition << std::endl;

					if (is_valid(definition))
					{
						EFortRarity tier = read<EFortRarity>(definition + weapon::Tier);

						ImColor Color, RGBAColor;
						fvector Location = GetLocation(entity.Actor);

						fvector2d ChestPosition = game_helper.ProjectWorldToScreen(Location);

						if (game_helper.IsInScreen(ChestPosition))
						{
							uint64_t ftext_ptr = read<uint64_t>(definition + weapon::ItemName);

							std::cout << "FText Pointer -> " << ftext_ptr << std::endl;

							if (is_valid(ftext_ptr))
							{
								uint64_t ftext_data = read<uint64_t>(ftext_ptr + 0x28);
								int ftext_length = read<int>(ftext_ptr + 0x30);
								if (ftext_length > 0 && ftext_length < 50) {
									wchar_t* ftext_buf = new wchar_t[ftext_length];
									read1(ftext_data, ftext_buf, ftext_length * sizeof(wchar_t));
									std::wstring wstr_buf(ftext_buf);
									std::string WeaponName = std::string(wstr_buf.begin(), wstr_buf.end());
									delete[] ftext_buf;

									std::string wtf2 = WeaponName + " [" + std::to_string((int)entity.distance) + ("m]");

									ImVec2 text_size = ImGui::CalcTextSize(wtf2.c_str());

									if (tier == EFortRarity::EFortRarity__Uncommon and world.uncommon)
									{
										DrawString3(13, ChestPosition.x - (text_size.x / 2), ChestPosition.y - 18, get_loot_color(tier), false, false, wtf2.c_str());
									}
									else if (tier == EFortRarity::EFortRarity__Common and world.common)
									{
										DrawString3(13, ChestPosition.x - (text_size.x / 2), ChestPosition.y - 18, get_loot_color(tier), false, false, wtf2.c_str());
									}
									else if (tier == EFortRarity::EFortRarity__Rare and world.rare)
									{
										DrawString3(13, ChestPosition.x - (text_size.x / 2), ChestPosition.y - 18, get_loot_color(tier), false, false, wtf2.c_str());
									}
									else if (tier == EFortRarity::EFortRarity__Epic and world.epic)
									{
										DrawString3(13, ChestPosition.x - (text_size.x / 2), ChestPosition.y - 18, get_loot_color(tier), false, false, wtf2.c_str());
									}
									else if (tier == EFortRarity::EFortRarity__Legendary and world.legendary)
									{
										DrawString3(13, ChestPosition.x - (text_size.x / 2), ChestPosition.y - 18, get_loot_color(tier), false, false, wtf2.c_str());
									}
									else if (tier == EFortRarity::EFortRarity__Mythic and world.mythic)
									{
										DrawString3(13, ChestPosition.x - (text_size.x / 2), ChestPosition.y - 18, get_loot_color(tier), false, false, wtf2.c_str());
									}
								}
							}
						}
					}
				}
			}

			if (world.chests && strstr(entity.Name.c_str(), ("Tiered_Chest")))
			{
				if (entity.distance <= world.loot_distace)
				{
					fvector Location = GetLocation(entity.Actor);
					fvector2d Screen = game_helper.ProjectWorldToScreen(Location);

					if (game_helper.IsInScreen(Screen))
					{
						std::string BuiltString = "Chest [" + std::to_string((int)entity.distance) + "]";
						ImVec2 text_size = ImGui::CalcTextSize(BuiltString.c_str());

						DrawString2(13, Screen.x - (text_size.x / 2), Screen.y - 18, ImColor(255, 255, 0), false, false, BuiltString.c_str());
					}
				}
			}
		}
	}
}

void actorloop()
{
	//console.set_highest_priority();
	{
		temporary_entity_list.clear();
		std::lock_guard<std::mutex> lock(base);

		CachePointers.UWorld = read<__int64>(virtualaddy + offsets::UWorld); 
		CachePointers.GameInstance = read<uintptr_t>(CachePointers.UWorld + offsets::OwningGameInstance);
		CachePointers.LocalPlayer = read<uintptr_t>(read<uintptr_t>(CachePointers.GameInstance + offsets::LocalPlayers));
		CachePointers.PlayerController = read<uintptr_t>(CachePointers.LocalPlayer + offsets::PlayerController);
		CachePointers.AcknownledgedPawn = read<uintptr_t>(CachePointers.PlayerController + offsets::AcknowledgedPawn);
		CachePointers.Mesh = read<uintptr_t>(CachePointers.AcknownledgedPawn + offsets::Mesh);
		CachePointers.PlayerState = read<uintptr_t>(CachePointers.AcknownledgedPawn + offsets::PlayerState);
		CachePointers.RootComponent = read<uintptr_t>(CachePointers.AcknownledgedPawn + offsets::RootComponent);
		CachePointers.GameState = read<uintptr_t>(CachePointers.UWorld + offsets::GameState);
		CachePointers.PlayerArray = read<uintptr_t>(CachePointers.GameState + offsets::PlayerArray);
		CachePointers.PlayerArraySize = read<int>(CachePointers.GameState + (offsets::PlayerArray + sizeof(uintptr_t)));
		CachePointers.LocalWeapon = read<uintptr_t>(CachePointers.AcknownledgedPawn + weapon::CurrentWeapon);
	}

	TargetDistance = FLT_MAX;
	TargetEntity = NULL;
	DesyncTargetEntity = NULL;

	render_elements();

	for (int i = 0; i < CachePointers.PlayerArraySize; ++i)
	{
		uintptr_t PlayerState = read<uintptr_t>(CachePointers.PlayerArray + (i * sizeof(uintptr_t)));
		uintptr_t CurrentActor = read<uintptr_t>(PlayerState + offsets::PawnPrivate);

		if (CurrentActor == CachePointers.AcknownledgedPawn) continue;

		uintptr_t skeletalmesh = read<uintptr_t>(CurrentActor + offsets::Mesh);
		if (!skeletalmesh) continue;

		fvector base_bone = game_helper.GetBoneLocation(skeletalmesh, 0);
		if (base_bone.x == 0 && base_bone.y == 0 && base_bone.z == 0) continue;

		if (read<char>(CurrentActor + 0x758) >> 3) continue;

		uintptr_t PlayerArray = read<uintptr_t>(CachePointers.PlayerArray + i * 0x8);
		uintptr_t SkeletalMesh = read<uintptr_t>(CurrentActor + offsets::Mesh);

		fvector root_bone = game_helper.GetBoneLocation(SkeletalMesh, 0);
		fvector2d root_box1 = game_helper.ProjectWorldToScreen(fvector(root_bone.x, root_bone.y, root_bone.z - 15));

		fvector head_bone = game_helper.GetBoneLocation(SkeletalMesh, 110);
		fvector2d head_box = game_helper.ProjectWorldToScreen(fvector(head_bone.x, head_bone.y, head_bone.z + 15));
		fvector2d head = game_helper.ProjectWorldToScreen(head_bone);
		fvector2d root = game_helper.ProjectWorldToScreen(root_bone);

		float box_height = abs(head.y - root_box1.y);
		float box_width = box_height * 0.30f;
		float distance = camera_postion.location.distance(root_bone) / 100;

		float CornerHeight = abs(head_box.y - root.y);
		float CornerWidth = CornerHeight * visuals.corner_width;

		int bottom_offset = 0;
		int top_offset = 0;

		uintptr_t pawn_private1 = read<uintptr_t>(offsets::PlayerState + 0x320);

		if (distance > visuals.renderDistance && CachePointers.AcknownledgedPawn) continue;

		static ImColor box_color;
		static ImColor box_filled;

		if (game_helper.IsEnemyVisible(SkeletalMesh))
		{
			box_color = ImGui::GetColorU32({ colors.box_visible[0], colors.box_visible[1], colors.box_visible[2],  1.0f });
			box_filled = ImGui::GetColorU32({ colors.box_filled_visible[0], colors.box_filled_visible[1], colors.box_filled_visible[2], colors.box_filled_visible[3] });
		}
		else
		{
			box_color = ImGui::GetColorU32({ colors.box_invisible[0], colors.box_invisible[1], colors.box_invisible[2],  1.0f });
			box_filled = ImGui::GetColorU32({ colors.box_filled_invisible[0], colors.box_filled_invisible[1], colors.box_filled_invisible[2],  colors.box_filled_invisible[3] });
		}

		if (aimbot.enable)
		{
			double dx = head.x - (globals.ScreenWidth / 2);
			double dy = head.y - (globals.ScreenHeight / 2);
			float dist = sqrtf(dx * dx + dy * dy);

			if (aimbot.vischeck)
			{
				if (game_helper.IsEnemyVisible(SkeletalMesh))
				{
					if (dist < aimbot.fovsize && dist < TargetDistance)
					{
						TargetDistance = dist;
						TargetEntity = CurrentActor;
					}
				}
			}
			else
			{
				if (dist < aimbot.fovsize && dist < TargetDistance)
				{
					TargetDistance = dist;
					TargetEntity = CurrentActor;
				}
			}
		}

		if (visuals.box && visuals.enable)
		{
			const float halfWidth = box_width / 2.0f;
			const ImVec2 topLeft(head_box.x - halfWidth, head_box.y);
			const ImVec2 topRight(root.x + halfWidth, head_box.y);
			const ImVec2 bottomLeft(head_box.x - halfWidth, root.y);
			const ImVec2 bottomRight(root.x + halfWidth, root.y);

			const int boxThickness = visuals.box_thick;

			const ImColor outlineColor(0, 0, 0, 255);
			const int outlineThickness = visuals.box_thick;

			if (visuals.filled)
			{
				ImGui::GetBackgroundDrawList()->AddRectFilled(topLeft, bottomRight, box_filled, 0.0f, ImDrawCornerFlags_All);
			}

			if (visuals.box_outline)
			{
				ImGui::GetBackgroundDrawList()->AddRect(topLeft, bottomRight, ImColor(0, 0, 0), 0.0f, ImDrawCornerFlags_All, outlineThickness + 2.5);
			}

			ImGui::GetBackgroundDrawList()->AddRect(topLeft, bottomRight, box_color, 0.0f, ImDrawCornerFlags_All, outlineThickness);
		}


		if (visuals.distance && visuals.enable)
		{
			bottom_offset += 10;

			ImVec2 textPosition(root.x, root.y + bottom_offset);
			std::string distance_str = std::to_string(static_cast<int>(distance)) + "M";
			char buffer[128];

			sprintf_s(buffer, ("%s"), distance_str.c_str());
			Draw_Text(buffer, textPosition, 15.f, ImColor(255, 255, 255, 255), true);
		}

		if (visuals.username && visuals.enable)
		{
			ImVec2 textPosition(head_box.x, head_box.y - 30);
			std::string playerName = decryption.GetPlayerName(PlayerState);
			char buffer[128];

			sprintf_s(buffer, ("%s"), playerName.c_str());
			Draw_Text(buffer, textPosition, 15.f, ImColor(255, 255, 255, 255), true);
		}
		else if (visuals.username && visuals.distance)
		{
			ImVec2 textPosition(head_box.x, head_box.y - 30);

			std::string playerName = decryption.GetPlayerName(PlayerState);
			std::string distance_str = std::to_string(static_cast<int>(distance)) + "M";

			// Combine the username and distance into a single string
			std::string full_text = playerName + " " + "(" + distance_str + ")";

			// Draw the combined text
			Draw_Text(full_text.c_str(), textPosition, 15.f, ImColor(255, 255, 255, 255), true);
		}

		if (visuals.weapon && visuals.enable)
		{
			ImVec2 textPosition(head_box.x, head_box.y - 15);
			std::string weaponname = decryption.GetWeaponName(CurrentActor);
			if (weaponname.empty()) weaponname = "Hands";
			char buffer[128];

			sprintf_s(buffer, ("%s"), weaponname.c_str());

			Draw_Text(buffer, textPosition, 15.f, ImColor(255, 255, 255, 255), true);
		}

		if (visuals.rank && visuals.enable)
		{
			bottom_offset += 15;

			uintptr_t habenero = read<uintptr_t>(PlayerState + 0x9f0); 
			int32_t RankProgress = read<int32_t>(habenero + 0xb8 + 0x10); 

			std::string rankText = decryption.getRank(RankProgress); 
			uint32_t rankColor = ImGui::ColorConvertFloat4ToU32(decryption.getRankColor(RankProgress)); 

			Draw_Text(rankText, ImVec2(root.x, root.y + bottom_offset), ImGui::GetFontSize(), rankColor, true);
		}


		int side_offset = 0;

		if (visuals.platform && visuals.enable)
		{
			bottom_offset += 20;

			ImVec2 textPosition(root.x, root.y + bottom_offset);

			WCHAR buffer[0x30];

			handler::read_physical(read<uintptr_t*>(PlayerState + 0x3f0), buffer, sizeof(buffer));

			std::wstring ws = buffer;

			std::string PlatformName = std::string(ws.begin(), ws.end());

			ImColor PlatformColor;

			if (strstr(PlatformName.c_str(), _xor_("WIN").c_str()))
			{
				PlatformColor = ImColor(255, 255, 255, 255);

				Draw_Text("PC", textPosition, 17.f, PlatformColor, true);
			}
			else if (strstr(PlatformName.c_str(), _xor_("PSN").c_str()) || strstr(PlatformName.c_str(), _xor_("PS5").c_str()))
			{
				PlatformColor = ImColor(0, 108, 199, 255);

				Draw_Text("PSN", textPosition, 17.f, PlatformColor, true);

			}
			else if (strstr(PlatformName.c_str(), _xor_("XBL").c_str()) || strstr(PlatformName.c_str(), _xor_("XSX").c_str()))
			{
				PlatformColor = ImColor(18, 120, 16, 255);

				Draw_Text("XBOX", textPosition, 17.f, PlatformColor, true);

			}
			else if (strstr(PlatformName.c_str(), _xor_("SWT").c_str()))
			{
				PlatformColor = ImColor(223, 0, 17);

				Draw_Text("SWITCH", textPosition, 17.f, PlatformColor, true);
			}
			else if (strstr(PlatformName.c_str(), _xor_("AND").c_str()) || strstr(PlatformName.c_str(), _xor_("IOS").c_str()))
			{
				PlatformColor = ImColor(255, 255, 255, 255);

				Draw_Text("MOBILE", textPosition, 17.f, PlatformColor, true);
			}
			else
			{
				PlatformColor = ImColor(255, 255, 255, 255);

				Draw_Text(PlatformName.c_str(), textPosition, 17.f, PlatformColor, true);
			}
		}

		if (visuals.killscore)
		{
			side_offset += 15;

			ImVec2 textPosition(head_box.x + 200, head_box.y - 15 + side_offset);
			int killScore = read<int>(PlayerState + 0x1214);

			std::string killScoreStr = "Player Kills: " + std::to_string(killScore);

			Draw_Text(killScoreStr, textPosition, 15.f, ImColor(255, 255, 255, 255), true);
		}

		if (visuals.level_score)
		{
			side_offset += 15;

			ImVec2 textPosition(head_box.x + 200, head_box.y - 15 + side_offset);
			int LevelScore = read<int>(PlayerState + 0x1228);

			std::string LevelScoreStr = "Player Level: " + std::to_string(LevelScore);

			Draw_Text(LevelScoreStr, textPosition, 15.f, ImColor(255, 255, 255, 255), true);
		}

		if (visuals.chests_opened)
		{
			side_offset += 15;

			ImVec2 textPosition(head_box.x + 200, head_box.y - 15 + side_offset); // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AFortPlayerStateAthena&member=NumChestsOpened
			int ChestScore = read<int>(PlayerState + 0x126c);

			std::string ChestScoreStr = "Chests Opened: " + std::to_string(ChestScore);

			Draw_Text(ChestScoreStr, textPosition, 15.f, ImColor(255, 255, 255, 255), true);
		}

		if (visuals.minutes_alive)
		{
			side_offset += 15;

			ImVec2 textPosition(head_box.x + 200, head_box.y - 15 + side_offset);
			int MinutesScore = read<int>(PlayerState + 0x1294); // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AFortPlayerStateAthena&member=NumMinutesAlive

			std::string MinutesScoreStr = "Minutes Alive: " + std::to_string(MinutesScore);

			Draw_Text(MinutesScoreStr, textPosition, 15.f, ImColor(255, 255, 255, 255), true);
		}

		if (visuals.current_health)
		{
			side_offset += 15;

			ImVec2 textPosition(head_box.x + 200, head_box.y - 15 + side_offset);
			int HealthScore = read<int>(PlayerState + 0xdf4); // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AFortPlayerStateZone&member=CurrentHealth

			std::string HealthScoreStr = "Health: " + std::to_string(HealthScore);

			Draw_Text(HealthScoreStr, textPosition, 15.f, ImColor(255, 255, 255, 255), true);
		}

		if (visuals.current_shield)
		{
			side_offset += 15;

			ImVec2 textPosition(head_box.x + 200, head_box.y - 15 + side_offset);
			int ShieldScore = read<int>(PlayerState + 0xdfc); // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AFortPlayerStateZone&member=CurrentShield

			std::string ShieldScoreStr = "Shield: " + std::to_string(ShieldScore);

			Draw_Text(ShieldScoreStr, textPosition, 15.f, ImColor(255, 255, 255, 255), true);
		}

		if (visuals.current_spectators)
		{
			side_offset += 15;

			ImVec2 textPosition(head_box.x + 200, head_box.y - 15 + side_offset);
			int SpectatorsScore = read<int>(PlayerState + 0xb20); // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AFortPlayerStateZone&member=Spectators

			std::string SpectatorsScoreStr = "Spectators: " + std::to_string(SpectatorsScore);

			Draw_Text(SpectatorsScoreStr, textPosition, 15.f, ImColor(255, 255, 255, 255), true);
		}

		if (visuals.skeleton && visuals.enable && distance <= 50)
		{
			fvector2d bonePositions[16];
			const int boneIndices[] = { 110, 3, 66, 9, 38, 10, 39, 11, 40, 78, 71, 79, 72, 75, 82, 67 };
			for (int i = 0; i < 16; ++i)
			{
				bonePositions[i] = game_helper.ProjectWorldToScreen(game_helper.GetBoneLocation(SkeletalMesh, boneIndices[i]));
			}

			std::pair<int, int> bonePairs[] =
			{
				{1, 2}, {3, 4}, {4, 3}, {5, 3}, {6, 4}, {5, 7}, {6, 8},
				{10, 1}, {9, 1}, {12, 10}, {11, 9}, {13, 12}, {14, 11}, {2, 15}, { 15, 0 }
			};
			ImGui::GetBackgroundDrawList()->PushClipRectFullScreen();
			for (const auto& pair : bonePairs)
			{
				ImVec2 start(bonePositions[pair.first].x, bonePositions[pair.first].y);
				ImVec2 end(bonePositions[pair.second].x, bonePositions[pair.second].y);

				if (pair.first == 110)
				{
					end.y += 20;
				}

				if (visuals.skel_outline)
				{
					ImGui::GetBackgroundDrawList()->AddLine(start, end, ImColor(0, 0, 0, 255), visuals.skeleton_thickness + 2);
				}

				ImGui::GetBackgroundDrawList()->AddLine(start, end, box_color, visuals.skeleton_thickness);
			}
			ImGui::GetBackgroundDrawList()->PopClipRect();
		}

		if (visuals.player_count) {
			char rendercount[256];
			sprintf(rendercount, "Render Count: %d", CachePointers.PlayerArraySize);
			ImVec2 text_size = ImGui::CalcTextSize(rendercount);
			float x = (globals.ScreenWidth - text_size.x) / 2.0f;
			float y = 80.0f;
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), 15.0f, ImVec2(x, y), ImColor(255, 0, 0, 255), rendercount);
		}

		if (triggerbot.triggerbot_enable && (GetAsyncKeyState(triggerbot.triggerbot_key) < 0))
		{
			if ((read<uintptr_t>(CachePointers.PlayerController + offsets::TargetedFortPawn)))
			{
				if (distance <= triggerbot.triggerbot_distance)
				{
					Sleep(triggerbot.delay);
					utils.left_click();
				}
			}
		}

		if (aimbot.fov_arrows)
		{
			decryption.AddPlayerToFovCircle(root_bone, 187, game_helper.IsEnemyVisible(SkeletalMesh), ImColor(255, 0, 0));
		}

		if (exploits.bEditEnemyBuilds)
		{
			write<float>(CachePointers.PlayerController + exploits_offsets::bAllowEditingEnemyWalls, true);
		}

		if (exploits.noreloadcooldown) { 
			bool bIsReloadingWeapon = read<bool>(weapon::CurrentWeapon + weapon::bIsReloadingWeapon); 
			uintptr_t Mesh = read<uintptr_t>(CachePointers.AcknownledgedPawn + offsets::Mesh);  

		    write<float>(Mesh + exploits_offsets::GlobalAnimRateScale, 999); 
		}

		if (exploits.airStuck_enemyPlayers)
		{
			uintptr_t CurrentWeapon = read<uintptr_t>(CachePointers.AcknownledgedPawn + weapon::CurrentWeapon); 
			 
			write<float>(CurrentWeapon + 0x68, 70); 
		}

		if (exploits.bFallDamage)
		{
			uintptr_t CurrentVehicle = read<DWORD_PTR>(CachePointers.AcknownledgedPawn + 0x2a10);

			if (CurrentVehicle) {
				write<bool>(CurrentVehicle + 0x87a, false);
			}
			else
			{
				write<bool>(CurrentVehicle + 0x87a, true);
			}
		}

		if (exploits.no_recoil)
		{
			write<float>(CachePointers.PlayerController + 0x68, -1);
		}

		if (exploits.big_players)
		{
			float BigPlayersScale = 2.0f;
			write<fvector>(SkeletalMesh + 0x150, fvector(BigPlayersScale, BigPlayersScale, BigPlayersScale)); //Class Engine.SceneComponent -> RelativeScale3D -> 0x134
			write<fvector>(SkeletalMesh + 0x150, fvector(BigPlayersScale, BigPlayersScale, BigPlayersScale)); //Class Engine.SceneComponent -> RelativeScale3D -> 0x134
			write<fvector>(SkeletalMesh + 0x150, fvector(BigPlayersScale, BigPlayersScale, BigPlayersScale)); //Class Engine.SceneComponent -> RelativeScale3D -> 0x134
		}

		if (exploits.AimInAir)
		{
			write<bool>(CachePointers.AcknownledgedPawn + 0x5619, true); //bADSWhileNotOnGround
		}
		else {
			write<bool>(CachePointers.AcknownledgedPawn + 0x5619, false); //bADSWhileNotOnGround
		}

		if (exploits.fov_changer)
		{
			uint64_t Cameramanager = read<uint64_t>(CachePointers.PlayerController + 0x348);
			write<float>(Cameramanager + 0x4AC + 0x4, exploits.fov_value);
		}

		if (exploits.insta_reboot)
		{
			float ResurrectionStartDelay = read<float>(CachePointers.AcknownledgedPawn + 0x1910 + 0x9d8); ////AFortPlayerStateAthena InteractingRebootVan //https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=ABuildingGameplayActorSpawnMachine&member=ResurrectionStartDelay
			if (ResurrectionStartDelay != 0.001f)
			{
				write<float>(CachePointers.AcknownledgedPawn + 0x1910 + 0x9d8, 0.001f); //ABuildingGameplayActorSpawnMachine ResurrectionStartDelay 
			}
		}

		if (exploits.airStuck) {
			uintptr_t Instigator = read<uintptr_t>((uintptr_t)CachePointers.AcknownledgedPawn + 0x10);
			uintptr_t DefaultPawn = read<uintptr_t>(Instigator + 0x110);
			uintptr_t DefaultMesh = read<uintptr_t>(DefaultPawn + offsets::Mesh);
			uintptr_t StaticMesh = read<uintptr_t>(DefaultMesh + 0x508);
			uintptr_t Bone = read<uintptr_t>(StaticMesh + 0x338);


			fvector ModifiedHitsize = { 4, 4, 4 };

			fvector CurrentHitsize = read<fvector>(Bone + 0x1E0 + 0x40);

			 
			if (CurrentHitsize.x != ModifiedHitsize.x ||
				CurrentHitsize.y != ModifiedHitsize.y ||
				CurrentHitsize.z != ModifiedHitsize.z)
			{
				write<fvector>(Bone + 0x1E0 + 0x40, ModifiedHitsize);  
			}
		}

		if (exploits.spin_bot)
		{
			if (CachePointers.AcknownledgedPawn)
			{
				auto Mesh = read<uint64_t>((uint64_t)CachePointers.AcknownledgedPawn + offsets::Mesh);

				if (!exploits.isSpinning)
				{
					exploits.isSpinning = true;
					exploits.originalRotation = read<fvector>(Mesh + 0x138);
					exploits.currentAngle = exploits.originalRotation.y;
				}

				exploits.currentAngle += exploits.rotationSpeed;

				fvector CachedRotation = read<fvector>(Mesh + 0x138);
				fvector newRotation = fvector(CachedRotation.x, exploits.currentAngle, CachedRotation.z);
				write<fvector>(Mesh + 0x138, newRotation);
			}
		}

		entity cached_actors{ };
		cached_actors.entity = CurrentActor;
		cached_actors.skeletal_mesh = skeletalmesh;
		cached_actors.player_state = PlayerState;

		temporary_entity_list.push_back(cached_actors);
	}

	if (TargetEntity && aimbot.enable)
	{
		auto ClosestMesh = read<uint64_t>(TargetEntity + offsets::Mesh);

		game_helper.get_camera();
		fvector Hitbox;

		if (aimbot.Hitbox == 0)
			Hitbox = game_helper.GetBoneLocation(ClosestMesh, 110);
		else if (aimbot.Hitbox == 1)
			Hitbox = game_helper.GetBoneLocation(ClosestMesh, 66);
		else if (aimbot.Hitbox == 2)
			Hitbox = game_helper.GetBoneLocation(ClosestMesh, 7);
		else if (aimbot.Hitbox == 3)
			Hitbox = game_helper.GetBoneLocation(ClosestMesh, 2);

		fvector2d HitboxScreen = game_helper.ProjectWorldToScreen(Hitbox);

		if (aimbot.predictiondot)
			ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(HitboxScreen.x, HitboxScreen.y), 8.0f, ImColor(102, 0, 255), 200);

		if (aimbot.target_line)
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(globals.ScreenWidth / 2, globals.ScreenHeight / 2), ImVec2(HitboxScreen.x, HitboxScreen.y), ImColor(255, 255, 255), 1.f);

		if (HitboxScreen.x != 0 || HitboxScreen.y != 0 && (get_cross_distance(HitboxScreen.x, HitboxScreen.y, globals.ScreenWidth / 2, globals.ScreenHeight / 2) <= aimbot.fovsize))
		{
			if (aimbot.vischeck ? game_helper.IsEnemyVisible(ClosestMesh) : true) {

				if (GetAsyncKeyState(aimbot.aimkey))
				{

					if (aimbot.prediction)
					{
						float projectileSpeed = 0;
						float projectileGravityScale = 0;

						projectileSpeed = read<float>(CachePointers.LocalWeapon + 0x1CC4);
						projectileGravityScale = read<float>(CachePointers.LocalWeapon + 0x1F34);

						auto root = read<uintptr_t>(TargetEntity + offsets::RootComponent);
						auto distance = camera_postion.location.distance(Hitbox);
						fvector velocity = read<fvector>(root + offsets::Velocity);

						if (projectileSpeed > 1000)
						{
							Hitbox = game_helper.PredictLocation(Hitbox, velocity, projectileSpeed, projectileGravityScale, distance);
						}

						HitboxScreen = game_helper.ProjectWorldToScreen(Hitbox);

						move(HitboxScreen);
					}
					else {
						move(HitboxScreen);
					}
				}
			}
		}
	}

	else
	{
		TargetDistance = FLT_MAX;
		TargetEntity = NULL;
	}

	entity_list.clear();
	entity_list = temporary_entity_list;
}