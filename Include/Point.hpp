#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <SceneNode.hpp>

#include <SFML/Graphics/CircleShape.hpp>

namespace Editor
{
    class Point : public SceneNode
    {
        public:
                                    Point(float posX, float posY);
            virtual                 ~Point();

            // Update Point
            virtual void            update(sf::Time dt) override;

            // Get Point Type.
            SceneNode::NodeType     getNodeType() const override;

            // Get & Set Position
            sf::Vector2f            getPosition() const;
            void                    setPosition(const sf::Vector2f& position);


        protected:
            // Draw Point.
            virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            // Get Point Area.
            virtual sf::FloatRect   getRect() const override;


        private:
            sf::CircleShape         mPoint;
            // Attribute
            sf::Color               mColor;

            //bool                    mIsActive;
            //bool                    mIsEnable;
    };
}

#endif // _POINT_HPP_
