#include "../game/render/sdk.h"
#include "../framework/ImGui/imgui.h"
#include <d3d9.h>
#include "../framework/ImGui/imgui_impl_win32.h"
#include "../kernal/driver.hpp"
#include <windows.h>
#include <dwmapi.h>

ImFont* MenuFont;
ImFont* GameFont;

class structs
{
public:

	uintptr_t
		UWorld,
		GameInstance,
		GameState,
		LocalPlayer,
		AcknownledgedPawn,
		PlayerState,
		PlayerController,
		RootComponent,
		Mesh,
		PlayerArray,
		LocalWeapon;
	int32_t
		AmmoCount;

	int
		TeamIndex,
		PlayerArraySize;


}; structs CachePointers;

class entity {
public:
	uintptr_t
		entity,
		skeletal_mesh,
		root_component,
		player_state;

	char
		IgnoreDeads;

	int
		team_index,
		kills;
	char
		team_number;
	float
		lastrendertime;
	bool
		is_visible;
};
std::vector<entity> entity_list;
std::vector<entity> temporary_entity_list;

class item {
public:
	uintptr_t
		Actor;

	std::string
		Name;
	bool
		isVehicle,
		isChest,
		isPickup,
		isAmmoBox;
	float
		distance;
};

std::vector<item> item_pawns;