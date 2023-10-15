#include "../header/ImageView.h"

ImageView::ImageView() = default;

ImageView::~ImageView() = default;

void ImageView::initialize(sf::String texture_path, float image_width, float image_height, sf::Vector2f position)
{
    UIView::initialize();
    setTexture(texture_path);
    setScale(image_width, image_height);
    setPosition(position);
}

void ImageView::update() 
{
    UIView::update();
}

void ImageView::render()
{
    UIView::render();

    if (ui_state == UIState::VISIBLE)
    {
        game_window->draw(image_sprite);
    }
}

void ImageView::setTexture(sf::String texture_path)
{
    if (image_texture.loadFromFile(texture_path))
    {
        image_sprite.setTexture(image_texture);
    }
}

void ImageView::setScale(float width, float height)
{
    float scale_x = width / image_sprite.getTexture()->getSize().x;
    float scale_y = height / image_sprite.getTexture()->getSize().y;

    image_sprite.setScale(scale_x, scale_y);
}

void ImageView::setPosition(sf::Vector2f position)
{
    image_sprite.setPosition(position);
}

void ImageView::setImageAlpha(float alpha)
{
    sf::Color color = image_sprite.getColor();
    color.a = alpha;
    image_sprite.setColor(color);
}