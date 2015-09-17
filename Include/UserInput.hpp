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
                SelectType,
                MoveType,
                PointType,
                LineType,
                AddFrameType,
                DeleteFrameType,
                ExitType,
            };


        public:
                                UserInput(sf::RenderWindow& window);

            // Major function for process events.
            void                processEvents(std::vector<std::unique_ptr<WorkFlow>>& workFlows,
                                              std::vector<std::unique_ptr<Button>>& buttons, unsigned int& frameNumber);

            // Get and Set methods for Instrument type.
            InstrumentType      getInstrumentType() const;
            void                setInstrumentType(InstrumentType type);


        private:
            // Function for process every Instrument
            void                moveElements(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement);

            void                processSelectInstrument(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement);
            void                processPointInstrument(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement);
            void                processLineInstrument(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement);

            // Major process function for instruments
            void                processInstruments(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement);

            void                processButtons(std::vector<std::unique_ptr<WorkFlow>>& workFlows,
                                               std::vector<std::unique_ptr<Button>>& buttons, sf::Event event);

            // Check active elements
            SceneNode*          checkActiveElements(WorkFlow& workFlow, std::vector<std::unique_ptr<Button>>& buttons) const;

            // Check active draw elements (Points, Lines).
            SceneNode*          checkActiveDrawingElements(WorkFlow& workFlow) const;


        private:
            sf::RenderWindow&       mWindow;
            InstrumentType          mType;
    };
}

#endif // _USERINPUT_HPP_
