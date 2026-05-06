#include "OnScreenKeyboard.h"
#include "renderers/Renderer.h"
#include "resources/Font.h"

OnScreenKeyboard::OnScreenKeyboard(Window* window)
    : GuiComponent(window), cursorX(0), cursorY(0), currentPage(PAGE_LETTERS)
{
    loadPage(PAGE_LETTERS);
}

void OnScreenKeyboard::loadPage(KeyboardPage page)
{
    currentPage = page;
    mKeys.clear();

    if (page == PAGE_LETTERS) {
        mKeys = {
            "A","B","C","D","E","F","G","H","I",
            "J","K","L","M","N","O","P","Q","R",
            "S","T","U","V","W","X","Y","Z"," ",
            "<","123","!@#"
        };
    } else if (page == PAGE_NUMBERS) {
        mKeys = {
            "0","1","2","3","4","5","6","7","8","9",
            "-","_","+","=","/",":",";",".",",","?",
            "<","ABC","!@#"
        };
    } else if (page == PAGE_SYMBOLS) {
        mKeys = {
            "!","@","#","$","%","^","&","*","(",")",
            "[","]","{","}","<",">","|","\\","'","\"",
            "<","ABC","123"
        };
    }
}

void OnScreenKeyboard::render(const Transform4x4f& parentTrans)
{
    Transform4x4f trans = parentTrans;
    Renderer::setMatrix(trans);

    auto font = Font::get(FONT_SIZE_MEDIUM);
    int cols = 9;
    int cellW = 40;
    int cellH = 40;

    for (size_t i = 0; i < mKeys.size(); i++) {
        int x = (i % cols) * cellW;
        int y = (i / cols) * cellH;

        unsigned int color = 0xFFFFFFFF;
        if ((int)(i % cols) == cursorX && (int)(i / cols) == cursorY)
            color = 0x00FF00FF; // highlight cursor

        // Build a text cache and draw it
        TextCache* cache = font->buildTextCache(mKeys[i], x, y, color);
        font->renderTextCache(cache);
        delete cache;
    }
}


bool OnScreenKeyboard::input(InputConfig* config, Input input)
{
    int cols = 9;
    int rows = (mKeys.size() + cols - 1) / cols;

    if (input.value) {
        if (config->isMappedTo("left", input))  cursorX = (cursorX + cols - 1) % cols;
        if (config->isMappedTo("right", input)) cursorX = (cursorX + 1) % cols;
        if (config->isMappedTo("up", input))    cursorY = (cursorY + rows - 1) % rows;
        if (config->isMappedTo("down", input))  cursorY = (cursorY + 1) % rows;

        if (config->isMappedTo("a", input)) { // “A” button = select
            int idx = cursorY * cols + cursorX;
            if (idx < (int)mKeys.size()) {
                std::string key = mKeys[idx];
                if (key == "<") {
                    if (!mText.empty()) mText.pop_back();
                } else if (key == "ABC") {
                    loadPage(PAGE_LETTERS);
                } else if (key == "123") {
                    loadPage(PAGE_NUMBERS);
                } else if (key == "!@#") {
                    loadPage(PAGE_SYMBOLS);
                } else {
                    mText += key;
                }
            }
        }

        if (config->isMappedTo("b", input)) {
            // Optional: handle “B” button as cancel/back
            return false; 
        }
    }
    return true;
}

std::string OnScreenKeyboard::getText() const
{
    return mText;
}
