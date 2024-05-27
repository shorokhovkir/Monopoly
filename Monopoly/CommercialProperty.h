#pragma once

#include "Property.h"

#include <cstring>


class CommercialProperty :public Property {
public:

	CommercialProperty();
	CommercialProperty(char* spaceType, int*, int, char*, char*, int, int, bool, int, int, int);
	CommercialProperty(CommercialProperty&);

	int getPurchasePrice();
	int getRentPrice();

	~CommercialProperty();
};
