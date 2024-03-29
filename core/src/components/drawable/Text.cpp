#include "components/drawable/Text.h"
#include "objects/base/CanvasObject.h"
#include "utilities/AABB.h"
#include "utilities/Origin.h"

namespace QSFML
{
    namespace Components
    {
        COMPONENT_IMPL(Text);
        Text::Text(const std::string& name)
            : Drawable(name)
           // , m_pos(0, 0)
            , m_origin(Utilities::Origin::Type::TopLeft)
            , m_font(nullptr)
        {
            m_text.setScale(0.1f,0.1f);
            setText(name);
        }
        Text::Text(const Text &other)
            : Drawable(other)
           // , m_pos(other.m_pos)
            , m_origin(other.m_origin)
            , m_font(other.m_font)
        {
            m_text = other.m_text;
            updateCenter(other.getPosition());
        }
        void Text::setText(const std::string &text)
        {
            m_text.setString(text);
            updateCenter(getPosition());
        }
        std::string Text::getText() const
        {
            return m_text.getString();
        }

        void Text::setCharacterSize(unsigned int size)
        {
            m_text.setCharacterSize(size);
            updateCenter(getPosition());
        }
        unsigned int Text::getCharacterSize() const
        {
            return m_text.getCharacterSize();
        }

        void Text::setScale(float scale)
        {
            m_text.setScale(sf::Vector2f(scale, scale));
            updateCenter(getPosition());
        }
        float Text::getScale() const
        {
            return m_text.getScale().x;
        }

        //void Text::setPosition(const sf::Vector2f &pos)
        //{
        //    m_pos = pos;
        //    updateCenter(m_pos);
        //}
        //const sf::Vector2f &Text::getPosition() const
        //{
        //    return m_pos;
        //}

        
       

        void Text::setFont(const sf::Font& font)
        {
            m_text.setFont(font);
            m_font = m_text.getFont();
            updateCenter(getPosition());
        }
        bool Text::setFont(const std::string& path)
        {
            sf::Font *f = new sf::Font();
            if (f->loadFromFile(path))
            {
                setFont(*f);
                return true;
            }
            delete f;
            return false;
        }
        const sf::Font& Text::getFont() const
        {
            return *m_text.getFont();
        }

        void Text::setParent(Objects::CanvasObject *parent)
        {
            Component::setParent(parent);
            if(!m_font)
            if(getParent())
            {
                setFont(getParent()->getTextFont());
            }
        }

        void Text::drawComponent(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(m_text, states);
        }

        void Text::updateCenter(const sf::Vector2f &pos)
        {
            QSFML_UNUSED(pos);
            sf::FloatRect bounds = m_text.getLocalBounds();
            Utilities::AABB box(bounds.left, bounds.top, bounds.width, bounds.height);
    
            sf::Vector2f originPos = m_origin.getOrigin(box);
            m_text.setOrigin(originPos);
            //m_text.setPosition(pos);
        }

    }
}
