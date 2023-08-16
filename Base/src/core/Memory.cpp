#include "Memory.h"
#include "Interfaces.h"

#include <Windows.h>
#include <vector>
#include <stdexcept>

void Memory::Initialize()
{
    present = reinterpret_cast<uintptr_t>(Scan("gameoverlayrenderer", "FF 15 ? ? ? ? 8B F0 85 FF") + 2);
    reset = reinterpret_cast<uintptr_t>(Scan("gameoverlayrenderer", "C7 45 ? ? ? ? ? FF 15 ? ? ? ? 8B D8") + 9);

    disablePostProcessing = *reinterpret_cast<bool**>(Scan("client", "83 EC 4C 80 3D") + 5);

    setClanTag = reinterpret_cast<decltype(setClanTag)>(Scan("engine", "53 56 57 8B DA 8B F9 FF 15"));

    globalVars = **reinterpret_cast<CGlobalVarsBase***>((*reinterpret_cast<uintptr_t**>(interfaces->client))[11] + 10);
}

uint8_t* Memory::Scan(const char* module, const char* pattern)
{
    const auto handle = GetModuleHandle(module);

    if (!handle)
        throw std::runtime_error("Failed to get " + std::string(module) + " module handle.");

    static auto patternToByte = [](const char* pattern)
    {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + std::strlen(pattern);

        for (auto current = start; current < end; ++current)
        {
            if (*current == '?')
            {
                ++current;

                if (*current == '?')
                    ++current;

                bytes.push_back(-1);
            }
            else
            {
                bytes.push_back(std::strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(handle);
    auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(handle) + dosHeader->e_lfanew);

    auto size = ntHeaders->OptionalHeader.SizeOfImage;
    auto bytes = patternToByte(pattern);
    auto scanBytes = reinterpret_cast<std::uint8_t*>(handle);

    auto s = bytes.size();
    auto d = bytes.data();

    for (auto i = 0ul; i < size - s; ++i)
    {
        bool found = true;

        for (auto j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1) {

                found = false;
                break;
            }
        }

        if (found)
            return &scanBytes[i];
    }

    throw std::runtime_error("Outdated pattern \"" + std::string(pattern) + "\"");
}