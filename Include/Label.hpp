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

            // Update for Label.
            virtual void            update(sf::Time dt) override;

            // Set & Get Label Position.
            void                    setPosition(const sf::Vector2f& position);
            void                    setPosition(float posX, float posY);
            sf::Vector2f            getPosition() const;

            // Set another text.
            void                    setText(const std::string& text);
            // Set Label Style.
            void                    setStyle(unsigned int style);
            // Set another Color.
            void                    setColor(const sf::Color& color);

        protected:
            // Draw Label.
            virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            // Get position and size of our drawing elements.
            virtual sf::FloatRect   getRect() const override;

        private:
            // Helper Initial function
            void                    initText(const sf::Font& font, const std::string& text, float posX, float posY);

        private:
            sf::Text                mText;
            sf::Color               mColor;
    };
}


#endif // _LABEL_HPP_
