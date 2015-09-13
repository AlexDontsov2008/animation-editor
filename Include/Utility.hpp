#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include <SFML/System/Vector2.hpp>

#include <sstream>

namespace sf
{
    class Shape;
    class Text;
}

namespace Editor
{
    // Set origin in the center of our object.
    void setCenterOrigin(sf::Shape& shape);
    void setCenterOrigin(sf::Text& text);

    // Evalute vector lenght.
    float vectorLenght(const sf::Vector2f& vec);
    // Evalute dot product.
    float dotProduct(const sf::Vector2f& vecLhs, const sf::Vector2f& vecRhs);
    // Evalute angle between vectors.
    float angleBetweenVectors(const sf::Vector2f& vecLhs, const sf::Vector2f& vecRhs);
    // translate radians to angles.
    float radToAngle(const float rad);

    // Process value to String.
    template <typename T>
    std::string toString(const T& value)
    {
        std::stringstream stream;
        stream << value;
        return stream.str();
    }
}

#endif // _UTILITY_HPP_
