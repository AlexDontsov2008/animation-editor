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
    class SceneNode : public sf::Transformable, public sf::Drawable , private sf::NonCopyable
    {
        public:
            virtual                 ~SceneNode() = 0;

            virtual void            update(sf::Time dt) = 0;

        protected:
            virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
            virtual sf::FloatRect   getRect() const = 0;
    };
}


#endif // _SCENENODE_HPP_

