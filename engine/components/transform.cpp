#include "transform.h"
#include <iostream>

using namespace nim;

Transform::Transform() : size(1.0f, 1.0f), position(0.f, 0.f) {
    std::cout << "[Transform] Default Constructor"
              << "\n";
}

Transform::Transform(Vector2 size, Vector2 position) {
    std::cout << "[Transform] (Vector2, Vector2) Constructor"
              << "\n";
    this->position = position;
    this->size = size;
    SetRect();
}

Transform::Transform(const Transform &other) {
    std::cout << "[Transform] Copy Constructor"
              << "\n";
    size = other.size;
    position = other.position;
    SetRect();
}

Transform::Transform(Transform &&other) {
    std::cout << "[Transform] Move Constructor"
              << "\n";
    size = other.size;
    position = other.position;
    rect = std::move(other.rect);

    other.position = 0;
    other.size = 0;
}

Transform::~Transform() {
    // delete rect;
    //rect = nullptr;
}

Transform &Transform::operator=(const Transform &other) {
    if (&other != this) {
        size = other.size;
        position = other.position;
        SetRect();
    }
    return *this;
}
Transform &Transform::operator=(Transform &&other) {
    if (&other != this) {
        size = other.size;
        position = other.position;
        rect = std::move(other.rect);

        other.position = 0;
        other.size = 0;
    }
    return *this;
}

void Transform::Size(Vector2 *size) {
    this->size.x = size->x;
    this->size.y = size->y;
    SetRect();
}
void Transform::Size(Vector2 &&size) {
    this->size = size;
    SetRect();
}
void Transform::Position(const Vector2 *position) {
    this->position.x = position->x;
    this->position.y = position->y;
    SetRect();
}
void Transform::Position(Vector2 &&position) {
    this->position = position;
    SetRect();
}
void Transform::Size(float width, float height) {
    size.x = width;
    size.y = height;
    SetRect();
}
void Transform::Position(float x, float y) {
    position.x = x;
    position.y = y;
    SetRect();
}

SDL_FRect *Transform::GetRect() {
    SetRect();
    return rect.get();
}

void Transform::SetRect() {
    if (rect == nullptr)
        rect = std::make_unique<SDL_FRect>();
    rect->x = position.x;
    rect->y = position.y;
    rect->w = size.x;
    rect->h = size.y;
}