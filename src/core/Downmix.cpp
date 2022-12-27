#include "shone/Downmix.hpp"

namespace shone::core 
{
    constexpr Downmix::CoefficientArray m_monoCoefficients = {0.707f, 0.707f, 1.0f, 0.5f, 0.5f, 0.5f, 0.5f};
        
    constexpr Downmix::CoefficientMatrix<2> m_stereoCoefficients = 
    {{
        {1.0f, 0.0f, 0.707f, 0.707f, 0.0f, 0.707f, 0.0f},
        {0.0f, 1.0f, 0.707f, 0.0f, 0.707f, 0.0f, 0.707f}
    }};
    
    const Downmix::CoefficientArray& Downmix::monoCoefficients() 
    {
        return m_monoCoefficients;
    }

    const Downmix::CoefficientMatrix<2>& Downmix::stereoCoefficients()
    {
        return m_stereoCoefficients;
    }
}