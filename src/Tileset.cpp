/**
 * \file Tileset.cpp
 * \author Mathieu BAGUE
 * \date 23/04/2016
 */

#include <ios>

#include <zzbgames/tileset/Tileset.hpp>

namespace zzbgames
{

namespace tileset
{

Tileset::Tileset(const std::string& filename, const Dimension& tileSize, const Insets& margin, const Insets& spacing)
    : m_image(),
      m_texture(),
      m_tileSize(tileSize),
      m_margin(margin),
      m_spacing(spacing),
      m_gridSize(0, 0)
{
    if (!m_image.loadFromFile(filename))
        throw std::ios_base::failure("Failed to load resource " + filename);

    if (!m_texture.loadFromImage(m_image))
        throw std::ios_base::failure("Failed to load resource " + filename);

    computeGridSize();
}

Tileset::Tileset(const sf::Image& image, const Dimension& tileSize, const Insets& margin, const Insets& spacing)
    : m_image(image),
      m_texture(),
      m_tileSize(tileSize),
      m_margin(margin),
      m_spacing(spacing),
      m_gridSize(0, 0)
{
    if (!m_texture.loadFromImage(m_image))
        throw std::ios_base::failure("Failed to load image");

    computeGridSize();
}

void Tileset::computeGridSize()
{
    unsigned long tileWidth = m_spacing.getLeft() + m_tileSize.getWidth() + m_spacing.getRight();
    unsigned long tileHeight = m_spacing.getTop() + m_tileSize.getHeight() + m_spacing.getBottom();

    Dimension textureSize(m_texture.getSize());

    m_gridSize.setWidth((textureSize.getWidth() - m_margin.getLeft() - m_margin.getRight()) / tileWidth);
    m_gridSize.setHeight((textureSize.getHeight() - m_margin.getTop() - m_margin.getBottom()) / tileHeight);
}

unsigned long Tileset::getColumnCount() const
{
    return m_gridSize.getWidth();
}

const sf::Image& Tileset::getImage() const
{
    return m_image;
}

const Insets& Tileset::getMargin() const
{
    return m_margin;
}

unsigned long Tileset::getRowCount() const
{
    return m_gridSize.getHeight();
}

const Insets& Tileset::getSpacing() const
{
    return m_spacing;
}

std::unique_ptr<sf::Image> Tileset::getTileAsImage(unsigned long tileIndex) const
{
    const sf::IntRect& spriteArea = getTileAsRect(tileIndex);

    unsigned int width = static_cast<unsigned int>(std::max(0, spriteArea.width));
    unsigned int height = static_cast<unsigned int>(std::max(0, spriteArea.height));

    std::unique_ptr<sf::Image> image(new sf::Image());
    image->create(width, height);
    image->copy(m_image, 0, 0);

    return image;
}

sf::IntRect Tileset::getTileAsRect(unsigned long tileIndex) const
{
    sf::IntRect spriteArea;
    if (tileIndex < getTileCount())
    {
        unsigned long rowIndex = tileIndex / getColumnCount();
        unsigned long columnIndex = tileIndex % getColumnCount();

        unsigned long tileWidth = m_spacing.getLeft() + m_tileSize.getWidth() + m_spacing.getRight();
        unsigned long tileHeight = m_spacing.getTop() + m_tileSize.getHeight() + m_spacing.getBottom();

        spriteArea.left = static_cast<unsigned int>(m_margin.getLeft() + columnIndex * tileWidth);
        spriteArea.top = static_cast<unsigned int>(m_margin.getTop() + rowIndex * tileHeight);
        spriteArea.width = static_cast<unsigned int>(m_tileSize.getWidth());
        spriteArea.height = static_cast<unsigned int>(m_tileSize.getHeight());
    }

    return spriteArea;
}

std::unique_ptr<sf::Sprite> Tileset::getTileAsSprite(unsigned long tileIndex) const
{
    const sf::IntRect& spriteArea = getTileAsRect(tileIndex);

    return std::unique_ptr<sf::Sprite>(new sf::Sprite(m_texture, spriteArea));
}

unsigned long Tileset::getTileCount() const
{
    return m_gridSize.getHeight() * m_gridSize.getWidth();
}

const Dimension& Tileset::getTileSize() const
{
    return m_tileSize;
}

}


}