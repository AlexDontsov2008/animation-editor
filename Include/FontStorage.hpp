#ifndef _FONTSTORAGE_HPP_
#define _FONTSTORAGE_HPP_

#include <SFML/Graphics/Font.hpp>

namespace Editor
{
    class FontStorage
    {
        public:
                                FontStorage(const std::string& pathToFont);
            // Get Font.
            const sf::Font&     getFont() const;

        private:
            // Helper function for load Font
            void                loadFont(const std::string& pathToFont);

        private:
            sf::Font            mFont;
    };
}

#endif // _FONTSTORAGE_HPP_
