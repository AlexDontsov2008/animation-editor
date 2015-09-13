#ifndef _LABEL_HPP_
#define _LABEL_HPP_

#include <SFML/Graphics/Text.hpp>

#include <SceneNode.hpp>

namespace Editor
{
    class Label : public SceneNode
    {
        public:
                                    Label(const sf::Font& font, const std::string& text, float posX, float posY);
            virtual                 ~Label();

            virtual void            update(sf::Time dt) override;
            void                    setText(const std::string& text);

            void                    setPosition(const sf::Vector2f& position);
            void                    setPosition(float posX, float posY);


            void                    setColor(const sf::Color& color);
            void                    setStyle(unsigned int style);

        protected:
            virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            virtual sf::FloatRect   getRect() const override;

        private:
            void                    initText(const sf::Font& font, const std::string& text, float posX, float posY);

        private:
            sf::Text                mText;
            sf::Color               mColor;
    };
}


#endif // _LABEL_HPP_
