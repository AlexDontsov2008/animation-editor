#include <Utility.hpp>
#include <InitialParametrs.hpp>
#include <Line.hpp>

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

    float angleToRad(const float angle)
    {
        constexpr float PI{ 3.1415926f };
        return angle * PI / 180.f;
    }

    bool isMousePositionInArea(const sf::Vector2i& mousePosition, const sf::FloatRect& workArea, bool isWorkArea)
    {
        if (isWorkArea)
            return (workArea.left + workAreaOffset < mousePosition.x && mousePosition.x < workArea.left + workArea.width - workAreaOffset) &&
                   (workArea.top + workAreaOffset < mousePosition.y  && mousePosition.y < workArea.top + workArea.height - workAreaOffset);

        return (workArea.left <= mousePosition.x && mousePosition.x <= workArea.left + workArea.width) &&
               (workArea.top <= mousePosition.y  && mousePosition.y <= workArea.top + workArea.height);
    }

    // Get precision for activation Line from line Lenght.
    const float getPrecisionLevel(float lineLenght)
    {
        float precisionLevel { 0.f };


        if (lineLenght <= 80.f)
            precisionLevel = 5.f;
        else if (lineLenght > 80.f && lineLenght <= 150.f)
            precisionLevel = 10.f;
        else if (lineLenght > 150.f && lineLenght <= 300.f)
            precisionLevel = 14.f;
        else if (lineLenght > 300.f && lineLenght <= 450.f)
            precisionLevel = 18.f;
        else if (lineLenght > 450.f && lineLenght <= 600.f)
            precisionLevel = 22.f;
        else if (lineLenght > 600.f && lineLenght <= 750.f)
            precisionLevel = 26.f;
        else if(lineLenght > 750.f)
            precisionLevel = 30.f;

        return precisionLevel;
    }

    // Check Lines which exist in an odd quarters
    bool checkOddQuarter(const sf::Vector2i& mousePosition, const sf::FloatRect& Area, float precisionLevel)
    {
        bool isActive { false };
        float leftPos = Area.left, topPos = Area.top + Area.height;

        for (float offsetX = Area.width / precisionLevel, offsetY = Area.height / precisionLevel;
             leftPos <= Area.left + Area.width - offsetX;)
        {
            isActive = isMousePositionInArea(mousePosition, sf::FloatRect(leftPos, topPos - offsetY, offsetX, offsetY), false);
            if (isActive)
                return true;

            leftPos += offsetX / 2.f;
            topPos -= offsetY / 2.f;
        }
        return false;
    }

    // Check Lines which exist in an even quarters
    bool checkEvenQuarter(const sf::Vector2i& mousePosition, const sf::FloatRect& Area, float precisionLevel)
    {
        bool isActive { false };
        float  leftPos = Area.left, topPos = Area.top;

        for (float offsetX = Area.width / precisionLevel, offsetY = Area.height / precisionLevel;
             leftPos <= Area.left + Area.width - offsetX;)
        {
            isActive = isMousePositionInArea(mousePosition, sf::FloatRect(leftPos, topPos, offsetX, offsetY), false);
            if (isActive)
                return true;

            leftPos += offsetX / 2.f;
            topPos += offsetY / 2.f;
        }
        return false;
    }

    // Global function for chek active lines
    bool checkActiveLines(const sf::Vector2i& mousePosition, const sf::FloatRect& Area, SceneNode* element)
    {
        Line* line = static_cast<Line*>(element);
        constexpr float pi {90.f}, offset { 3.f }, additionLenght { 5.f };
        const float precisionLevel = getPrecisionLevel(line->getLenght()), angle = line->getAngle();

        if ( (angle >= pi - offset && angle <= pi + offset) || (angle >= 3 * pi - offset && angle <= 3 * pi + offset))
        {
            return isMousePositionInArea(mousePosition, sf::FloatRect(Area.left - additionLenght, Area.top,
                                                                      Area.width + additionLenght * 2.f, Area.height), false);
        }
        else if ( (angle >= 2 * pi - offset && angle <= 2 * pi + offset) || (angle >= 4 * pi - offset && angle <= 4 * pi) ||
                  (angle >= pi * 0 && angle <= offset))
        {
            return isMousePositionInArea(mousePosition, sf::FloatRect(Area.left, Area.top - additionLenght,
                                                                      Area.width, Area.height + additionLenght * 2.f), false);
        }
        else if ( (angle >= pi && angle <= 2 * pi) || (angle >= 3 * pi && angle <= 4 * pi))
        {
            if (checkOddQuarter(mousePosition, Area, precisionLevel))
                return true;
        }
        else
        {
            if (checkEvenQuarter(mousePosition, Area, precisionLevel))
                return true;
        }

        return false;
    }

    bool isActiveDrawingElement(const sf::Vector2i& mousePosition, const sf::FloatRect& Area, SceneNode* element)
    {
        switch (element->getNodeType())
        {
            case SceneNode::Point:
                return isMousePositionInArea(mousePosition, Area, false);

            case SceneNode::Line:
                return checkActiveLines(mousePosition, Area, element);

            case SceneNode::None:
                return false;

            default:
                return false;
        }
    }

    void deleteCharacter(std::string& str)
    {
        if (str.size() > 0)
        {
            if (str[str.size() - 1] == '|')
                str.erase(str.end() - 2);
            else
                str.erase(str.end() - 1);
        }
    }

}
