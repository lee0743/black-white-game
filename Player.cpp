#include "Player.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Player::Player(const char* name) 
{
	srand(time(NULL));
	strncpy(mName, name, NAME_LEN);
	mName[NAME_LEN - 1] = '\0';
	
	for (size_t i = 0; i < mRemainingCardCount; ++i) 
	{
		mbCards[i] = true;
	}
}

const char* Player::GetName() const
{
	return mName;	
}

size_t Player::GetRemainingCardCount() const
{
	return mRemainingCardCount;
}

eCardColor Player::GetCardColor(size_t cardNum) const
{
	assert(0 <= cardNum && cardNum < MAX_CARD_COUNT);
	return (cardNum % 2 == 0) ? eCardColor::BLACK : eCardColor::WHITE;
}

bool Player::HasCard(size_t cardNum) const
{
	assert(0 <= cardNum && cardNum < MAX_CARD_COUNT);
	
	return mbCards[cardNum];
}

bool Player::SelectCard(size_t cardNum) 
{
	assert(0 <= cardNum && cardNum < MAX_CARD_COUNT);
	
	if (mbCards[cardNum] == true) {
		mbCards[cardNum] = false;
		--mRemainingCardCount;
		
		return true;
	}
	
	return false;
}

