#pragma once

#include "../../console/console.h"

#include "../../other/configs/configs.h"

int Selection = 1;

void FilterSelectedItemSelection(int item)
{
	switch (item)
	{
	case 1:visuals.enable = !visuals.enable; break;
	case 2:visuals.box = !visuals.box; break;
	}
}

void menu_class()
{
    if (menu.menu_index == 0)
    {
        ImGui::SetNextWindowSize(ImVec2(850.0f, 450.0f));
        ImGui::Begin("Hades Private", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        if (ImGui::BeginTabBar("Aimbot"))
        {
            menu.tab = 0;
            if (ImGui::BeginTabItem("Combat"))
            {
                if (ImGui::CollapsingHeader("Aimbot"))
                {
                    ImGui::Checkbox("Enable", &aimbot.enable);
                    ImGui::Checkbox("Prediction", &aimbot.prediction);
                    ImGui::Checkbox("Prediction Dot", &aimbot.predictiondot);
                    ImGui::Checkbox("Draw Fov", &aimbot.drawfov);
                    ImGui::Checkbox("Fov Arrows", &aimbot.fov_arrows);
                    ImGui::Checkbox("Target Line", &aimbot.target_line);
                }

                if (ImGui::CollapsingHeader("Triggerbot"))
                {
                    ImGui::Checkbox("Enable", &triggerbot.triggerbot_enable);
                    ImGui::SliderInt("Distance", &triggerbot.triggerbot_distance, 1, 300);
                    ImGui::SliderInt("Delay", &triggerbot.delay, 1, 300);
                    HotkeyButton(triggerbot.triggerbot_key, ChangeKeyTriggerbot, triggerbot_keystatus);
                }

                if (ImGui::CollapsingHeader("Accuracy"))
                {
                    ImGui::SliderInt("Fov Value", &aimbot.fovsize, 10, 350);
                    ImGui::SliderInt("Smooth Value", &aimbot.smoothsize, 1, 30);
                    const char* hitboxes[] = { "Head", "Neck", "Chest", "Pelvis" };
                    ImGui::Combo("Hitbox", &aimbot.Hitbox, hitboxes, IM_ARRAYSIZE(hitboxes));
                }

                if (ImGui::CollapsingHeader("Other"))
                {
                    const char* aim_methods[] = { "Mouse", "Memory" };
                    ImGui::Combo("Aiming Method", &aimbot.method, aim_methods, IM_ARRAYSIZE(aim_methods));
                    ImGui::Text("Aimbot Key");
                    HotkeyButton(aimbot.aimkey, ChangeKey, keystatus);
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Visuals"))
            {
                menu.tab = 1;
                if (ImGui::CollapsingHeader("Visuals"))
                {
                    ImGui::Checkbox("Enable##Visuals", &visuals.enable);
                    ImGui::Checkbox("Box", &visuals.box);
                    ImGui::Checkbox("Box Filled", &visuals.filled);
                    ImGui::Checkbox("Skeleton", &visuals.skeleton);
                    ImGui::Checkbox("Distance", &visuals.distance);
                    ImGui::Checkbox("Username", &visuals.username);
                    ImGui::Checkbox("Platform", &visuals.platform);
                    ImGui::Checkbox("Weapon", &visuals.weapon);
                    ImGui::Checkbox("Rank", &visuals.rank);
                    ImGui::Checkbox("Player Count", &visuals.player_count);
                }

                if (ImGui::CollapsingHeader("Misc Visuals"))
                {
                    ImGui::Checkbox("Kills", &visuals.killscore);
                    ImGui::Checkbox("Level", &visuals.level_score);
                    ImGui::Checkbox("Chests Opened", &visuals.chests_opened);
                    ImGui::Checkbox("Minutes Alive", &visuals.minutes_alive);
                    ImGui::Checkbox("Current Health", &visuals.current_health);
                    ImGui::Checkbox("Current Shield", &visuals.current_shield);
                    ImGui::Checkbox("Spectators", &visuals.current_spectators);

                    ImGui::SliderInt("Offset X", &visuals.offset_x, 0, 200);
                }

                if (ImGui::CollapsingHeader("Thickness"))
                {
                    ImGui::SliderInt("Box Thickness", &visuals.box_thick, 1, 10);
                    ImGui::SliderInt("Skeleton Thickness", &visuals.skeleton_thickness, 1, 10);
                }

                if (ImGui::CollapsingHeader("Outline"))
                {
                    ImGui::Checkbox("Box Outline", &visuals.box_outline);
                    ImGui::Checkbox("Skeleton Outline", &visuals.skel_outline);
                }

                if (ImGui::CollapsingHeader("Other"))
                {
                    ImGui::SliderInt("Render Distance", &visuals.renderDistance, 1, 500);
                }

                ImGui::EndTabItem();
            }

           if (ImGui::BeginTabItem("Subscription"))
            {
                if (ImGui::CollapsingHeader("Box"))
                {
                    ImGui::ColorEdit4("Visible", colors.box_visible);
                    ImGui::ColorEdit4("Invisible", colors.box_invisible);

                    ImGui::ColorEdit4("Box Filled", colors.box_filled_visible);
                    ImGui::ColorEdit4("Box Filled Invisible", colors.box_filled_invisible);
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("World"))
            {
                if (ImGui::CollapsingHeader("Visuals"))
                {
                    ImGui::Checkbox("Enable", &world.enable);
                    ImGui::Checkbox("Chests", &world.chests);
                    ImGui::Checkbox("Pickups", &world.pickups);
                    ImGui::Checkbox("Uncommon", &world.uncommon);
                    ImGui::Checkbox("Common", &world.common);
                    ImGui::Checkbox("Epic", &world.epic);
                    ImGui::Checkbox("Rare", &world.rare);
                    ImGui::Checkbox("Legendary", &world.legendary);
                    ImGui::Checkbox("Mythic", &world.mythic);
                    ImGui::SliderInt("World Visuals Distance", &world.loot_distace, 1, 250);
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Misc"))
            {
                if (ImGui::CollapsingHeader("Menu"))
                {
                    ImGui::Text("Menu Key");
                    HotkeyButton(menu.menu_key, ChangeMenuKey, menu_keystatus);

                    ImGui::Text("Watermark:");
                    ImGui::Checkbox("Enable", &watermark.enable);
                    ImGui::Checkbox("Center", &watermark.center);
                    ImGui::SliderFloat("Size", &watermark.watermark_size, 5.0f, 200.0f);
                    ImGui::SliderInt("Pos X", &watermark.watermark_pos_x, 1, 2000);
                    ImGui::SliderInt("Pos Y", &watermark.watermark_pos_y, 1, 2000);
                }

                if (ImGui::CollapsingHeader("Config"))
                {
                    if (ImGui::Button("Save Config"))
                    {
                        save_config(("C:\\config.ini"));
                    }

                    if (ImGui::Button("Load Config"))
                    {
                        load_config(("C:\\config.ini"));
                    }
                }

                if (ImGui::CollapsingHeader("Exploits"))
                {
                    ImGui::Checkbox("Fov Changer", &exploits.fov_changer);

                    if (exploits.fov_changer == true)
                        ImGui::SliderInt("Fov Value", &exploits.fov_value, 0, 210);

                    ImGui::Checkbox("No reload cooldown", &exploits.noreloadcooldown);
                    ImGui::Checkbox("Insta Reboot", &exploits.insta_reboot);
                    ImGui::Checkbox("Spin Bot", &exploits.spin_bot);    
                    ImGui::Checkbox("Edit Enemy Builds", &exploits.bEditEnemyBuilds);
                    ImGui::Checkbox("Aim In Air", &exploits.AimInAir);
                    ImGui::Checkbox("Big Players", &exploits.big_players);
                    ImGui::Checkbox("Magic Bullet", &exploits.airStuck);
                    ImGui::Checkbox("Rapid Fire", &exploits.airStuck_enemyPlayers);
                    ImGui::Checkbox("No gravity in vehicle", &exploits.bFallDamage);
                    ImGui::Checkbox("No Recoil", &exploits.no_recoil);
                }

                ImGui::EndTabItem();
            }


            if (ImGui::BeginTabItem("test tab"))

            if (ImGui::BeginTabItem("Changelog"))
            {
                if (ImGui::CollapsingHeader("Info"))
                {
                    ImGui::Text("Version -> 2.3");
                    ImGui::Text("Developer -> Hades Team");
                    ImGui::Text("Discord -> https://discord.gg/hadesware");
                    ImGui::Text("Build -> 10/31/2024 - 11:25 AM");
                }

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        ImGui::End();
    }
    else if (menu.menu_index == 1)
    {
		if (GetAsyncKeyState(VK_DOWN) & 1)
			Selection = Selection + 1;

		if (GetAsyncKeyState(VK_UP) & 1)
			Selection = Selection - 1;

		if (GetAsyncKeyState(VK_RETURN) & 1)
			FilterSelectedItemSelection(Selection);

		const char* Key_1 = ("");
		const char* Key_2 = ("");

		switch (Selection)
		{
		case 1: Key_1 = (" >"); break;
		case 2: Key_2 = (" >"); break;
		}

        menu_drawing.SimpleBox(19, 200, ImColor(255, 255, 255, 255), "Enable", Key_1, visuals.enable);
        menu_drawing.SimpleBox(19, 220, ImColor(255, 255, 255, 255), "Box", Key_2, visuals.box);
    }
}