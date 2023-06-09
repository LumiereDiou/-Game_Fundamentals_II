#pragma once
#include "Sprite.h"
class Tile :
    public SpriteObject
{
private:
    bool m_obstacle;
    bool m_hazard;
public:
    Tile(SDL_Rect source, SDL_FRect destination, bool obstacle, bool hazard)
        : SpriteObject(source, destination)
        , m_obstacle(obstacle)
        , m_hazard(hazard)
    {

    }

    Tile* Clone()
    {
        return new Tile(m_sourceTransfrom, m_destinationTransform, m_obstacle, m_hazard);
    }

    bool IsObstacle() { return m_obstacle; }
    bool IsHazard() { return m_hazard; }
    void SetXY(float x, float y) { m_destinationTransform.x = x, m_destinationTransform.y = y; }
    void Update(float deltaTime) override {}
    void Render() override {}

};

