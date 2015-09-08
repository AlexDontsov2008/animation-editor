#include <Utility.hpp>

#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace Editor
{
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
}
