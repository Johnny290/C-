// Snake

#include<iostream>
#include <list>
#include <thread>
#include<Windows.h>

using namespace std;

int iScreenWidth = 120;
int iScreenHeight = 30;

struct sSnakeSegment
{
	int x;
	int y;
};

int main()
{
	//Screen Buffer
	wchar_t *screen = new wchar_t[iScreenWidth * iScreenHeight];
	for (int i = 0; i < iScreenWidth * iScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	while (1)
	{

		list<sSnakeSegment> snake = { {60,15},{61,15},{62,15},{63,15},{64,15},{65,15},{66,15},{67,15},{68,15},{69,15} };
		int iFoodX = 30;
		int iFoodY = 15;
		int iScore = 0;
		int iSnakeDirection = 3;
		bool bDead = 0;
		bool bKeyLeft = 0, bKeyRight = 0, bKeyLeftOld = 0, bKeyRightOld = 0;



		while (!bDead)
		{
			// Timing & Input
			//this_thread::sleep_for(200ms);

			
			auto t1 = chrono::system_clock::now();
			while ((chrono::system_clock::now() - t1) < ((iSnakeDirection % 2 == 1) ? 120ms : 200ms))
			{
				// Get Input
				bKeyLeft = (0x8000 & GetAsyncKeyState((unsigned char)('\x25'))) != 0;
				bKeyRight = (0x8000 & GetAsyncKeyState((unsigned char)('\x27'))) != 0;

				if (bKeyRight && !bKeyRightOld)
				{
					iSnakeDirection++;
					if (iSnakeDirection == 4) iSnakeDirection = 0;
				}

				if (bKeyLeft && !bKeyLeftOld)
				{
					iSnakeDirection--;
					if (iSnakeDirection == -1) iSnakeDirection = 3;
				}

				bKeyRightOld = bKeyRight;
				bKeyLeftOld = bKeyLeft;
			}

			// Logic
			// Update Position
			switch (iSnakeDirection)
			{
			case 0: // UP
				snake.push_front({ snake.front().x, snake.front().y - 1 });
				break;
			case 1: // RIGHT
				snake.push_front({ snake.front().x + 1, snake.front().y });
				break;
			case 2: // DOWN
				snake.push_front({ snake.front().x, snake.front().y + 1 });
				break;
			case 3: // LEFT
				snake.push_front({ snake.front().x - 1, snake.front().y });
				break;

			}

			// Collision
			// 
			// Collision Detect Area
			if (snake.front().x < 0 || snake.front().x >= iScreenWidth)
				bDead = 1;
			if (snake.front().y < 3 || snake.front().y >= iScreenHeight)
				bDead = 1;

			// Collision - Food
			if (snake.front().x == iFoodX && snake.front().y == iFoodY)
			{
				iScore += 100;
				while (screen[iFoodY * iScreenWidth + iFoodX] != L' ')
				{
					iFoodX = rand() % iScreenWidth;
					iFoodY = (rand() % (iScreenHeight - 3)) + 3;
				}

				for (int i = 0; i < 5; i++)
				{
					snake.push_back({ snake.back().x , snake.back().y });
				}
			}

			// Snake Body Collision
			for (list<sSnakeSegment>::iterator i = snake.begin(); i != snake.end(); i++)
				if (i != snake.begin() && i->x == snake.front().x && i->y == snake.front().y)
					bDead = 1;
			{

			}

			// Tail
			snake.pop_back();

			// Display


			// Clear Screen
			for (int i = 0; i < iScreenWidth * iScreenHeight; i++) screen[i] = L' ';


			// Draw Stats & Border
			for (int i = 0; i < iScreenWidth; i++)
			{
				screen[i] = L'=';
				screen[2 * iScreenWidth + i] = L'=';
			}
			wsprintf(&screen[iScreenWidth + 5], L"      S N A K E                                      SCORE: %d", iScore);


			// Draw Body
			for (auto s : snake)
			{
				screen[s.y * iScreenWidth + s.x] = bDead ? L'+' : L'O';
			}

			// Draw Head
			screen[snake.front().y * iScreenWidth + snake.front().x] = bDead ? L'X' : L'@';

			// Draw Food
			screen[iFoodY * iScreenWidth + iFoodX] = L'*';


			// Dead Condition
			if (bDead)
				wsprintf(&screen[15 * iScreenWidth + 40], L"       Press 'SPACE' To Restart");

			// Display Frame
			WriteConsoleOutputCharacter(hConsole, screen, iScreenWidth * iScreenHeight, { 0,0 }, &dwBytesWritten);
		}

		// Restart
		while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);
	}

	return 0;
}
// Inspired by javidx9
