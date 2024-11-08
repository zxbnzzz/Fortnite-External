#include "../../kernal/driver.hpp"
#include <unordered_map>

namespace world_offsets
{
    inline static uintptr_t levels = 0x178;
    inline static uintptr_t aactor = 0xa0; // OwningWorld - 0x20
}

namespace offsets
{
    inline static uintptr_t UWorld = 0x12D18608;
    inline static uintptr_t RelativeLocation = 0x120;
    inline static uintptr_t OwningWorld = 0xc0;
    inline static uintptr_t AcknowledgedPawn = 0x350; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=APlayerController&member=AcknowledgedPawn
    inline static uintptr_t Mesh = 0x328; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=ACharacter&member=Mesh
    inline static uintptr_t RootComponent = 0x1B0; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AActor&member=RootComponent
    inline static uintptr_t LocalPlayers = 0x38; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=UGameInstance&member=LocalPlayers
    inline static uintptr_t PlayerController = 0x30; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=UPlayer&member=PlayerController
    inline static uintptr_t OwningGameInstance = 0x208; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=UWorld&member=OwningGameInstance
    inline static uintptr_t PawnPrivate = 0x320; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=APlayerState&member=PawnPrivate
    inline static uintptr_t GameState = 0x190; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=UWorld&member=GameState
    inline static uintptr_t PlayerArray = 0x2c0; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AGameStateBase&member=PlayerArray
    inline static uintptr_t PlayerState = 0x2b0; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AController&member=PlayerState
    inline static uintptr_t fLastSubmitTime = 0x2E0;
    inline static uintptr_t fLastRenderTimeOnScreen = 0x2E8;
    inline static uintptr_t Velocity = 0x168; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=USceneComponent&member=ComponentVelocity
    inline static uintptr_t BoneArray = 0x580;
    inline static uintptr_t PersistentLevel = 0x40; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=UWorld&member=PersistentLevel
    inline static uintptr_t ComponentToWorld = 0x1c0;
    inline static uintptr_t Platform = 0x3f0;
    inline static uintptr_t TargetedFortPawn = 0x1898;
}

namespace exploits_offsets
{
    inline static uintptr_t bAllowEditingEnemyWalls = 0x69c;
    inline static uintptr_t HealthSiphonValue = 0x138;
    inline static uintptr_t WoodSiphonValue = 0x13c;
    inline static uintptr_t StoneSiphonValue = 0x140;
    inline static uintptr_t MetalSiphonValue = 0x144;
    inline static uintptr_t bFallDamage = 0x154;
    inline static uintptr_t GlobalAnimRateScale = 0x9d8;
}

namespace weapon
{
    inline static uintptr_t CurrentWeapon = 0x9d8; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AFortPawn&member=CurrentWeapon
    inline static uintptr_t WeaponData = 0x520; // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AFortWeapon&member=WeaponData
    inline static uintptr_t AmmoCount = 0xf1c;
    inline static uintptr_t ItemName = 0x40;
    inline static uintptr_t Tier = 0x9A;
    inline static uintptr_t Color = 0x50;
    inline static uintptr_t bIsReloadingWeapon = 0x399;
}

namespace world_offsets
{
    uintptr_t Levels = 0x178;
    uintptr_t Actors = 0xa0;
}

template<class T>
class TArray
{
public:
    int getLength() const
    {
        return count;
    }

    int getIdentifier()
    {
        return data * count * max;
    }

    bool isValid() const
    {
        if (count > max)
            return false;
        if (!data)
            return false;
        return true;
    }

    uint64_t getAddress() const
    {
        return data;
    }

    T operator [](size_t idx) const
    {
        return read<T>(data + sizeof(T) * idx);
    }

protected:
    uint64_t data;
    uint64_t count;
    uint64_t max;
};

struct Fortnite
{
    static uint64_t getVAStart(uintptr_t gworldOffset);

    enum ActorType
    {
        NOT_IN_USE = 0,
        CHEST = 1,
        AMMO_BOX = 2
    };

    struct ActorDefinitions
    {
        int actorID;
        std::string fname;
        ActorType actorType;
    };

    static const std::unordered_map<std::string, ActorType>& getActorByName()
    {
        static const std::unordered_map<std::string, ActorType> actorTypeByName =
        {
            {"Tiered_Chest", ActorType::CHEST},
            {"Tiered_Ammo", ActorType::AMMO_BOX}
        };
        return actorTypeByName;
    }

    static ActorDefinitions getActorDefinitions(int actorID);
};