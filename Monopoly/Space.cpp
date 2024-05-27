#include "Space.h"
#include <cstring>

Space::Space() {
	spaceType = nullptr;
	playersOnSpace = nullptr;
	playersOnSpaceCount = 0;
}
Space::Space(char* spaceType, int* playersOnSpace, int playersOnSpaceCount) {
	int size = strlen(spaceType);
	this->spaceType = new char[size + 1];
	for (int i = 0; i < size; i++) {
		this->spaceType[i] = spaceType[i];
	}
	this->spaceType[size] = '\0';
	this->playersOnSpace = new int[playersOnSpaceCount];
	this->playersOnSpaceCount = playersOnSpaceCount;
	for (int i = 0; i < playersOnSpaceCount; i++) {
		this->playersOnSpace[i] = playersOnSpace[i];
	}
}
Space::Space(Space& cell) {
	char* temp = cell.getSpaceType();
	int* temp1 = cell.getPlayersOnSpace();

	int size = strlen(temp);
	this->spaceType = new char[size + 1];
	for (int i = 0; i < size; i++) {
		this->spaceType[i] = temp[i];
	}
	this->spaceType[size] = '\0';

	this->playersOnSpace = new int[4];
	this->playersOnSpaceCount = cell.getPlayersOnSpaceCount();
	for (int i = 0; i < playersOnSpaceCount; i++) {
		this->playersOnSpace[i] = temp1[i];
	}
}

void Space::setSpaceType(const char* spaceType) {
	int size = strlen(spaceType);
	this->spaceType = new char[size + 1];
	for (int i = 0; i < size; i++) {
		this->spaceType[i] = spaceType[i];
	}
	this->spaceType[size] = '\0';
}
void Space::setPlayersOnSpace(int* playersOnSpace, int playersOnSpaceCount) {
	this->playersOnSpace = new int[4];
	for (int i = 0; i < playersOnSpaceCount; i++) {
		this->playersOnSpace[i] = playersOnSpace[i];
	}
}
void Space::setPlayersOnSpaceCount(int playersOnSpaceCount) {
	this->playersOnSpaceCount = playersOnSpaceCount;
}

char* Space::getSpaceType() {
	return spaceType;
}
int* Space::getPlayersOnSpace() {
	return playersOnSpace;
}
int Space::getPlayersOnSpaceCount() {
	return playersOnSpaceCount;
}

void Space::putsPlayersOnSpace(int playerID) {

}
void Space::removePlayersFromSpace(int ID) {
	bool found = false;
	int index = 0;
	for (int i = 0; i < playersOnSpaceCount && found == false; i++) {
		if (playersOnSpace[i] == ID) {
			found = true;
			index = i;
		}
	}
	if (found) {
		for (int i = index; i < playersOnSpaceCount - 1; i--) {
			playersOnSpace[i] = playersOnSpace[i + 1];
		}
		playersOnSpaceCount--;
	}
}

Space::~Space() {
	if (spaceType != nullptr) {
		delete spaceType;
		spaceType = nullptr;
	}
	if (playersOnSpace != nullptr) {
		delete playersOnSpace;
		spaceType = nullptr;
	}
	playersOnSpaceCount = 0;
}