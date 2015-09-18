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
            // Types of Nodes
            enum NodeType
            {
                None,
                Point,
                Line
            };

        public:
                                    SceneNode();
            virtual                 ~SceneNode() = 0;

            // Update for current Node.
            virtual void            update(sf::Time dt) = 0;


            // Set & Get for manage active state.
            void            setActive(bool isActive);
            bool            getActive() const;

            // Set & Get for manage enable state.
            void            setEnable(bool isEnable);
            bool            getEnable() const;

            // Get NodeType for current Node.
            virtual NodeType        getNodeType() const;

            // Get position and size of our drawing elements.
            virtual sf::FloatRect   getRect() const = 0;

        protected:
            // Draw for current Node.
            virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

        private:
            // Flags Active and Enable states.
            bool            mIsActive;
            bool            mIsEnable;
    };
}


#endif // _SCENENODE_HPP_

