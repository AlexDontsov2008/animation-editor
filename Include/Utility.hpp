#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <sstream>

#include <SceneNode.hpp>

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
    float angleToRad(const float angle);

    // Check is mouse in current Area
    bool isMousePositionInArea(const sf::Vector2i& mousePosition, const sf::FloatRect& workArea, bool isWorkArea);
    bool isActiveDrawingElement(const sf::Vector2i& mousePosition, const sf::FloatRect& Area, SceneNode* element);

    // Process value to String.
    template <typename T>
    std::string toString(const T& value)
    {
        std::stringstream stream;
        stream << value;
        return stream.str();
    }

    // Delete cursor from str.
    void deleteCharacter(std::string& str);
}

#endif // _UTILITY_HPP_
