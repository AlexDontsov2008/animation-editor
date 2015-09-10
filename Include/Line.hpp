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

        protected:
            virtual void                draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            virtual sf::FloatRect       getRect() const override;

        private:
            void                        setColor(const sf::Color& color);
            void                        init();

        private:
            sf::RectangleShape          mLine;
            sf::Vector2f                mFirstPosition;
            sf::Vector2f                mSecondPosition;
            sf::Color                   mColor;
    };
}

#endif // _LINE_HPP_
