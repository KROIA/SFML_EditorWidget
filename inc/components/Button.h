#pragma once

#include <QObject>
#include "utilities/AABB.h"
#include "components/MousePressEvent.h"

namespace QSFML
{
namespace Components
{
class Button : public MousePressEvent, public Utilities::AABB
{
    public:
        explicit Button(const std::string &name = "BoxCollider");
        explicit Button(const std::string &name, const Utilities::AABB &box);
        Button(const Button &other);
        ~Button();

        CLONE_FUNC(Button)

    protected:
        bool getCurrentValue() override;
        bool m_wasInside;
        bool m_wasPressed;
};
}
}
