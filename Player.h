#pragma once

#include <stddef.h>
#include "CardColor.h"

class Player
{
public :
	Player(const char* name);
	const char* GetName() const;
	size_t GetRemainingCardCount() const;
	eCardColor GetCardColor(size_t cardNum) const;
	bool HasCard(size_t cardNum) const;
	bool SelectCard(size_t cardNum);
	
private:
	enum {
		MAX_CARD_COUNT = 10,
		NAME_LEN = 25
	};
	
	size_t mRemainingCardCount = MAX_CARD_COUNT;
	bool mbCards[MAX_CARD_COUNT];
	char mName[NAME_LEN];
}; 