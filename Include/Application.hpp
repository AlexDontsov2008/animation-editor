#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <SFML/Graphics/RenderWindow.hpp>

#include <SceneNode.hpp>

#include <memory>
#include <vector>

namespace sf
{
    class Time;
}

namespace Editor
{
    class Application
    {
        public:
                                Application();
            void                run();

        private:
            void                update(sf::Time dt);
            void                render();
            void                processEvents();

            void                init();

        private:
            sf::RenderWindow                        mWindow;
            std::vector<std::unique_ptr<SceneNode>> mElements;
    };
}

#endif // _APPLICATION_HPP_
