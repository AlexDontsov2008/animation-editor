#include <FontStorage.hpp>

namespace Editor
{
    FontStorage::FontStorage(const std::string& pathToFont)
    : mFont{}
    {
        loadFont(pathToFont);
    }

    void FontStorage::loadFont(const std::string& pathToFont)
    {
        if (!mFont.loadFromFile(pathToFont))
            throw std::logic_error("Incorrect path name to font source!");
    }

    const sf::Font& FontStorage::getFont() const
    {
        return mFont;
    }
}

