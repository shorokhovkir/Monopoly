#pragma once

#include <SFML/Graphics.hpp>
#include <cstring>


class Space {
	char* spaceType;
	int* playersOnSpace;
	int playersOnSpaceCount;
public:
	Space();
	Space(char*, int*, int);
	Space(Space&);

	void setSpaceType(const char*);
	void setPlayersOnSpace(int*, int);
	void setPlayersOnSpaceCount(int);

	char* getSpaceType();
	int* getPlayersOnSpace();
	int getPlayersOnSpaceCount();

	void putsPlayersOnSpace(int playerID);
	void removePlayersFromSpace(int);

	virtual ~Space();
};
