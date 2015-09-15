#include <SceneNode.hpp>

namespace Editor
{
    SceneNode::~SceneNode()
    {}

    SceneNode::NodeType SceneNode::getNodeType() const
    {
        return None;
    }

}
