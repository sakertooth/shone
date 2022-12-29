#include "shone/core/SndFileHelper.hpp"

namespace shone::core
{
    SNDFILE* SndFileHelper::openAudioHandle(const std::filesystem::path& filePath, SF_INFO& info, int mode)
    {
        auto nativeFilePath = filePath.c_str();
        SNDFILE* audioFile = nullptr;
        
        if (std::is_same_v<std::filesystem::path::value_type, char>) 
        {
            audioFile = sf_open(nativeFilePath, mode, &info);
        }
        #ifdef WIN32
        else if (std::is_same_v<std::filesystem::path::value_type, wchar_t>) 
        {
            audioFile = sf_wchar_open(nativeFilePath, mode, &info);
        }
        #endif
        else 
        {
            throw std::domain_error{"AudioFile::AudioFile: Unknown/unsupported file path.\n"};
        }

        if (sf_error(audioFile))
        {
            throw std::runtime_error{std::string{"AudioFile::AudioFile: SndFile error, "} + sf_strerror(audioFile)};
        }

        return audioFile;
    }  
}