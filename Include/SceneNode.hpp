#ifndef _SCENENODE_HPP_
#define _SCENENODE_HPP_

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>

namespace sf
{
    class Time;
}

namespace Editor
{
    // Abstact class, which describe scene elements.
    class SceneNode : public sf::Transformable, public sf::Drawable , private sf::NonCopyable
    {
        public:
            enum NodeType
            {
                None,
                Point,
                Line
            };

        public:
            virtual                 ~SceneNode() = 0;

            virtual void            update(sf::Time dt) = 0;

            virtual void            setActive(bool isActive) = 0;
            virtual bool            getActive() const = 0;

            virtual void            setEnable(bool isEnable) = 0;
            virtual bool            getEnable() const = 0;

            virtual NodeType        getNodeType() const;

            // Get position and size of our drawing elements.
            virtual sf::FloatRect   getRect() const = 0;

        protected:
            virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    };
}


#endif // _SCENENODE_HPP_

