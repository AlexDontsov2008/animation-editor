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
            // Run Window.
            void                    run();
            // Get File Name.
            const std::string&      getFileName() const;

        private:
            // Update window.
            void                    update(sf::Time dt);

            // Draw window.
            void                    draw();
            // Process All Events.
            void                    processEvents(sf::Time dt);

            // Process Buttons.
            void                    processButtons();
            // Check Active Elements.
            void                    checkActiveElements();

            // Helper Init function.
            void                    init();
            // Update string.
            void                    updateInputString(sf::Time dt);
            // Process Cursor.
            void                    checkStringForCursor();
            // Process OK Button.
            void                    processOkButton();


        private:
            // Window Type.
            WindowType                              mType;
            sf::RenderWindow                        mWindow;
            FontStorage                             mFontStorage;
            // Input Area.
            sf::RectangleShape                      mInputField;
            // Field Name.
            sf::Text                                mFieldName;
            sf::Text                                mFileNameText;
            std::string                             mFileNameStr;

            // Buttons.
            std::vector<std::unique_ptr<Button>>    mButtons;
            // Name Lenght Limit.
            const unsigned int                      mNameLenghtLimit;

    };
}

#endif // _INPUTWINDOW_HPP_
