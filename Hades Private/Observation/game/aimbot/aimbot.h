#include <Windows.h>
#include <cstdint>
#include <iostream>
#include <Psapi.h>
#include "../utils/settings.h"

namespace memoryk
{
    uintptr_t NetConnection = 0x508;
    uintptr_t RotationInput = NetConnection + 0x8;
}

class memory_t
{
public:
    bool memory_event(fvector newpos)
    {
        write<fvector>(CachePointers.PlayerController + memoryk::RotationInput, newpos);
        return true;
    }
    fvector GetLocation(fvector Location)
    {
        fvector Loc = fvector(Location.x, Location.y, Location.z);
        return Loc;
    }
    fvector CalcRotation(fvector& zaz, fvector& daz) {
        fvector dalte = zaz - daz;
        fvector ongle;
        float hpm = sqrtf(dalte.x * dalte.x + dalte.y * dalte.y);
        ongle.y = atan(dalte.y / dalte.x) * 57.295779513082f;
        ongle.x = (atan(dalte.z / hpm) * 57.295779513082f) * -1.f;
        if (dalte.x >= 0.f) ongle.y += 180.f;
        return ongle;
    }
}; memory_t memory;

inline void move(fvector2d Head2D)
{
    const float AimSpeed = aimbot.smoothsize;
    const fvector2d ScreenCenter = { static_cast<double>(globals.ScreenWidth) / 2, static_cast<double>(globals.ScreenHeight) / 2 };

    fvector2d Target = { 0, 0 };

    if (Head2D.x != 0) {
        Target.x = (Head2D.x > ScreenCenter.x) ? -(ScreenCenter.x - Head2D.x) : (Head2D.x - ScreenCenter.x);
        Target.x /= AimSpeed;
        Target.x = (Target.x + ScreenCenter.x > ScreenCenter.x * 2 || Target.x + ScreenCenter.x < 0) ? 0 : Target.x;
    }

    if (Head2D.y != 0) {
        Target.y = (Head2D.y > ScreenCenter.y) ? -(ScreenCenter.y - Head2D.y) : (Head2D.y - ScreenCenter.y);
        Target.y /= AimSpeed;
        Target.y = (Target.y + ScreenCenter.y > ScreenCenter.y * 2 || Target.y + ScreenCenter.y < 0) ? 0 : Target.y;
    }

    if (aimbot.method == 0)
    {
        mouse_event(MOUSEEVENTF_MOVE, Target.x, Target.y, NULL, NULL); 
    }
    else if (aimbot.method == 1)
    {
        memory.memory_event(fvector(-Target.y / AimSpeed, Target.x / AimSpeed, 0));
    }
}