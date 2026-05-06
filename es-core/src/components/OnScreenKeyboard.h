// OnScreenKeyboard.h
#pragma once
#include "GuiComponent.h"

class OnScreenKeyboard : public GuiComponent {
public:
    OnScreenKeyboard(Window* window);
    void render(const Transform4x4f& parentTrans) override;
    void onInput(const InputCompactEvent& event) override;
    std::string getText() const;
private:
    std::string mText;
    int cursorX, cursorY;
};
