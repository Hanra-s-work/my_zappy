/*
** EPITECH PROJECT, 10024
** my_zappy
** File description:
** Graphic
*/

#include "Graphic.hpp"

Graphic::Graphic() : scrollSpeed(500.0f), mapWidth(0), mapHeight(0)
{
}

void Graphic::initWindow(unsigned int width, unsigned int height, const std::string &title)
{
    window.create(sf::VideoMode(width, height), title);
    view.setSize(sf::Vector2f(width, height));
    view.setCenter(sf::Vector2f(width / 1.0f, height / 1.0f));
    window.setView(view);
}

sf::RenderWindow &Graphic::getWindow()
{
    return window;
}

void Graphic::setMapSize(float width, float height)
{
    mapWidth = width;
    mapHeight = height;
}

void Graphic::handleInput(bool& followPlayer, const sf::Vector2f& playerPosition)
{
    const float deltaTime = 1.0f / 60.0f;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f viewMove(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) || sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
        scrollSpeed += 50.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) || sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) {
        scrollSpeed -= 50.0f;
        if (scrollSpeed < 0) {
            scrollSpeed = 0;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
        followPlayer = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        followPlayer = false;
    }

    if (!followPlayer) {
        if (mousePosition.x <= 100) {
            viewMove.x = -scrollSpeed * deltaTime;
        }
        if (mousePosition.x >= windowSize.x - 100) {
            viewMove.x = scrollSpeed * deltaTime;
        }
        if (mousePosition.y <= 100) {
            viewMove.y = -scrollSpeed * deltaTime;
        }
        if (mousePosition.y >= windowSize.y - 100) {
            viewMove.y = scrollSpeed * deltaTime;
        }
    }

    sf::Vector2f newCenter = followPlayer ? playerPosition : view.getCenter() + viewMove;
    sf::Vector2f halfSize = view.getSize() / 1.0f;

    if (newCenter.x - halfSize.x < 0) {
        newCenter.x = halfSize.x;
    }
    if (newCenter.x + halfSize.x > mapWidth) {
        newCenter.x = mapWidth - halfSize.x;
    }
    if (newCenter.y - halfSize.y < 0) {
        newCenter.y = halfSize.y;
    }
    if (newCenter.y + halfSize.y > mapHeight) {
        newCenter.y = mapHeight - halfSize.y;
    }

    view.setCenter(newCenter);
    window.setView(view);
}

ISprite::ISprite(const std::string &textureFile)
{
    loadTexture(textureFile);
}

bool ISprite::loadTexture(const std::string &textureFile)
{
    if (!texture.loadFromFile(textureFile)) {
        return false;
    }
    sprite.setTexture(texture);
    return true;
}

Player::Player(const std::string &textureFile, const sf::Vector2f &startPosition, float moveSpeed, float animationSpeed)
: ISprite(textureFile), _direction(0, 0), _destPosition(startPosition), _moveSpeed(moveSpeed), _animationSpeed(animationSpeed), _reachedDest(false)
{
    _rect = sf::IntRect(0, 0, 80, 80);
    sprite.setTextureRect(_rect);
    sprite.setPosition(startPosition);
    sprite.setScale(3.0f, 3.0f);
}

void Player::handleInput()
{
    _direction = {0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        _direction.y = -1;
        _currentDir = Direction::Up;
        _rect.top = 240;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        _direction.y = 1;
        _currentDir = Direction::Down;
        _rect.top = 160;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        _direction.x = -1;
        _currentDir = Direction::Left;
        _rect.top = 80;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _direction.x = 1;
        _currentDir = Direction::Right;
        _rect.top = 0;
    }
}

void Player::updateTime(sf::Time elapsed)
{
    _elapsedTime += elapsed;
    if (_elapsedTime.asSeconds() > 1.0f / _animationSpeed) {
        sprite.move(_direction * _moveSpeed * _elapsedTime.asSeconds());
        _elapsedTime = sf::Time::Zero;
        updateAnimation();
    }
}

void Player::updateAnimation()
{
    _rect.left += 80;
    if (_rect.left >= _texture.getSize().x) {
        _rect.left = 0;
    }
    sprite.setTextureRect(_rect);
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

void Player::setPosition(const sf::Vector2f &position)
{
    sprite.setPosition(position);
}

sf::Vector2f Player::getPosition() const
{
    return sprite.getPosition();
}

Resource::Resource(const std::string &textureFile) : ISprite(textureFile), mapWidth(0), mapHeight(0)
{
}

void Resource::generateMap(unsigned int width, unsigned int height)
{
    mapWidth = width;
    mapHeight = height;
    mapSprites.clear();

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            sf::Sprite cellSprite = sprite;
            cellSprite.setPosition(x * 128.0f, y * 128.0f);
            mapSprites.push_back(cellSprite);
        }
    }
}

unsigned int Resource::getMapWidth() const
{
    return mapWidth * 128;
}

unsigned int Resource::getMapHeight() const
{
    return mapHeight * 128;
}

void Resource::addMaterial(const std::string &type, const std::string &textureFile)
{
    sf::Texture texture;
    if (!texture.loadFromFile(textureFile)) {
        return;
    }
    materialTextures[type] = texture;
}

void Resource::generateMaterials()
{
    materials.clear();

    unsigned int totalCells = mapWidth * mapHeight;

    for (const auto& pair : resourceDensity) {
        const std::string &type = pair.first;
        float density = pair.second;
        unsigned int count = static_cast<unsigned int>(totalCells * density);
        for (unsigned int i = 0; i < count; ++i) {
            if (materialTextures.find(type) == materialTextures.end()) {
                continue;
            }
            sf::Sprite materialSprite;
            materialSprite.setTexture(materialTextures[type]);
            float x = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * (mapWidth - 1) * 128.0f;
            float y = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * (mapHeight - 1) * 128.0f;
            materialSprite.setPosition(x, y);

            materials.push_back({ materialSprite, type });
        }
    }
}

void Resource::draw(sf::RenderWindow &window) const
{
    for (const auto& cellSprite : mapSprites) {
        window.draw(cellSprite);
    }

    for (const auto& material : materials) {
        window.draw(material.sprite);
    }
}

void Resource::addResourceAt(const std::string &type, int x, int y)
{
    if (materialTextures.find(type) == materialTextures.end()) {
        return;
    }

    sf::Sprite materialSprite;
    materialSprite.setTexture(materialTextures[type]);
    materialSprite.setPosition(x * 128.0f, y * 128.0f);

    materials.push_back({ materialSprite, type });
}
