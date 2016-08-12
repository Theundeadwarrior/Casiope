#include "world.h"
#include <iostream>

World::World(unsigned int sizeX, unsigned int sizeY)
	: m_SizeX(sizeX)
	, m_SizeY(sizeY)
{
	m_WorldArray = new Chunk*[sizeY];
	for (unsigned int i = 0; i < sizeY; ++i)
	{
		m_WorldArray[i] = new Chunk[sizeX];
	}
}

World::~World()
{
	for (unsigned int i = 0; i < m_SizeY; ++i)
	{
		delete[] m_WorldArray[i];
	}
	delete[] m_WorldArray;
}

void World::Draw()
{
	std::string buffer = "";
	for (unsigned int i = 0; i < m_SizeY; ++i)
	{
		for (unsigned int j = 0; j < m_SizeX; ++j)
		{
			buffer += m_WorldArray[i][j].ToChar();
		}
		buffer += '\n';
	}
	std::cout << buffer.c_str();
}

char Chunk::ToChar()
{
	return '.';
}
