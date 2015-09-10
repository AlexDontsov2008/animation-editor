#ifndef _INITIALPARAMETRS_HPP_
#define _INITIALPARAMETRS_HPP_

#include <SFML/System/Time.hpp>

namespace Editor
{
    constexpr static float windowWidth{ 1200 }, windowHeight { 800 };
    const static std::string windowName { "AnimationEditor" };
    const static sf::Time dt{ sf::seconds(1.f / 60.f) };
    constexpr static float borderSize { 3.f };

    constexpr static float workAreaPosX{ 100 }, workAreaPosY{ 50 }, workAreaWidth{ 1000 }, workAreaHeight{ 700 };

    constexpr static float pointSize { 5.f };
    constexpr static float LineThickness { 2.f };
}

#endif // _INITIALPARAMETRS_HPP_
