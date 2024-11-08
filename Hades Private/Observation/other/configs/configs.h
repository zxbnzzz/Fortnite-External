#include <WinBase.h>
#include <string>

#include "../../game/utils/settings.h"

static BOOL write_private_profile_int(LPCSTR lpAppName, LPCSTR lpKeyName, int nInteger, LPCSTR lpFileName) {
    char lpString[1024];
    sprintf(lpString, ("%d"), nInteger);
    return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}
static BOOL write_private_profile_float(LPCSTR lpAppName, LPCSTR lpKeyName, float nInteger, LPCSTR lpFileName) {
    char lpString[1024];
    sprintf(lpString, ("%f"), nInteger);
    return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}
static float get_private_profile_float(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT flDefault, LPCSTR lpFileName) {
    char szData[32];

    GetPrivateProfileStringA(lpAppName, lpKeyName, std::to_string(flDefault).c_str(), szData, 32, lpFileName);

    return (float)atof(szData);
}

static BOOL read_bool(LPCSTR section, LPCSTR key, bool& target, LPCSTR path) {
    int value = GetPrivateProfileIntA(section, key, -1, path);
    if (value != -1) {
        target = value != 0;

        return true;
    }       

    return false;
}

static BOOL read_int(LPCSTR section, LPCSTR key, int& target, LPCSTR path) {
    int value = GetPrivateProfileIntA(section, key, -1, path);
    if (value != -1) {
        target = value;

        return true;
    }

    return false;
}

static BOOL read_float(LPCSTR section, LPCSTR key, float& target, LPCSTR path) {
    char buffer[32];
    if (GetPrivateProfileStringA(section, key, "", buffer, sizeof(buffer), path) > 0) {
        float value = atof(buffer);
        target = value;

        return true;
    }

    return false;
}

static BOOL read_color(LPCSTR section, LPCSTR key, float target[4], LPCSTR path) {
    char buffer[64];
    if (GetPrivateProfileStringA(section, key, "", buffer, sizeof(buffer), path) > 0) {
        char* token;
        char* context;
        int i = 0;
        token = strtok_s(buffer, (","), &context);
        while (token != NULL && i < 4) {
            float value = atof(token);
            target[i] = value;
            token = strtok_s(NULL, (","), &context);
            i++;
        }

        return true;
    }

    return false;
}

static void write_color(LPCSTR section, LPCSTR key, const float value[4], LPCSTR path) {
    char buffer[64];
    snprintf(buffer, sizeof(buffer), ("%.6f,%.6f,%.6f,%.6f"), value[0], value[1], value[2], value[3]);
    WritePrivateProfileStringA(section, key, buffer, path);
}

void save_config(LPCSTR path)
{
    {
        {
            // Combat
            write_private_profile_int(("Combat"), ("enable"), aimbot.enable, path);
            write_private_profile_int(("Combat"), ("method"), aimbot.method, path);
            write_private_profile_int(("Combat"), ("prediction"), aimbot.prediction, path);
            write_private_profile_int(("Combat"), ("prediction_dot"), aimbot.predictiondot, path);
            write_private_profile_int(("Combat"), ("draw_fov"), aimbot.drawfov, path);
            write_private_profile_int(("Combat"), ("fov_arrows"), aimbot.fov_arrows, path);
            write_private_profile_int(("Combat"), ("fov_size"), aimbot.fovsize, path);
            write_private_profile_int(("Combat"), ("smothness"), aimbot.smoothsize, path);
            write_private_profile_int(("Combat"), ("hitbox"), aimbot.Hitbox, path);
            write_private_profile_int(("Hotkeys"), ("aimbot_key"), aimbot.aimkey, path);
            // Triggerbot
            write_private_profile_int(("Triggerbot"), ("enable"), triggerbot.triggerbot_enable, path);
            write_private_profile_int(("Triggerbot"), ("distance"), triggerbot.triggerbot_distance, path);
            write_private_profile_int(("Triggerbot"), ("delay"), triggerbot.delay, path);
            write_private_profile_int(("Triggerbot"), ("key"), triggerbot.triggerbot_key, path);
            // Visuals
            write_private_profile_int(("Visuals"), ("enable"), visuals.enable, path);
            write_private_profile_int(("Visuals"), ("box"), visuals.box, path);
            write_private_profile_int(("Visuals"), ("filled"), visuals.filled, path);
            write_private_profile_int(("Visuals"), ("skeleton"), visuals.skeleton, path);
            write_private_profile_int(("Visuals"), ("distance"), visuals.distance, path);
            write_private_profile_int(("Visuals"), ("username"), visuals.username, path);
            write_private_profile_int(("Visuals"), ("platform"), visuals.platform, path);
            write_private_profile_int(("Visuals"), ("weapon"), visuals.weapon, path);
            write_private_profile_int(("Visuals"), ("rank"), visuals.rank, path);
            write_private_profile_int(("Visuals"), ("box_thickness"), visuals.box_thick, path);
            write_private_profile_int(("Visuals"), ("skel_thickness"), visuals.skeleton_thickness, path);
            write_private_profile_int(("Visuals"), ("box_outline"), visuals.box_thick, path);
            write_private_profile_int(("Visuals"), ("skel_outline"), visuals.skel_outline, path);
            write_private_profile_int(("Visuals"), ("render_distance"), visuals.renderDistance, path);

            write_color(("Colors"), ("box_visible"), colors.box_visible, path);
            write_color(("Colors"), ("box_invisible"), colors.box_invisible, path);
            write_color(("Colors"), ("box_filled_visible"), colors.box_filled_visible, path);
            write_color(("Colors"), ("box_filled_invisible"), colors.box_filled_invisible, path);
        }
    }
}

void load_config(LPCSTR path)
{
    {
        {
            // Combat
            read_bool(("Combat"), ("enable"), aimbot.enable, path);
            read_int(("Combat"), ("method"), aimbot.method, path);
            read_bool(("Combat"), ("prediction"), aimbot.prediction, path);
            read_bool(("Combat"), ("prediction_dot"), aimbot.predictiondot, path);
            read_bool(("Combat"), ("draw_fov"), aimbot.drawfov, path);
            read_bool(("Combat"), ("fov_arrows"), aimbot.fov_arrows, path);
            read_int(("Combat"), ("fov_size"), aimbot.fovsize, path);
            read_int(("Combat"), ("smothness"), aimbot.smoothsize, path);
            read_int(("Combat"), ("hitbox"), aimbot.Hitbox, path);
            read_int(("Hotkeys"), ("aimbot_key"), aimbot.aimkey, path);
            // Triggerbot
            read_bool(("Triggerbot"), ("enable"), triggerbot.triggerbot_enable, path);
            read_int(("Triggerbot"), ("distance"), triggerbot.triggerbot_distance, path);
            read_int(("Triggerbot"), ("delay"), triggerbot.delay, path);
            read_int(("Triggerbot"), ("key"), triggerbot.triggerbot_key, path);
            // Visuals
            read_bool(("Visuals"), ("enable"), visuals.enable, path);
            read_bool(("Visuals"), ("box"), visuals.box, path);
            read_bool(("Visuals"), ("filled"), visuals.filled, path);
            read_bool(("Visuals"), ("skeleton"), visuals.skeleton, path);
            read_bool(("Visuals"), ("distance"), visuals.distance, path);
            read_bool(("Visuals"), ("username"), visuals.username, path);
            read_bool(("Visuals"), ("platform"), visuals.platform, path);
            read_bool(("Visuals"), ("weapon"), visuals.weapon, path);
            read_bool(("Visuals"), ("rank"), visuals.rank, path);
            read_int(("Visuals"), ("box_thickness"), visuals.box_thick, path);
            read_int(("Visuals"), ("skel_thickness"), visuals.skeleton_thickness, path);
            read_int(("Visuals"), ("box_outline"), visuals.box_thick, path);
            read_bool(("Visuals"), ("skel_outline"), visuals.skel_outline, path);
            read_int(("Visuals"), ("render_distance"), visuals.renderDistance, path);

            read_color(("Colors"), ("box_visible"), colors.box_visible, path);
            read_color(("Colors"), ("box_invisible"), colors.box_invisible, path);
            read_color(("Colors"), ("box_filled_visible"), colors.box_filled_visible, path);
            read_color(("Colors"), ("box_filled_invisible"), colors.box_filled_invisible, path);
        }
    }
}