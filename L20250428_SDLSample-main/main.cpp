#include <vector>
#include "SDL3/SDL.h"

#pragma comment(lib, "SDL3")
void DrawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y) {
		SDL_RenderPoint(renderer, centerX + x, centerY + y);
		SDL_RenderPoint(renderer, centerX + y, centerY + x);
		SDL_RenderPoint(renderer, centerX - y, centerY + x);
		SDL_RenderPoint(renderer, centerX - x, centerY + y);
		SDL_RenderPoint(renderer, centerX - x, centerY - y);
		SDL_RenderPoint(renderer, centerX - y, centerY - x);
		SDL_RenderPoint(renderer, centerX + y, centerY - x);
		SDL_RenderPoint(renderer, centerX + x, centerY - y);

		if (err <= 0) {
			y += 1;
			err += 2 * y + 1;
		}
		else {
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

int main()
{
	// Initialize
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	SDL_Window* MyWindow = SDL_CreateWindow("Sample", 640, 480, SDL_WINDOW_OPENGL);

	SDL_Renderer* MyRenderer = SDL_CreateRenderer(MyWindow, NULL);

	// ���α׷����� ����Ҷ� "����� ����"�� Polling ���� �Ѵٰ� �Ѵ�.
	bool isRunning = true;
	SDL_Event MyEvent;
	while (isRunning)
	{
		SDL_PollEvent(&MyEvent);
		switch (MyEvent.type)
		{
		case SDL_EVENT_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}


		// SDL_Renderer �� ���� ���ϱ�
		SDL_SetRenderDrawColor(MyRenderer, 0, 0, 0, 0);

		// ��ü ȭ�鿡 ĥ�ϱ�
		SDL_RenderClear(MyRenderer);



		// �簢��
		SDL_FRect Rectangle[100] = { NULL, };;
		for (int i = 0; i < 100; i++)
		{
			SDL_FRect Rect = { SDL_rand(640), SDL_rand(480), 10, 10 };
			Rectangle[i] = Rect;
		}
		SDL_SetRenderDrawColor(MyRenderer, 255, 0, 0, 0);
		SDL_RenderFillRects(MyRenderer, Rectangle, 100);

		// ��
		SDL_SetRenderDrawColor(MyRenderer, 255, 255, 255, 0);
		DrawCircle(MyRenderer, 320, 240, 100);
		SDL_RenderPresent(MyRenderer);

		//CPU�� RAM�� ���� ����. ������ GPU�� ����Ҷ� �ʿ��� ���������� stack���ĸ��� �׾Ƶΰ�
		// SDL_RenderFillRects(MyRenderer, ...);
		// RAM�� stack �� �׿� �ִ� Rect���� �ѹ��� GPU�� ���� �����
		SDL_RenderPresent(MyRenderer);
	}

	SDL_Delay(1000); // milliseconds �и������� ����

	SDL_DestroyRenderer(MyRenderer);

	SDL_DestroyWindow(MyWindow);

	SDL_Quit();

	return 0;
}