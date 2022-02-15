#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "Player.h"

#define s_player1_WIN (0)
#define s_player2_WIN (1)
#define DRAW		(2)
#define WINNER_NOT_DICIDED (-1)

#define BUFFER_LENGTH (1024)

Player s_player1("s_player1");
Player s_player2("s_player2");

size_t s_player1Score = 0;
size_t s_player2Score = 0;
	
static size_t sGetNumber();
static void sShowRemainingCards(const Player& player);

int main(void) 
{
	{
		printf("START PLAYER TEST\n");

		Player s_player1("VeryVeryVeryGoodGreatName");

		assert(0 == strcmp("VeryVeryVeryGoodGreatNam", s_player1.GetName()));
		printf("Name: %s\n", s_player1.GetName());

		assert(10 == s_player1.GetRemainingCardCount());
		printf("Number of Card Count: %lu\n\n", s_player1.GetRemainingCardCount());

		// printf("Card[10]: %lu", s_player1.GetCardNum(10));
		for (size_t i = 0; i < s_player1.GetRemainingCardCount(); ++i) {
			printf("Num: %lu, Color: %s\n", i, s_player1.GetCardColor(i) == eCardColor::BLACK ? "black" : "white");
		}

		assert(s_player1.SelectCard(3) == true);
		assert(s_player1.SelectCard(9) == true);
		assert(s_player1.SelectCard(3) == false);

		assert(s_player1.GetRemainingCardCount() == 8);

		assert(s_player1.SelectCard(4) == true);
		assert(s_player1.SelectCard(5) == true);
		assert(s_player1.SelectCard(6) == true);

		assert(s_player1.SelectCard(4) == false);
		assert(s_player1.SelectCard(5) == false);
		assert(s_player1.SelectCard(6) == false);

		assert(s_player1.GetRemainingCardCount() == 5);

		printf("END PLAYER TEST\n\n");
	}
	
	bool finishedGame = false;
	size_t winner = WINNER_NOT_DICIDED;
	
	size_t roundNum = 1;
	
	printf("=== %s vs %s ===\n", s_player1.GetName(), s_player2.GetName());
		
	while (!finishedGame) 
	{
		printf("Round %lu\n", roundNum);
		
		printf("[%s]", s_player1.GetName());
		sShowRemainingCards(s_player1);
		
		size_t s_player1Num = (size_t)-1;
		while (true)
		{
			s_player1Num = sGetNumber();	
			if (s_player1.SelectCard(s_player1Num) == true)
			{
				break;
			}
			
			printf("that number already used!\n");
		} 
		
		printf("[%s]", s_player2.GetName());
		sShowRemainingCards(s_player2);
		
		size_t s_player2Num = (size_t)-1;
		while (true)
		{
			s_player2Num = sGetNumber();
			if (s_player2.SelectCard(s_player2Num) == true)
			{
				break;
			}
			
			printf("that number already used!\n");
		}
		
		assert(s_player1Num != (size_t)-1 && s_player2Num != (size_t)-1);
		
		if (s_player1Num == s_player2Num) {
			printf("draw!\n\n");
		}
		else if (s_player1Num > s_player2Num) 
		{
			printf("%s win!\n\n", s_player1.GetName());	
			++s_player1Score;
		} 
		else
		{
			printf("%s win!\n\n", s_player2.GetName());
			++s_player2Score;
		}
		
		if (roundNum >= 10) 
		{
			finishedGame = true;
			
			if (s_player1Score == s_player2Score) 
			{
				winner = DRAW;
			}
			else
			{
				winner = (s_player1Score > s_player2Score) ? s_player1_WIN : s_player2_WIN;
			}
		}
		
		++roundNum;
	}
	
	assert(winner != (size_t)WINNER_NOT_DICIDED);
	printf("winner: %s!", (winner == s_player1_WIN) ? s_player1.GetName() : s_player2.GetName());
	
	return 0;
}

static size_t sGetNumber() 
{
	char buffer[BUFFER_LENGTH];	
	int num;
	while (true)
	{
		printf("pick (0~9): ");
		fgets(buffer, BUFFER_LENGTH, stdin);

		if (sscanf(buffer, "%d", &num) == 1 && (0 <= num && num <= 9)) 
		{
			break;
		}
	}
	
	return (size_t)num;
}

static void sShowRemainingCards(const Player& player)
{
	const int MAX_NUM_CARD = 10;
	
	char buffer[BUFFER_LENGTH];
	char* ptr = buffer;	
	
	/*
	*ptr++ = '[';
	for (size_t i = 0; i < MAX_NUM_CARD; ++i)
	{
		if (player.HasCard(i))
		{
			if (*(ptr - 1) != '[') 
			{
				strcpy(ptr, ", ");
				ptr += 2;
			}			
			
			*(ptr++) = '0' + i;	
		}
	}
	
	*(ptr++) = ']';
	*(ptr++) = '\0';
	*/
	
	*ptr = '[';
	for (size_t i = 0; i < MAX_NUM_CARD; ++i)
	{
		if (player.HasCard(i))
		{
			if (*ptr != '[') 
			{
				++ptr;
				strcpy(ptr, ", ");
				ptr += 1;
			}			
			
			*(++ptr) = '0' + i;	
		}
	}
	
	*(++ptr) = ']';
	*(++ptr) = '\0';
	
	printf("%s\n", buffer);
}