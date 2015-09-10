#ifndef _WORKFLOW_HPP_
#define _WORKFLOW_HPP_

#include <SceneNode.hpp>
#include <Rectangle.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <memory>

namespace Editor
{

    class WorkFlow
    {
        public:
                            WorkFlow(sf::RenderWindow& window);
                            ~WorkFlow();

            void            update(sf::Time dt);
            void            draw() const;
            sf::FloatRect   getRect() const;

            void            addPoint(const sf::Vector2f& position);
            void            addLine(const sf::Vector2f& firstPos, const sf::Vector2f& secondPos);

        private:
            std::vector<std::unique_ptr<SceneNode>>     mElements;
            sf::RenderWindow&                           mWindow;
            Rectangle                                   mWorkArea;
    };
}

#endif // _WORKFLOW_HPP_
