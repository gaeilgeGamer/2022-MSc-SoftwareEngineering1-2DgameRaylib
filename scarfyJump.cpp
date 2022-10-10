#include "raylib.h"
int main(){
 const int windowWidth{700};
 const int windowHeight{450};
InitWindow(windowWidth,windowHeight,"My Window");

//const int width{50};
//const int height{80};
const int gravity{1000};

Texture2D scarfy = LoadTexture("resources/scarfy.png");
Texture2D background = LoadTexture("resources/cyberpunk_street_background.png");
Texture2D midground = LoadTexture("resources/cyberpunk_street_midground.png");
Texture2D foreground = LoadTexture("resources/cyberpunk_street_foreground.png");

Rectangle scarfyRec;
scarfyRec.width = scarfy.width/6;
scarfyRec.height = scarfy.height;
scarfyRec.x = 0;
scarfyRec.y = 0; 
Vector2 scarfyPos;
scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
scarfyPos.y = windowHeight - scarfyRec.height;

int frame{};
const float updateTime{1.0/12};
float runningTime{};

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;

//int posY{windowHeight-height};
int velocity{0};
const int jumpHeight{500};
bool jumped{false};
int speed{200};
SetTargetFPS(60);  
	while(!WindowShouldClose()){
	const float deltaTime{GetFrameTime()};

	    scrollingBack -= 0.1f;
        scrollingMid -= 0.5f;
        scrollingFore -= 1.0f;

		if (scrollingBack <= -background.width*2)
			{ 
			scrollingBack = 0;
			}
        if (scrollingMid <= -midground.width*2)
			{ 
			scrollingMid = 0;
			}
        if (scrollingFore <= -foreground.width*2)
			{ 
			scrollingFore = 0;
			}

	if(IsKeyDown(KEY_D))
{
	scarfyPos.x += speed*deltaTime;
	scarfyRec.width = scarfy.width/6;

	runningTime += deltaTime; 
	if(runningTime >= updateTime)
	{
	runningTime = 0.0;
	scarfyRec.x = frame* scarfyRec.width;
	frame++;
	if (frame>5){
	frame = 0;
	}

	}
}
if(IsKeyReleased(KEY_D)&& !jumped)
{frame = 0;
scarfyRec.x = frame* scarfyRec.width;}
if(IsKeyDown(KEY_A)&& !jumped)
{
	scarfyPos.x -= speed*deltaTime;
	scarfyRec.width = -scarfy.width/6;

	runningTime += deltaTime; 
	if(runningTime >= updateTime)
	{
	runningTime = 0.0;
	scarfyRec.x = frame* scarfyRec.width;
	frame++;
	if (frame>5){
	frame = 0;
	}

	}
}
if(IsKeyReleased(KEY_A)&& !jumped)
{frame = 0;
scarfyRec.x = frame* scarfyRec.width;}
BeginDrawing();

//if (posY >= windowHeight - height){
if (scarfyPos.y >= windowHeight - scarfy.height){

	velocity=0;
	jumped = false; 
}
else 
{velocity += gravity * deltaTime;
jumped = true;
}
if(IsKeyPressed(KEY_SPACE) && !jumped)
{
	velocity -= jumpHeight;
}

//posY += velocity;
scarfyPos.y += velocity * deltaTime; 
ClearBackground(WHITE); 
            
			DrawTextureEx(background, (Vector2){ scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);

            // Draw midground image twice
            DrawTextureEx(midground, (Vector2){ scrollingMid, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(midground, (Vector2){ midground.width*2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);

            // Draw foreground image twice
            DrawTextureEx(foreground, (Vector2){ scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(foreground, (Vector2){ foreground.width*2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE); 
//DrawRectangle(windowWidth/2,posY,width,height,GREEN);
DrawTextureRec(scarfy,scarfyRec,scarfyPos,WHITE);
EndDrawing();
}
UnloadTexture(scarfy);
    UnloadTexture(background);  // Unload background texture
    UnloadTexture(midground);   // Unload midground texture
    UnloadTexture(foreground); 
CloseWindow();
}