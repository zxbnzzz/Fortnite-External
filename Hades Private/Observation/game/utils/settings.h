#ifndef SETTINGS_H
#define SETTINGS_H

#include <mutex>
#include <memory>

class menu_t
{
public:
	bool ShowMenu = true;
	int menu_key = VK_INSERT;
	int fontsize = 15;

	ImFont* MenuFont;
	bool menu_cursor = true;
	int menu_index = 0;
	int tab;
}; menu_t menu;

class watermark_t
{
public:
	bool enable = true;
	float watermark_size = 18.0f;
	int watermark_pos_x = 1;
	int watermark_pos_y = 1;
	bool center = false;
}; watermark_t watermark;

class globals_t
{
public:
	int ScreenWidth;
	ImVec2 NiggaWidth;
	int ScreenHeight;

	__int64 va_text = 0;
	HWND window_handle;
}; globals_t globals;

class triggerbot_t
{
public:
	bool triggerbot_enable = true;
	int triggerbot_distance = 20;
	int delay = 1;
	int triggerbot_key = VK_F4;
}; triggerbot_t triggerbot;

class aimbot_t
{
public:
	// Main
	bool enable = false;
	bool target_line = false;
	int method = 0;

	// Misc
	bool prediction = false;
	bool predictiondot = false;
	bool vischeck = false;
	bool drawfov = false;
	bool fov_arrows = false;
	int fov_drawdistance;

	// Settings
	int fovsize = 150;
	int ADS_Fov_Size = 150;
	int smoothsize = 6;
	int Hitbox = 0;
	int aimkey = VK_RBUTTON;
}; aimbot_t aimbot;

class world_t
{
public:
	bool enable = false;
	bool chests = false;
	bool pickups = false;
	bool uncommon = false;
	bool common = false;
	bool epic = false;
	bool rare = false;
	bool legendary = false;
	bool mythic = false;

	int loot_distace = 50;
	int cache_update_speed = 100;
}; world_t world;

class visuals_t
{
public:
	bool enable = false;
	bool player_count = false;
	bool nigger = true;
	bool rank = false;
	bool killscore = false;
	bool level_score = false;
	bool chests_opened = false;
	bool minutes_alive = false;
	bool current_health = false;
	bool current_shield = false;
	bool current_spectators = false;
	bool box = false;
	int offset_x = 0;
	bool corner_box = false;
	bool filled = false;
	bool skeleton = false;
	bool distance = false;
	bool username = false;
	bool platform = false;
	bool weapon = false;

	int box_thick = 1;
	int skeleton_thickness = 1;
	float corner_width = 0.75f;

	bool box_outline = false;
	bool skel_outline = false;

	int renderDistance = 200;
}; visuals_t visuals;

class colors_t
{
public:
	float box_visible[4] = { 255.f / 255.f, 0.f, 255.f / 255.f, 1.f };
	float box_invisible[4] = { 1.f, 0.f, 0.f, 1.f };

	float box_filled_visible[4] = { 100.f / 255.f, 0.f, 255.f / 255.f, 110.f / 255.f };
	float box_filled_invisible[4] = { 255.f / 255.f, 0.f, 0.f, 110.f / 255.f };
}; colors_t colors;

class misc_t
{
public:
	bool debug = true;
}; misc_t misc;

class exploits_t
{
public:
	bool fov_changer = false;
	bool spin_bot = false;
	bool bEditEnemyBuilds = false;
	bool airStuck_enemyPlayers = false;
	bool insta_reboot = false;
	bool AimInAir = false;
	bool airStuck = false;
	bool no_recoil = false;
	bool noreloadcooldown = false;

	float rotationSpeed = 0.9f;
	float currentAngle = 8.0f;
	bool isSpinning = false;
	bool big_players = false;
	bool bFallDamage = false;
	fvector originalRotation;

	int fov_value;

	int freeze_enemyplayers_key = 'G';
}; inline exploits_t exploits;

#endif // SETTINGS_H