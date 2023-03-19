#pragma once

struct Vec2
{
    int x, y;

    inline bool operator==(const Vec2 &v2) const
    {
        return (x == v2.x && y == v2.y);
    }
};
