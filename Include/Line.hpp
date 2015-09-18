#ifndef _LINE_HPP_
#define _LINE_HPP_

#include <SceneNode.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

namespace Editor
{
    class Line : public SceneNode
    {
        public:
                                        Line(const sf::Vector2f& firstPos, const sf::Vector2f& secondPos);
            virtual                     ~Line();

            // Update Line.
            virtual void                update(sf::Time dt) override;

            // Get Line Type.
            SceneNode::NodeType         getNodeType() const override;

            // Get Angle & Lenght.
            float                       getAngle() const;
            float                       getLenght() const;

            // Get First & Second Position.
            sf::Vector2f                getFirstPosition() const;
            sf::Vector2f                getSecondPosition() const;

            // Set First & Second Position.
            void                        setFirstPosition(const sf::Vector2f& firstPosition);
            void                        setSecondPosition(const sf::Vector2f& secondPosition);

        protected:
            // Draw Line.
            virtual void                draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            // get Line Area.
            virtual sf::FloatRect       getRect() const override;

        private:
            // Helper initialization function.
            void                        init();
            // Evalution geometry parametrs.
            void                        EvalutionLineParametrs();

        private:
            sf::RectangleShape          mLine;
            // Geometry parametrs.
            sf::Vector2f                mFirstPosition;
            sf::Vector2f                mSecondPosition;
            float                       mAngle;
            // Attributes.
            sf::Color                   mColor;

            //bool                        mIsActive;
            //bool                        mIsEnable;
    };
}

#endif // _LINE_HPP_
