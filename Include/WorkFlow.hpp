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

            // Functions for add the Points and the Lines on the WorkArea.
            void            addPoint(const sf::Vector2f& position);
            void            addLine(const sf::Vector2f& firstPos, const sf::Vector2f& secondPos);

            void            setBorderColor(const sf::Color& color);
            void            setActive(bool isActive);

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
