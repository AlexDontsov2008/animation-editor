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

            virtual void                update(sf::Time dt) override;

            virtual bool                getActive() const override;
            virtual void                setActive(bool isActive) override;

            virtual void                setEnable(bool isEnable) override;
            virtual bool                getEnable() const override;

            SceneNode::NodeType         getNodeType() const override;

            float                       getAngle() const;
            float                       getLenght() const;

            sf::Vector2f                getFirstPosition() const;
            sf::Vector2f                getSecondPosition() const;

            void                        setFirstPosition(const sf::Vector2f& firstPosition);
            void                        setSecondPosition(const sf::Vector2f& secondPosition);

        protected:
            virtual void                draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            virtual sf::FloatRect       getRect() const override;

        private:
            void                        init();
            void                        EvalutionLineParametrs();

        private:
            sf::RectangleShape          mLine;
            sf::Vector2f                mFirstPosition;
            sf::Vector2f                mSecondPosition;
            sf::Color                   mColor;
            float                       mAngle;

            bool                        mIsActive;
            bool                        mIsEnable;
    };
}

#endif // _LINE_HPP_
