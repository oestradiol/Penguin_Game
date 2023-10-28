#include "headers/Collider.h"

#ifdef DEBUG
#include "../core/headers/Game.h"
#include "../core/headers/Camera.h"

#include <SDL2/SDL.h>
#endif // DEBUG

void Collider::Render() {
#ifdef DEBUG
	Vec2 center( box.Center() );
	SDL_Point points[5];

    Sprite* goSprite = static_cast<Sprite*>(associated.GetComponent("Sprite"));
    float angle = goSprite ? goSprite->GetRotation() * M_PI / 180 : 0;
	Vec2 point = (Vec2(box.x, box.y) - center).Rotated(angle)
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).Rotated(angle)
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotated(angle)
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).Rotated(angle)
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset)
    : Component(associated), scale(scale), offset(offset) {
}

void Collider::Update(float dt) {
    box = associated.box;
    box.w = box.w * scale.x;
    box.h = box.h * scale.y;
    Sprite* goSprite = static_cast<Sprite*>(associated.GetComponent("Sprite"));
    float angle = goSprite ? goSprite->GetRotation() * M_PI / 180 : 0;
    box.SetCenter(associated.box.Center() + offset.Rotated(angle));
}