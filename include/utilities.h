#pragma once

class Utilities {
public:
    static Utilities& Instance()
    {
        static Utilities* instance_ = new Utilities();
        return *instance_;
    }
    int GetScreenHeight() { return screenHeight_; }
    int GetScreenWidth() { return screenWidth_; }
    void SetScreenHeight(int x)
    {
        screenHeight_ = x;
        tileHeight_ = screenHeight_ / numbersOfTiles;
    }
    void SetScreenWidth(int x)
    {
        screenWidth_ = x;
        tileWidth_ = screenWidth_ / numbersOfTiles;
    }
    int GetTileHeight() { return tileHeight_; }
    int GetTileWidth() { return tileWidth_; }

private:
    Utilities() {}
    int screenHeight_, screenWidth_;
    int tileHeight_, tileWidth_;
    int numbersOfTiles = 20;
    static Utilities* instance_;
};
