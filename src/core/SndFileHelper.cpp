#include "SndFileHelper.hpp"

namespace shone::core 
{
    std::pair<std::unique_ptr<SNDFILE, std::function<void(SNDFILE*)>>, SF_INFO> 
        SndFileHelper::open(const std::filesystem::path& filepath, int mode) 
    {
        auto nativeFilePath = filepath.c_str();
        auto audioFile = std::unique_ptr<SNDFILE, std::function<void(SNDFILE*)>>{};
        SF_INFO audioInfo;

        if (std::is_same_v<std::filesystem::path::value_type, char>) 
        {
            audioFile = std::unique_ptr<SNDFILE, std::function<void(SNDFILE*)>>{sf_open(nativeFilePath, mode, &audioInfo), [](SNDFILE* p){sf_close(p);}};
        }
        #ifdef WIN32
        else if (std::is_same_v<std::filesystem::path::value_type, wchar_t>) 
        {
            audioFile = std::unique_ptr<SNDFILE, std::function<void(SNDFILE*)>>{sf_wchar_open(nativeFilePath, mode, &audioInfo), [](SNDFILE* p){sf_close(p);}};
        }
        #endif
        else 
        {
            throw std::domain_error{"Unknown/unsupported file path.\n"};
        }

        return {std::move(audioFile), audioInfo};
    }
}