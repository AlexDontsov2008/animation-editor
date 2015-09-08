#ifndef _INITIALPARAMETRS_HPP_
#define _INITIALPARAMETRS_HPP_

namespace Editor
{
    constexpr static float windowWidth{ 800 }, windowHeight { 600 };
    const static std::string windowName { "AnimationEditor" };
    const static sf::Time dt{ sf::seconds(1.f / 60.f) };
}

#endif // _INITIALPARAMETRS_HPP_
