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

            // Update WorkFlow
            void            update(sf::Time dt);
            // Draw WorkFlow
            void            draw() const;
            // Get WorkFLow Area
            sf::FloatRect   getRect() const;

            // Add Point & Line in WorkFlow
            void            addPoint(const sf::Vector2f& position);
            void            addLine(const sf::Vector2f& firstPos, const sf::Vector2f& secondPos);

            // Set Active.
            void            setActive(bool isActive);

            // Set element from reference on elements.
            std::vector<std::unique_ptr<SceneNode>>& setElements();

        private:
            // Container for store our entity.
            std::vector<std::unique_ptr<SceneNode>>     mElements;
            sf::RenderWindow&                           mWindow;
            // WorkArea, where we draw our entity.
            Rectangle                                   mWorkArea;
    };
}

#endif // _WORKFLOW_HPP_
