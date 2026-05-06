// OnScreenKeyboard.cpp
#include "OnScreenKeyboard.h"
#include "Renderer.h"

OnScreenKeyboard::OnScreenKeyboard(Window* window) : GuiComponent(window) {
    cursorX = cursorY = 0;
}

void OnScreenKeyboard::render(const Transform4x4f& parentTrans) {
    // Draw a simple grid of letters
    // Highlight cursor position
}

void OnScreenKeyboard::onInput(const InputCompactEvent& event) {
    // Handle d-pad navigation
    // Handle A button to select letter
    // Append to mText
}

std::string OnScreenKeyboard::getText() const {
    return mText;
}
