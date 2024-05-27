#pragma once
#include <iostream>

#include "Property.h"


class Player
{
private:

	char* name;
	int playerid;
	int cash;
	Property** propertylist;
	int  propertylistsize;
	bool isInJail;
	int hasJailRescueCard;
	int isbankrupt;
	int playerPosition;
	int inJailCount;
	int isRenting;

public:
	Player();
	Player(const char* Name, int Playerid);
	Player(const Player& P);
	char* getName();
	int getPlayerID();
	int getCash();
	Property** getPropertyList();
	int getPropertyListSize();
	int getIsInJail();
	int getHasJailRescueCard();
	bool getIsBankrupt();
	int getPlayerPosition();
	int getIsInJailCount();
	int getIsRenting();

	void setName(char* Name);
	void setPlayerID(int id);
	void setCash(int amount);
	void setPropertyList(Property** list, int size);
	void setPropertyListSize(int size);
	void setIsInJail(bool);
	void setHasJailRescueCard(int);
	void setIsBankrupt(bool);
	void setIsRenting(int);
	void setPlayerPosition(int);
	void setIsInJailCount(int);

	void addProperty(Property* propertyid);
	void removeProperty(Property* propertyid);
	void addCash(int amount);
	void deductCash(int amount);


	Player& operator = (const Player& p)
	{
		int i = 0, f = 0, j = 0;
		for (int k = 0; p.name[k] != '\0'; k++)
		{
			f++;
		}
		name = new char[f + 1];
		for (j = 0; j < f; j++)
		{
			name[j] = p.name[j];

		}
		name[j] = '\0';
		playerid = p.playerid;
		cash = p.cash;
		propertylist = p.propertylist;
		propertylistsize = p.propertylistsize;
		isInJail = p.isInJail;
		hasJailRescueCard = p.hasJailRescueCard;
		isbankrupt = p.isbankrupt;
	}




	int& getCashRef();
	void PropertyMortgaged(int);
	int ReturnUpgradedPrice(int);
	int SoldPropertyPrice(int);
	bool searchProperty(int);
	void atJail(Player& a);

	~Player();
};