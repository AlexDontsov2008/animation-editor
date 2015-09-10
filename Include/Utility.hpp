#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include <SFML/System/Vector2.hpp>

namespace sf
{
    class Shape;
    class Text;
}

namespace Editor
{
    void setCenterOrigin(sf::Shape& shape);
    void setCenterOrigin(sf::Text& text);

    float vectorLenght(const sf::Vector2f& vec);
    float dotProduct(const sf::Vector2f& vecLhs, const sf::Vector2f& vecRhs);
    float angleBetweenVectors(const sf::Vector2f& vecLhs, const sf::Vector2f& vecRhs);

    float radToAngle(const float rad);
}

#endif // _UTILITY_HPP_
