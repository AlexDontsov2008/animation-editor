#ifndef _USERINPUT_HPP_
#define _USERINPUT_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>


#include <Button.hpp>
#include <WorkFlow.hpp>

#include <memory>
#include <vector>

namespace Editor
{
    class UserInput
    {
        public:
            enum InstrumentType
            {
                MoveType,
                PointType,
                LineType,
            };

        public:
                                UserInput(sf::RenderWindow& window);

            // Major function for process events.
            void                processEvents(WorkFlow& workFlow, std::vector<std::unique_ptr<Button>>& buttons);

            // Get and Set methods for Instrument type.
            InstrumentType      getInstrumentType() const;
            void                setInstrumentType(InstrumentType type);


        private:
            // Function for process every Instrument
            void                processMouseMoveInstrument(WorkFlow& workFlow, sf::Event event, sf::Vector2i mousePosition);
            void                processPointInstrument(WorkFlow& workFlow, sf::Event event, sf::Vector2i mousePosition);
            void                processLineInstrument(WorkFlow& workFlow, sf::Event event, sf::Vector2i mousePosition);

            // Major process function for instruments
            void                processInstruments(WorkFlow& workFlow, sf::Event event);

            void                processButtons(std::vector<std::unique_ptr<Button>>& buttons, sf::Event event);
            // Check Mouse position in WorkArea

            bool                isMousePositionInArea(const sf::Vector2i& mousePosition, const sf::FloatRect& workArea, bool isWorkArea);


        private:
            sf::RenderWindow&       mWindow;
            InstrumentType          mType;
    };
}

#endif // _USERINPUT_HPP_
