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
                LoadType,
                SaveType,
                ExitType,
            };


        public:
                                UserInput(sf::RenderWindow& window);

            // ================== Function process all inputs ==================
            void                processEvents(std::vector<std::unique_ptr<WorkFlow>>& workFlows,
                                              std::vector<std::unique_ptr<Button>>& buttons, unsigned int& frameNumber);

            // Get and Set methods for Instrument type.
            InstrumentType      getInstrumentType() const;
            void                setInstrumentType(InstrumentType type);


        private:
            // ================== Process Instruments ==================

            // ================== Process Instruments above drawing entities ==================
            void                moveElements(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement);
            void                processSelectInstrument(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement);
            void                processPointInstrument(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement);
            void                processLineInstrument(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement);

            // ================== Process Instruments above frames ==================
            void                processAddFrame(std::vector<std::unique_ptr<WorkFlow>>& workFlows);
            void                processDeleteFrame(std::vector<std::unique_ptr<WorkFlow>>& workFlows, unsigned int& frameNumber);

            // ================== Process Instruments above files ==================
            void                processLoadInstrument(std::vector<std::unique_ptr<WorkFlow>>& workFlows, unsigned int& frameNumber);
            void                processSaveInstrument(const std::vector<std::unique_ptr<WorkFlow>>& workFlows) const;

            // ================== Invoke Select, Point and Line instruments ==================
            void                processInstruments(WorkFlow& workFlow, sf::Vector2i mousePosition, SceneNode* activeElement);

            // ================== Process Buttons, and Invoke all others instruments ==================
            void                processButtons(std::vector<std::unique_ptr<WorkFlow>>& workFlows,
                                               std::vector<std::unique_ptr<Button>>& buttons, sf::Event event, unsigned int& frameNumber);

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
