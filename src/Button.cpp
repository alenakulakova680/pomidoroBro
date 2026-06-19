#include "Button.hpp"
Button::Button(const sf::Vector2f &size, const sf::Vector2f &position,
               const sf::Color &color, const std::string &textStr, const sf::Font &font, unsigned int characterSize)
    : m_baseColor(color), m_text(font)
{
    m_shape.setSize(size);
    m_shape.setPosition(position);
    m_shape.setFillColor(color);

    m_hoverColor = sf::Color(color.r, color.g, color.b, 170);

    m_text.setString(textStr);
    m_text.setCharacterSize(characterSize);
    m_text.setFillColor(sf::Color::White);

    centerText();
}

void Button::centerText()
{
    sf::Vector2f buttonPos = m_shape.getPosition(); 
    sf::Vector2f buttonSize = m_shape.getSize();      
    sf::FloatRect textBounds = m_text.getLocalBounds(); 

    float textX = buttonPos.x + (buttonSize.x - textBounds.size.x) / 2.0f - textBounds.position.x;
    float textY = buttonPos.y + (buttonSize.y - textBounds.size.y) / 2.0f - textBounds.position.y;

    m_text.setPosition({textX, textY});
}

void Button::setText(const std::string &textStr)
{
    m_text.setString(textStr); 
    centerText();              
}

void Button::draw(sf::RenderWindow &window) const
{
    window.draw(m_shape); 
    window.draw(m_text);  
}

void Button::updateHover(const sf::Vector2f &mousePos)
{
    if (m_shape.getGlobalBounds().contains(mousePos))
    {
        m_shape.setFillColor(m_hoverColor);
    }
    else
    {
        m_shape.setFillColor(m_baseColor); 
    }
}

bool Button::isClicked(const sf::Vector2f &mousePos, bool isLeftClick) const
{
    return isLeftClick && m_shape.getGlobalBounds().contains(mousePos);
}