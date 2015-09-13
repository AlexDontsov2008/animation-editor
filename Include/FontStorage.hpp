#ifndef _FONTSTORAGE_HPP_
#define _FONTSTORAGE_HPP_

#include <SFML/Graphics/Font.hpp>

namespace Editor
{
    class FontStorage
    {
        public:
                                FontStorage(const std::string& pathToFont);
            const sf::Font&     getFont() const;

        private:
            void                loadFont(const std::string& pathToFont);

        private:
            sf::Font            mFont;
    };
}

#endif // _FONTSTORAGE_HPP_
