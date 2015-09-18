#include <FontStorage.hpp>

namespace Editor
{
    FontStorage::FontStorage(const std::string& pathToFont)
    : mFont{}
    {
        loadFont(pathToFont);
    }

    // Helper function for load Font
    void FontStorage::loadFont(const std::string& pathToFont)
    {
        if (!mFont.loadFromFile(pathToFont))
            throw std::logic_error("Incorrect path name to font source!");
    }

    // Get Font.
    const sf::Font& FontStorage::getFont() const
    {
        return mFont;
    }
}

