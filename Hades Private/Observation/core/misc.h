#pragma once

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <TlHelp32.h>
#include <windows.h>
#include <string>
#include <cstdio>

#define WINVER 0x0501 // Windows XP and later
#define _WIN32_WINNT 0x0501

class core_misc_t
{
public:
    std::string generate_string(int length)
    {
        const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

        std::random_device rd;
        std::mt19937 gen(rd());  // Seed the generator
        std::uniform_int_distribution<> distrib(0, characters.size() - 1);  // Define the range

        std::string randomString;
        randomString.reserve(length);

        for (int i = 0; i < length; ++i) {
            randomString += characters[distrib(gen)];
        }

        Sleep(50);

        std::string name = "HADES - ";

        return name + randomString;
    }

	static bool admincheck()
	{
		HANDLE hToken;

		if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
		{
			TOKEN_ELEVATION elevation;
			DWORD size;

			if (GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &size))
			{
				CloseHandle(hToken);

				return elevation.TokenIsElevated != 0;
			}

			CloseHandle(hToken);
		}

		return false;
	}
}; core_misc_t core_misc;