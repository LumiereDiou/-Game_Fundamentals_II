#include "TiledLevel.h"
#include "Game.h"
#include "Tile.h"
#include "TextureManager.h"
#include <fstream>

TiledLevel::TiledLevel(int rows, int cols, int tileWidth, int tileHeight,
	const char* tileData, const char* levelData, const char* tileKey)
	: m_tileKey(tileKey)
	, m_rows(rows)
	, m_cols(cols)
{
	std::ifstream inFile(tileData);
	if (inFile.is_open())
	{
		char key;
		int x;
		int y;
		bool isObstacle;
		bool isHazard;
		while (!inFile.eof())
		{
			inFile >> key >> x >> y >> isObstacle >> isHazard;
			m_tiles.emplace(key, new Tile(
				{ x * tileWidth, y * tileHeight, tileWidth, tileHeight },
				{ 0.0f, 0.0f, (float)tileWidth, (float)tileHeight }, isObstacle, isHazard));
		}
	}
	
	inFile.close();
	inFile.open(levelData);
	if (inFile.is_open())
	{
		char key;
		m_levelTiles.resize(m_rows);
		for (int row = 0; row < m_rows; ++row)
		{
			m_levelTiles[row].resize(m_cols);
			for (int col = 0; col < m_cols; ++col)
			{
				inFile >> key;
				m_levelTiles[row][col] = m_tiles[key]->Clone();
				m_levelTiles[row][col]->SetXY((float)(col * tileWidth), (float)(row * tileHeight));
				if (m_levelTiles[row][col]->IsObstacle())
				{
					m_obstacles.push_back(m_levelTiles[row][col]);
				}
				if (m_levelTiles[row][col]->IsHazard())
				{
					m_hazards.push_back(m_levelTiles[row][col]);
				}
			}
		}
	}
	inFile.close();

}

TiledLevel::~TiledLevel()
{
	//clear the tile clones. this also clears the one in m_obstacles
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			delete m_levelTiles[row][col];
			m_levelTiles[row][col] = nullptr;
		}
	}
	m_levelTiles.clear();
	m_obstacles.clear();
	m_hazards.clear();
	//clear the original tiles
	for (std::map<char, Tile*>::iterator i = m_tiles.begin(); i != m_tiles.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}
	m_tiles.clear();
}

void TiledLevel::Update(float deltaTime)
{

}

void TiledLevel::Render()
{
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture(m_tileKey),
				m_levelTiles[row][col]->GetSourceTransform(), m_levelTiles[row][col]->GetDestinationTransform());
		}
	}
}