#ifndef _INITIALPARAMETRS_HPP_
#define _INITIALPARAMETRS_HPP_

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>


namespace Editor
{

    constexpr static float windowWidth{ 1100 }, windowHeight { 750 };
    const static std::string windowName { "AnimationEditor" };
    const static sf::Time dt{ sf::seconds(1.f / 60.f) };
    constexpr static float borderSize { 3.f };
    //const sf::Color GrayColor(sf::Color(174, 171, 171));
    const sf::Color InactiveColor(sf::Color(17, 18, 93));
    //const sf::Color boxColor(sf::Color(83, 85, 247));
    const sf::Color boxColor(sf::Color(114, 116, 248));
    const sf::Color windowColor(sf::Color(17, 18, 93));
    const sf::Color ActiveColor(sf::Color::White);
    const sf::Color EnableColor(sf::Color::White);

    // Parametrs for our work area
    constexpr static float workAreaPosX{ 75 }, workAreaPosY{ 30 }, workAreaWidth{ 1000 }, workAreaHeight{ 700 };
    constexpr static float workAreaOffset{ 10 };

    // Parametrs for drawing elements.
    constexpr static float pointSize { 5.f };
    constexpr static float LineThickness { 2.f };

    constexpr static float rightAngle { 90.f };

    constexpr static char pathToFont[] { "Resources/Sansation.ttf" };
    constexpr static unsigned short int characterSize { 12 };

    constexpr static float buttonSize { 50.f };
}

#endif // _INITIALPARAMETRS_HPP_
