#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <SFML/Graphics/RenderWindow.hpp>

#include <WorkFlow.hpp>

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

        private:
            sf::RenderWindow                        mWindow;
            WorkFlow                                mWorkFlow;
    };
}

#endif // _APPLICATION_HPP_
