#include <iostream>

#include "UI/Button.h"

Button::Button(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text, const sf::Font &font,
               const unsigned int characterSize, std::function<void(void)> callback)
    : callback(callback)
{
    shape.setSize(size); // установка размеров заднего фона

    this->text.setString(text); // установка текста кнопки
    this->text.setFont(font);
    this->text.setCharacterSize(characterSize); // установка размера текста

    setPosition(position); // позиционирование кнопки
}

void Button::setBackgroundColor(const sf::Color &color, const sf::Color &onClick, const sf::Color &onHover)
{
    backgroundColor = color;
    backgroundColorOnClick = onClick;
    backgroundColorOnHover = onHover;

    updateColor();
}

void Button::setBackgroundColor(const sf::Color &color, const sf::Color &onClick)
{
    setBackgroundColor(color, onClick, color);
}

void Button::setBackgroundColor(const sf::Color &color)
{
    setBackgroundColor(color, color, color);
}

void Button::setTextColor(const sf::Color &color, const sf::Color &onClick, const sf::Color &onHover)
{
    textColor = color;
    textColorOnClick = onClick;
    textColorOnHover = onHover;

    updateColor();
}

void Button::setTextColor(const sf::Color &color, const sf::Color &onClick)
{
    setTextColor(color, onClick, color);
}

void Button::setTextColor(const sf::Color &color)
{
    setTextColor(color, color, color);
}

void Button::updateColor()
{
    if (isPressed) // кнопка нажата
    {
        shape.setFillColor(backgroundColorOnClick);
        text.setFillColor(textColorOnClick);
    }
    else if (isHovered) // курсор наведен на кнопку
    {
        shape.setFillColor(backgroundColorOnHover);
        text.setFillColor(textColorOnHover);
    }
    else // стандартный вид кнопки
    {
        shape.setFillColor(backgroundColor);
        text.setFillColor(textColor);
    }
}

void Button::setPosition(sf::Vector2f position)
{
    shape.setPosition(position); // позиционирование заднего фона

    // обновление исходной точки текста (т.к. размеры текста могли измениться)
    text.setOrigin(text.getGlobalBounds().getPosition());
    // центрирование текста на кнопке
    text.setPosition(shape.getPosition() + (shape.getSize() - text.getGlobalBounds().getSize()) / 2.f);
}

void Button::handleEvent(const sf::Event &event)
{
    switch (event.type)
    {
    case sf::Event::MouseButtonReleased: // кнопка отпущена
        if (event.mouseButton.button == sf::Mouse::Button::Left)
        {
            if (isPressed and shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            // данная проверка проводится для того, чтобы случайно нажав на кнопку была возможность не
            // активировать ее, если отвести курсор в другое место и только потом отпустить
            {
                callback();

                isPressed = false;
                updateColor();
            }
        }

        break;
    case sf::Event::MouseButtonPressed: // кнопка нажата
        if (shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
            isPressed = true;
            updateColor();
        }
        else
            isPressed = false;

        break;
    case sf::Event::MouseMoved: // положение курсора изменилось
        isHovered = shape.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y);
        updateColor();

        break;
    default:
        break;
    }
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(shape, states);
    target.draw(text, states);
}
