#include "SDL3/SDL.h"

#pragma comment(lib, "SDL3")

int main()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	SDL_Window* MyWindow = SDL_CreateWindow("Sample", 640, 480, SDL_WINDOW_OPENGL);

	SDL_Renderer* MyRenderer = SDL_CreateRenderer(MyWindow, nullptr);

	bool IsRunning = true;
	SDL_Event MyEvent;

	int NumKeys = 0;
	const bool* KeyStates = SDL_GetKeyboardState(&NumKeys);

	int PlayerX = 0;
	int PlayerY = 0;
	while (IsRunning)
	{
		SDL_PollEvent(&MyEvent);
		switch (MyEvent.type)
		{
		case SDL_EVENT_QUIT:
			IsRunning = false;
			break;
		case SDL_EVENT_KEY_DOWN:
			if (KeyStates[SDL_SCANCODE_UP])
			{
				PlayerY -= 10;
			}
			if (KeyStates[SDL_SCANCODE_DOWN])
			{
				PlayerY += 10;
			}
			if (KeyStates[SDL_SCANCODE_LEFT])
			{
				PlayerX -= 10;
			}
			if (KeyStates[SDL_SCANCODE_RIGHT])
			{
				PlayerX += 10;
			}
			if (KeyStates[SDL_SCANCODE_ESCAPE])
			{
				IsRunning = false;
			}
		default:
			break;
		}

		SDL_SetRenderDrawColor(MyRenderer, 0, 0, 0, 0);
		SDL_RenderClear(MyRenderer);

		SDL_FRect Player = { (float) PlayerX, (float) PlayerY, 100, 100 };
		SDL_SetRenderDrawColor(MyRenderer, 255, 255, 255, 0);
		SDL_RenderFillRect(MyRenderer, &Player);

		//for (int i = 0; i < 1000; ++i)
		//{
		//	SDL_SetRenderDrawColor(MyRenderer,
		//		SDL_rand(255),
		//		SDL_rand(255),
		//		SDL_rand(255),
		//		0);
		//	SDL_FRect MyRect{ SDL_randf() * 640 - 320,
		//		SDL_randf() * 480 - 240,
		//		SDL_randf() * 640, SDL_randf() * 480
		//	};
		//	SDL_RenderFillRect(MyRenderer, &MyRect);
		//}

		//SDL_SetRenderDrawColor(MyRenderer, 255, 0, 0, 0);

		//int Radius = 200;
		//int X = 320;
		//int Y = 240;
		//int PrevCirCleX = Radius * SDL_cos(0) + X;
		//int PrevCirCleY = Radius * SDL_sin(0) + Y;
		//for (int Angle = 10; Angle <= 360; Angle += 10 )
		//{
		//	int CircleX = Radius * SDL_cos(Angle * SDL_PI_F / 180) + X;
		//	int CircleY = Radius * SDL_sin(Angle * SDL_PI_F / 180) + Y;
		//	SDL_RenderLine(MyRenderer, PrevCirCleX, PrevCirCleY,
		//		CircleX, CircleY);
		//	PrevCirCleX = CircleX;
		//	PrevCirCleY = CircleY;
		//}



		SDL_RenderPresent(MyRenderer);
	}

	SDL_DestroyRenderer(MyRenderer);

	SDL_DestroyWindow(MyWindow);

	SDL_Quit();

	return 0;
}