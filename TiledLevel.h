#pragma once
#include "GameObject.h"
#include <vector>
#include <map>

class Tile;

class TiledLevel : public GameObject
{
private:
    const char* m_tileKey;
    int m_rows;
    int m_cols;

    //Our map of 16 prototype Tile objects
    std::map<char, Tile*> m_tiles;
    std::vector<std::vector<Tile*>> m_levelTiles; //2D vector
    std::vector<Tile*> m_obstacles;

public:
    TiledLevel(int rows, int cols, int tileWidth, int tileHeight, const char* tileData, const char* levelData, const char* tileKey);
    
    ~TiledLevel();
    
    virtual void Update(float deltaTime) override;
    virtual void Render() override;

    std::vector<Tile*>& GetObstacles() { return m_obstacles; }

};

