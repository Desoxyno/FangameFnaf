#include <initializer_list>
#include <string>
#include <vector>

#include "raylib.h"

class Dropdown
{
public:
    Rectangle rect;
    bool opened = false;
    int selected = 0;

    std::vector<std::string> items;

    Dropdown(Rectangle r, std::initializer_list<std::string> values)
        : rect(r)
        , items(values)
    {
    }

    bool Update();
    void Draw();
};