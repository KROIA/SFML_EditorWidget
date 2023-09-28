#include "components/drawable/Line.h"
#include <math.h>
#include <SFML/Graphics.hpp>

namespace QSFML
{
namespace Components
{
COMPONENT_IMPL(Line)
Line::Line(const std::string &name)
    : Drawable(name)
    , m_thickness(1)
    , m_color(sf::Color::Green)
    , m_begin(0,0)
    , m_end(1,1)
{

}
Line::Line(const Line &other)
    : Drawable(other)
    , m_thickness(other.m_thickness)
    , m_color(other.m_color)
    , m_begin(other.m_begin)
    , m_end(other.m_end)
{
    updateShape();
}

void Line::setStartPos(const sf::Vector2f &pos)
{
    m_begin = pos;
    updateShape();
}
const sf::Vector2f &Line::getStartPos() const
{
    return m_begin;
}

void Line::setEndPos(const sf::Vector2f &pos)
{
    m_end = pos;
    updateShape();
}
const sf::Vector2f &Line::getEndPos() const
{
    return m_end;
}

void Line::setThickness(float thickness)
{
    m_thickness = thickness;
    updateShape();
}
float Line::getThickness() const
{
    return m_thickness;
}
void Line::setColor(const sf::Color &color)
{
    m_color = color;
    updateColor();
}
const sf::Color &Line::getColor() const
{
    return m_color;
}

void Line::updateShape()
{
    sf::Vector2f direction = m_end - m_begin;
    float dist =  sqrt(direction.x*direction.x+direction.y*direction.y);
    if(dist == 0)
        return;
    sf::Vector2f unitDirection = direction / dist;
    sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

    sf::Vector2f offset = (m_thickness/2.f)*unitPerpendicular;

    m_relativeVertices[0].position = m_begin + offset;
    m_relativeVertices[1].position = m_end + offset;
    m_relativeVertices[2].position = m_end - offset;
    m_relativeVertices[3].position = m_begin - offset;
}
void Line::updateColor()
{
    for (int i=0; i<4; ++i)
        m_relativeVertices[i].color = m_color;
}

void Line::draw(sf::RenderTarget& target,
                sf::RenderStates) const
{
     target.draw(m_relativeVertices,4,sf::Quads);
}
}
}