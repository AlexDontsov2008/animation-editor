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

            virtual void            update(sf::Time dt) override;

            bool                    getActive() const override;
            void                    setActive(bool isActive) override;

            void                    setEnable(bool isEnable) override;
            bool                    getEnable() const override;

            SceneNode::NodeType     getNodeType() const override;

            sf::Vector2f            getPosition() const;
            void                    setPosition(const sf::Vector2f& position);


        protected:
            virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            virtual sf::FloatRect   getRect() const override;


        private:
            sf::CircleShape         mPoint;
            sf::Color               mColor;

            bool                    mIsActive;
            bool                    mIsEnable;
    };
}

#endif // _POINT_HPP_
