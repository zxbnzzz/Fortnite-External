#include <string.h>
#include <list>
#include "../../game/render/camera.h"
#include <iostream>
#include "../../kernal/driver.hpp"

#define FNAMEPOOL_OFFSET 0x117284C0

class decryption_t
{
public:
	static std::string get_fname(int key)
	{
		uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
		uint16_t NameOffset = (uint16_t)key;

		uint64_t NamePoolChunk = read<uint64_t>(globals.va_text + FNAMEPOOL_OFFSET + (8 * ChunkOffset) + 16) + (unsigned int)(2 * NameOffset); //((ChunkOffset + 2) * 8) ERROR_NAME_SIZE_EXCEEDED
		if (read<uint16_t>(NamePoolChunk) < 64)
		{
			auto a1 = read<DWORD>(NamePoolChunk + 2);
			return GetNameFromIndex(a1);
		}
		else
		{
			return GetNameFromIndex(key);
		}
	}

	static std::string GetNameFromIndex(int key)
	{
		uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
		uint16_t NameOffset = (uint16_t)key;
		uint64_t NamePoolChunk = read<uint64_t>(globals.va_text + FNAMEPOOL_OFFSET + (8 * ChunkOffset) + 16) + (unsigned int)(2 * NameOffset);
		uint16_t nameEntry = read<uint16_t>(NamePoolChunk);
		int nameLength = nameEntry >> 6;
		char buff[1024] = {};

		char* v3 = buff; // rdi
		int v5; // r8d
		__int64 result = nameLength; // rax
		__int64 v7 = 0; // rdx
		unsigned int v8; // r8d
		v5 = 26;
		if ((int)result)
		{
			handler::read_physical(reinterpret_cast<void*>(NamePoolChunk + 2), static_cast<uint8_t*>(static_cast<void*>(buff)), 2 * nameLength);
			do
			{
				v8 = v5 + 45297;
				*v3 = v8 + ~*v3;
				result = v8 << 8;
				v5 = result | (v8 >> 8);
				++v3;
				--v7;
			} while (v7);
			buff[nameLength] = '\0';
			return std::string(buff);
		}
		return std::string("");
	}

	void AddPlayerToFovCircle(fvector WorldLocation, float fDistance, bool visible, ImColor color)
	{
		fvector vAngle = camera_postion.rotation;
		float fYaw = vAngle.y * PI / 180.0f;
		float dx = WorldLocation.x - camera_postion.location.x;
		float dy = WorldLocation.y - camera_postion.location.y;
		float fsin_yaw = sinf(fYaw);
		float fminus_cos_yaw = -cosf(fYaw);

		auto Center = ImVec2(globals.ScreenWidth / 2, globals.ScreenHeight / 2);

		float x = -(dy * fminus_cos_yaw + dx * fsin_yaw);
		float y = dx * fminus_cos_yaw - dy * fsin_yaw;

		float fovRadius = aimbot.fovsize;
		float angle = atan2f(y, x);
		float triangleSize = 12.0f;
		float widthFactor = 8.0f;
		float outlineThickness = 2.0f;

		ImVec2 triangleCenter = ImVec2(Center.x + cosf(angle) * (fovRadius + triangleSize),
			Center.y + sinf(angle) * (fovRadius + triangleSize));

		ImVec2 point1 = ImVec2(triangleCenter.x + cosf(angle) * triangleSize,
			triangleCenter.y + sinf(angle) * triangleSize);
		ImVec2 point2 = ImVec2(triangleCenter.x + cosf(angle + widthFactor) * triangleSize,
			triangleCenter.y + sinf(angle + widthFactor) * triangleSize);
		ImVec2 point3 = ImVec2(triangleCenter.x + cosf(angle - widthFactor) * triangleSize,
			triangleCenter.y + sinf(angle - widthFactor) * triangleSize);

		ImU32 fillColor = ImGui::ColorConvertFloat4ToU32(visible ? color : ImColor(color.Value.x, color.Value.y, color.Value.z, 0.5f));
		ImU32 outlineColor = ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0, 1.0));

		ImDrawList* drawList = ImGui::GetForegroundDrawList();
		drawList->AddTriangleFilled(point1, point2, point3, fillColor);
		drawList->AddTriangle(point1, point2, point3, outlineColor, outlineThickness);
	}

	std::string getRank(int tier) {
		switch (tier) {
		case 0:  return "Unranked";
		case 1:  return "Bronze 2";
		case 2:  return "Bronze 3";
		case 3:  return "Silver 1";
		case 4:  return "Silver 2";
		case 5:  return "Silver 3";
		case 6:  return "Gold 1";
		case 7:  return "Gold 2";
		case 8:  return "Gold 3";
		case 9:  return "Platinum 1";
		case 10: return "Platinum 2";
		case 11: return "Platinum 3";
		case 12: return "Diamond 1";
		case 13: return "Diamond 2";
		case 14: return "Diamond 3";
		case 15: return "Elite";
		case 16: return "Champion";
		case 17: return "Unreal";
		default: return "Unranked";
		}
	}

	ImVec4 getRankColor(int tier) {
		switch (tier) {
		case 0:  return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);    // Unranked
		case 1:
		case 2:  return ImVec4(0.902f, 0.580f, 0.227f, 1.0f); // Bronze
		case 3:
		case 4:
		case 5:  return ImVec4(0.843f, 0.843f, 0.843f, 1.0f); // Silver
		case 6:
		case 7:
		case 8:  return ImVec4(1.0f, 0.871f, 0.0f, 1.0f); // Gold
		case 9:
		case 10:
		case 11: return ImVec4(0.0f, 0.7f, 0.7f, 1.0f);  // Platinum
		case 12:
		case 13:
		case 14: return ImVec4(0.1686f, 0.3294f, 0.8235f, 1.0f); // Diamond
		case 15: return ImVec4(0.7f, 0.7f, 0.7f, 1.0f);   // Elite
		case 16: return ImVec4(1.0f, 0.6f, 0.0f, 1.0f);   // Champion
		case 17: return ImVec4(0.6f, 0.0f, 0.6f, 1.0f);   // Unreal
		default: return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);    // Unranked
		}
	}

	std::string ReadWideString(uint64_t address, int length) {
		if (length <= 0 || length > 50) return "";

		std::wstring buffer(length, L'\0');
		read1(address, buffer.data(), length * sizeof(wchar_t));
		return std::string(buffer.begin(), buffer.end());
	}

	static std::string GetPlayerName(uintptr_t playerState) {
		auto Name = read<uintptr_t>(playerState + 0xA98);
		auto length = read<int>(Name + 0x10);
		auto v6 = (__int64)length;

		if (length <= 0 || length > 255) return std::string("BOT");

		auto FText = (uintptr_t)read<__int64>(Name + 0x8);

		wchar_t* Buffer = new wchar_t[length];
		handler::read_physical(PVOID(static_cast<ULONGLONG>(FText)), Buffer, length * sizeof(wchar_t));

		char v21;
		int v22;
		int i;

		int v25;
		UINT16* v23;

		v21 = v6 - 1;
		if (!(UINT32)v6)
			v21 = 0;
		v22 = 0;
		v23 = (UINT16*)Buffer;
		for (i = (v21) & 3; ; *v23++ += i & 7)
		{
			v25 = v6 - 1;
			if (!(UINT32)v6)
				v25 = 0;
			if (v22 >= v25)
				break;
			i += 3;
			++v22;
		}

		std::wstring PlayerName{ Buffer };
		delete[] Buffer;
		return std::string(PlayerName.begin(), PlayerName.end());
	}

	std::string GetWeaponName(uintptr_t Player) {
		std::string PlayersWeaponName = "";
		uint64_t CurrentWeapon = read<uint64_t>((uintptr_t)Player + weapon::CurrentWeapon);
		uint64_t weapondata = read<uint64_t>(CurrentWeapon + weapon::WeaponData);
		uint64_t AmmoCount = read<uint64_t>(CurrentWeapon + weapon::AmmoCount);
		uint64_t ItemName = read<uint64_t>(weapondata + weapon::ItemName);

		if (!ItemName) return "";

		uint64_t FData = read<uint64_t>(ItemName + 0x28);
		int FLength = read<int>(ItemName + 0x30);

		if (FLength > 0 && FLength < 50) {

			wchar_t* WeaponBuffer = new wchar_t[FLength];
			handler::read_physical((void*)FData, (PVOID)WeaponBuffer, FLength * sizeof(wchar_t));
			std::wstring wstr_buf(WeaponBuffer);
			if (AmmoCount != 0) PlayersWeaponName.append(std::string(wstr_buf.begin(), wstr_buf.end()) + " [" + "Ammo: " + std::to_string(AmmoCount) + "]");
			else PlayersWeaponName.append(std::string(wstr_buf.begin(), wstr_buf.end()));

			delete[] WeaponBuffer;
		}
		return PlayersWeaponName;
	}
}; decryption_t decryption;

class gamehelper_t
{
public:
	static auto GetBoneLocation(uintptr_t skeletal_mesh, int bone_index) -> fvector {
		uintptr_t bone_array = read<uintptr_t>(skeletal_mesh + offsets::BoneArray);
		if (bone_array == NULL) bone_array = read<uintptr_t>(skeletal_mesh + offsets::BoneArray + 0x10);
		FTransform bone = read<FTransform>(bone_array + (bone_index * 0x60));
		FTransform component_to_world = read<FTransform>(skeletal_mesh + offsets::ComponentToWorld);
		D3DMATRIX matrix = MatrixMultiplication(bone.ToMatrixWithScale(), component_to_world.ToMatrixWithScale());
		return fvector(matrix._41, matrix._42, matrix._43);
	}

	camera_position_s get_camera()
	{
		camera_position_s camera;

		auto location_pointer = read<uintptr_t>(CachePointers.UWorld + 0x130); 
		auto rotation_pointer = read<uintptr_t>(CachePointers.UWorld + 0x140); 

		struct FNRot
		{
			double a; //0x0000
			char pad_0008[24]; //0x0008
			double b; //0x0020
			char pad_0028[424]; //0x0028
			double c; //0x01D0
		} fnRot;

		fnRot.a = read<double>(rotation_pointer);   
		fnRot.b = read<double>(rotation_pointer + 0x20);
		fnRot.c = read<double>(rotation_pointer + 0x1d0);  

		camera.rotation.x = asin(fnRot.c) * (180.0 / M_PI);
		camera.rotation.y = ((atan2(fnRot.a * -1, fnRot.b) * (180.0 / M_PI)) * -1) * -1;
		camera.rotation.z = 0;
		camera.location = read<fvector>(location_pointer);
		camera.fov = read<float>(CachePointers.LocalPlayer + 0x4AC); 

		return camera;
	}

	inline fvector2d ProjectWorldToScreen(fvector WorldLocation)
	{
		camera_postion = get_camera();

		if (WorldLocation.x == 0)
			return fvector2d(0, 0);

		_MATRIX tempMatrix = Matrix(camera_postion.rotation);
		fvector vAxisX = fvector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		fvector vAxisY = fvector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		fvector vAxisZ = fvector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

		fvector vDelta = WorldLocation - camera_postion.location;
		fvector vTransformed = fvector(vDelta.dot(vAxisY), vDelta.dot(vAxisZ), vDelta.dot(vAxisX));

		if (vTransformed.z < 1.f)
			vTransformed.z = 1.f;

		return fvector2d((globals.ScreenWidth / 2.0f) + vTransformed.x * (((globals.ScreenWidth / 2.0f) / tanf(camera_postion.fov * (float)M_PI / 360.f))) / vTransformed.z, (globals.ScreenHeight / 2.0f) - vTransformed.y * (((globals.ScreenWidth / 2.0f) / tanf(camera_postion.fov * (float)M_PI / 360.f))) / vTransformed.z);
	}

	fvector PredictLocation(fvector target, fvector targetVelocity, float projectileSpeed, float projectileGravityScale, float distance)
	{
		float horizontalTime = distance / projectileSpeed;
		float verticalTime = distance / projectileSpeed;

		target.x += targetVelocity.x * horizontalTime;
		target.y += targetVelocity.y * horizontalTime;
		target.z += targetVelocity.z * verticalTime +
			abs(-980 * projectileGravityScale) * 0.5f * (verticalTime * verticalTime);

		return target;
	}

	static auto IsEnemyVisible(uintptr_t skeletal_mesh) -> bool
	{
		auto last_submit = read<float>(skeletal_mesh + offsets::fLastSubmitTime);
		auto last_render = read<float>(skeletal_mesh + offsets::fLastRenderTimeOnScreen);
		return last_render + 0.06f >= last_submit;
	}

	auto IsInScreen(fvector2d screen_location) -> bool
	{
		if (screen_location.x > 0 && screen_location.x < globals.ScreenWidth && screen_location.y > 0 && screen_location.y < globals.ScreenHeight) return true;
		else return false;
	}
}; gamehelper_t game_helper;

char* wchar_to_char(const wchar_t* pwchar)
{
	int currentCharIndex = 0;
	char currentChar = pwchar[currentCharIndex];

	while (currentChar != '\0')
	{
		currentCharIndex++;
		currentChar = pwchar[currentCharIndex];
	}

	const int charCount = currentCharIndex + 1;

	char* filePathC = (char*)malloc(sizeof(char) * charCount);

	for (int i = 0; i < charCount; i++)
	{
		char character = pwchar[i];

		*filePathC = character;

		filePathC += sizeof(char);

	}
	filePathC += '\0';

	filePathC -= (sizeof(char) * charCount);

	return filePathC;
}