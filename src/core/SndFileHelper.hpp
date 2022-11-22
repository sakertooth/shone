#pragma once
#include <filesystem>
#include <memory>
#include <functional>
#include <sndfile.h>

namespace shone::core 
{
    class SndFileHelper 
    {
    public:
        static std::pair<std::unique_ptr<SNDFILE, std::function<void(SNDFILE*)>>, SF_INFO> 
            open(const std::filesystem::path& filepath, int mode);
    };
}