#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

namespace sf
{
    class Shape;
    class Text;
}

namespace Editor
{
    void setCenterOrigin(sf::Shape& shape);
    void setCenterOrigin(sf::Text& text);
}

#endif // _UTILITY_HPP_
