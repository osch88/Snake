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
        tileHeight_ = screenHeight_ / numbersOfTiles_;
    }
    void SetScreenWidth(int x)
    {
        screenWidth_ = x;
        tileWidth_ = screenWidth_ / numbersOfTiles_;
    }
    int GetTileHeight() { return tileHeight_; }
    int GetTileWidth() { return tileWidth_; }
    int GetNumersOfTiles() { return numbersOfTiles_; }
    // void SetNumersOfTiles(int x) { numbersOfTiles_ = x; }

private:
    Utilities() {}
    int screenHeight_, screenWidth_;
    int tileHeight_, tileWidth_;
    int numbersOfTiles_ = 20;
    static Utilities* instance_;
};
