#include "components/MousePressEvent.h"
namespace QSFML
{
namespace Components
{
MousePressEvent::MousePressEvent(const std::string &name,
                                 sf::Mouse::Button button)
    : AbstractPressEvent(name)
{
    setTriggerButton(button);
}
MousePressEvent::MousePressEvent(const MousePressEvent &other)
    : AbstractPressEvent(other)
{
    m_button = other.m_button;
}
void MousePressEvent::setTriggerButton(sf::Mouse::Button button)
{
    m_button = button;
}
sf::Mouse::Button MousePressEvent::getTriggerButton() const
{
    return m_button;
}
bool MousePressEvent::getCurrentValue()
{
    return sf::Mouse::isButtonPressed(m_button);
}
}
}
