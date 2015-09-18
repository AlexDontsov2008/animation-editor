#ifndef _INPUTWINDOW_HPP_
#define _INPUTWINDOW_HPP_

#include <Button.hpp>
#include <FontStorage.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <memory>



namespace Editor
{
    class InputWindow
    {
        public:
            enum WindowType
            {
                LoadWindow,
                SaveWindow,
            };


        public:
            enum ButtonsType
            {
                OkType,
                CancelType,
            };


        public:
                                    InputWindow(InputWindow::WindowType type, const sf::RenderWindow& mainWindow,
                                                const std::string& windowName, const std::string& fieldName);

            void                    run();
            const std::string&      getFileName() const;

        private:
            void                    update(sf::Time dt);
            void                    draw();
            void                    processEvents(sf::Time dt);

            void                    processButtons();
            void                    checkActiveElements();

            void                    init();
            void                    updateInputString(sf::Time dt);
            void                    checkStringForCursor();

            void                    processOkButton();


        private:

            WindowType                              mType;
            sf::RenderWindow                        mWindow;
            FontStorage                             mFontStorage;
            sf::RectangleShape                      mInputField;

            sf::Text                                mFieldName;
            sf::Text                                mFileNameText;
            std::string                             mFileNameStr;

            std::vector<std::unique_ptr<Button>>    mButtons;

            const unsigned int                      mNameLenghtLimit;

    };
}

#endif // _INPUTWINDOW_HPP_
