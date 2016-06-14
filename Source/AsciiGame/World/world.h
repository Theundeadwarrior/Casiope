#pragma once

class Chunk
{
public:
	char ToChar();
};

class World
{
public:
	World(unsigned int sizeX, unsigned int sizeY);
	~World();

	void Draw();

private:
	Chunk** m_WorldArray;
	unsigned int m_SizeX;
	unsigned int m_SizeY;
};

