#include <SceneNode.hpp>

namespace Editor
{
    SceneNode::SceneNode()
    : mIsActive{ false }
    , mIsEnable{ false }
    {}

    SceneNode::~SceneNode()
    {}

    // Default definition.
    SceneNode::NodeType SceneNode::getNodeType() const
    {
        return None;
    }

    // Set & Get for manage active state.
    void SceneNode::setActive(bool isActive)
    {
        mIsActive = isActive;
    }

    bool SceneNode::getActive() const
    {
        return mIsActive;
    }

    // Set & Get for manage enable state.
    void SceneNode::setEnable(bool isEnable)
    {
        mIsEnable = isEnable;
    }

    bool SceneNode::getEnable() const
    {
        return mIsEnable;
    }
}
