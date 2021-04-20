#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
    GameObject(float x, float y, float width, float height)
        : _x(x), _y(y), _width(width), _height(height)
    {
    }

    float GetX() const { return _x; }

    void SetX(float x) { _x = x; }

    float GetY() const { return _y; }

    void SetY(float y) { _y = y; }

    float GetWidth() const { return _width; };

    float GetHeight() const { return _height; }

    virtual bool IsVisible() const { return true; }

protected:
    float _x, _y;
    float _width, _height;
};

#endif