#include <iostream>

#include "raylib.h"
#include "Battle/Actors/FighterGameState.h"
#include "Render/RenderState.h"

#include "WindowsIncludeFix.h"

int main(int argc, char* argv[])
{
    const int screenWidth = 320;
    const int screenHeight  = 240;
	const int windowWidth = screenWidth * 6;
    const int windowHeight  = screenHeight * 6;

    InitWindow(windowWidth, windowHeight, "Night Sky Engine -Lite-");

    SetTargetFPS(60);
	const RenderTexture2D renderTexture = LoadRenderTexture(screenWidth, screenHeight);

    FighterGameState* GameState = new FighterGameState();
    GameState->Init();
    
    RenderState* CurRenderState = new RenderState(GameState);
    CurRenderState->Init();

	double NewTime = 0;
    while (!WindowShouldClose())
    {
		// TODO: Capsulize all this into a "scene"
        GameState->TickGameState();
    	
        BeginDrawing();
			BeginTextureMode(renderTexture);
            	ClearBackground(RAYWHITE);
            	CurRenderState->Draw();
			EndTextureMode();

			// TODO: Keep aspect ratio and draw borders
			DrawTexturePro(
				renderTexture.texture,
				{ 0.0f, 0.0f, (float)screenWidth, -(float)screenHeight },
				{ 0.0f, 0.0f, (float)windowWidth, (float)windowHeight },
				{ 0.0f, 0.0f },
				0.0f, WHITE
			);

        EndDrawing();
    }

    CloseWindow();
	if (argc == 5)
		WSACleanup();
	
    return 0;
}