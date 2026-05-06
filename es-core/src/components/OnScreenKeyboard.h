#pragma once
#include "GuiComponent.h"
#include <vector>
#include <string>

enum KeyboardPage { PAGE_LETTERS, PAGE_NUMBERS, PAGE_SYMBOLS };

class OnScreenKeyboard : public GuiComponent {
public:
    OnScreenKeyboard(Window* window);

    void render(const Transform4x4f& parentTrans) override;
    void onInput(Input input); // adapted for ES input events
    std::string getText() const;

private:
    void loadPage(KeyboardPage page);

    std::vector<std::string> mKeys;
    std::string mText;
    int cursorX, cursorY;
    KeyboardPage currentPage;
};
