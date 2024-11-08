#include "../../game/aimbot/keybind.h"

struct camera_position_s {
	fvector location{};
	fvector rotation{};
	float fov{};
};
inline camera_position_s camera_postion{};

#define deg2Rad(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define rad2Deg(angleRadians) ((angleRadians) * 180.0 / M_PI)

struct FMinimalViewInfo
{
	FMinimalViewInfo() : Location(), Rotation(), FOV(FOV) {}
	FMinimalViewInfo(fvector Location, fvector Rotation, float FOV) : Location(Location), Rotation(Rotation), FOV(FOV) {}

	fvector Location, Rotation;
	float FOV;
};

inline FMinimalViewInfo m_camera_information{};


typedef struct _D3DMATRIX1 {
	union {
		struct {
			double _11, _12, _13, _14;
			double _21, _22, _23, _24;
			double _31, _32, _33, _34;
			double _41, _42, _43, _44;

		};
		double m[4][4];
	};
} D3DMATRIX1;

typedef struct D3DXMATRIX1 {
	DOUBLE _ij;
} D3DXMATRIX1, * LPD3DXMATRIX1;

struct FPlane : public fvector
{
	double W;
};

struct FMatrix
{
	FPlane XPlane, YPlane, ZPlane, WPlane;

	FMatrix MatrixMultiplication(FMatrix Other)
	{
		FMatrix Copy = {};

		Copy.WPlane.x = this->WPlane.x * Other.XPlane.x + this->WPlane.y * Other.YPlane.x + this->WPlane.z * Other.ZPlane.x + this->WPlane.W * Other.WPlane.x;
		Copy.WPlane.y = this->WPlane.x * Other.XPlane.y + this->WPlane.y * Other.YPlane.y + this->WPlane.z * Other.ZPlane.y + this->WPlane.W * Other.WPlane.y;
		Copy.WPlane.z = this->WPlane.x * Other.XPlane.z + this->WPlane.y * Other.YPlane.z + this->WPlane.z * Other.ZPlane.z + this->WPlane.W * Other.WPlane.z;
		Copy.WPlane.W = this->WPlane.x * Other.XPlane.W + this->WPlane.y * Other.YPlane.W + this->WPlane.z * Other.ZPlane.W + this->WPlane.W * Other.WPlane.W;

		return Copy;
	}

	static FMatrix RotatorToMatrix(fvector Rotation)
	{
		auto ReturnValue = FMatrix();

		auto Pitch = (Rotation.x * 3.14159265358979323846 / 180);
		auto Yaw = (Rotation.y * 3.14159265358979323846 / 180);
		auto Roll = (Rotation.z * 3.14159265358979323846 / 180);

		auto sp = sin(Pitch);
		auto cp = cos(Pitch);
		auto sy = sin(Yaw);
		auto cy = cos(Yaw);
		auto sr = sin(Roll);
		auto cr = cos(Roll);

		ReturnValue.XPlane.x = cp * cy;
		ReturnValue.XPlane.y = cp * sy;
		ReturnValue.XPlane.z = sp;

		ReturnValue.YPlane.x = sr * sp * cy - cr * sy;
		ReturnValue.YPlane.y = sr * sp * sy + cr * cy;
		ReturnValue.YPlane.z = -sr * cp;

		ReturnValue.ZPlane.x = -(cr * sp * cy + sr * sy);
		ReturnValue.ZPlane.y = cy * sr - cr * sp * sy;
		ReturnValue.ZPlane.z = cr * cp;

		ReturnValue.WPlane.W = 0x1;

		return ReturnValue;
	}
};

uintptr_t viewStates;
uintptr_t viewMatrices;
D3DMATRIX1 invProjMatrix;

class Camera
{
public:
	void normalize(fvector& in)
	{
		while (in.x > 180.0f)
			in.x -= 360.0f;

		while (in.x < -180.0f)
			in.x += 360.0f;

		while (in.y > 180.0f)
			in.y -= 360.0f;

		while (in.y < -180.0f)
			in.y += 360.0f;

		in.z = 0;
	}

	auto calc_angle(fvector LocalPos, fvector WorldPos) -> fvector {
		fvector RelativePos = WorldPos - LocalPos;
		float yaw = atan2(RelativePos.y, RelativePos.x) * 180.0f / M_PI;
		float pitch = -((acos(RelativePos.z / LocalPos.distance(WorldPos)) * 180.0f / M_PI) - 90.0f);

		return fvector(pitch, yaw, 0);
	}

}; inline Camera* camera;

std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

inline std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}
inline std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}