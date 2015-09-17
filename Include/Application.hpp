#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <WorkFlow.hpp>
#include <UserInput.hpp>
#include <Label.hpp>
#include <Button.hpp>
#include <FontStorage.hpp>

#include <memory>
#include <vector>

namespace sf
{
    class Time;
}

namespace Editor
{
    // Main Class
    class Application
    {
        public:
                                Application();
            void                run();

        private:
            // Update Application.
            void                update(sf::Time dt);
            // Render Application.
            void                render();
            // Process events from user.
            void                processEvents();
            // Initializing out control buttons.
            void                initButtons();

        private:
            // Window where render our application.
            sf::RenderWindow                        mWindow;
            // Font storage.
            FontStorage                             mFontStorage;
            // Work Area, where we draw our animation.
            std::vector<std::unique_ptr<WorkFlow>>  mWorkFlows;
            // Buttons for communication.
            std::vector<std::unique_ptr<Button>>    mButtons;
            // Frames Counter.
            sf::Text                                mFramesCounterText;
            // User Input.
            UserInput                               mInput;
            // Frame number.
            unsigned int                            mFrameNumber;

    };
}

#endif // _APPLICATION_HPP_
