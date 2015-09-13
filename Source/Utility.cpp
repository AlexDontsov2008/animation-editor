#include <Utility.hpp>

#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <math.h>
#include <iostream>

namespace Editor
{
    // Set origin in the center of our object.
    void setCenterOrigin(sf::Shape& shape)
    {
        sf::FloatRect bounds { shape.getLocalBounds() };
        shape.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

    void setCenterOrigin(sf::Text& text)
    {
        sf::FloatRect bounds { text.getLocalBounds() };
        text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

    // Evalute vector lenght.
    float vectorLenght(const sf::Vector2f& vec)
    {
        return std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));
    }

    // Evalute dot product.
    float dotProduct(const sf::Vector2f& vecLhs, const sf::Vector2f& vecRhs)
    {
        return (vecLhs.x * vecRhs.x) + (vecLhs.y * vecRhs.y);
    }

    // Evalute angle between vectors.
    float angleBetweenVectors(const sf::Vector2f& vecLhs, const sf::Vector2f& vecRhs)
    {
        return radToAngle(std::acos(dotProduct(vecLhs, vecRhs) / (vectorLenght(vecLhs) * vectorLenght(vecRhs))));
    }

    // translate radians to angles.
    float radToAngle(const float rad)
    {
        constexpr float PI{ 3.1415926f };
        return rad * 180.f / PI;
    }
}
