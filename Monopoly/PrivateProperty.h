#pragma once

#include "Property.h"

#include <cstring>
#include <iostream>

class PrivateProperty :public Property
{

	int houseCount;
	int hotelCount;
	int shopCount;
	bool hasWifi;
	bool hasGas;
	bool hasElectricity;
public:

	PrivateProperty();
	PrivateProperty(char*, int*, int, char*, char*, int, int, bool, int, int, int, int, int, int, bool, bool, bool);
	PrivateProperty(PrivateProperty&);

	void setHouseCount(int);
	void setHotelCount(int);
	void setShopCount(int);
	void setHasWifi(bool);
	void setHasGas(bool);
	void setHasElectricity(bool);

	int getHouseCount();
	int getHotelCount();
	int getShopCount();
	int getPurchasePrice();
	int getRentPrice();
	bool getHasWifi();
	bool getHasGas();
	bool getHasElectricity();

	bool isUpgraded();
	void addHouse();
	void addHotel();
	void addShop();
	void addWifi();
	void addGas();
	void addElectricity();
	int calculateRent();

	void putsPlayersOnSpace(int& playerCash, int dealChoice);

	~PrivateProperty();
};
