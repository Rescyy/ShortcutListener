#include <windows.h>
#include "keyHooks.h"
// #include <iostream>

LRESULT LowLevelKeyboardProc(int, WPARAM, LPARAM);

bool KeyboardListener::shortcutMatches(std::set<char> *set, H_SHORTCUT hShortcut) {
    const char *keyCodes = hShortcut.keyCodes;
    int keyAmm = hShortcut.keyAmount;
    for (int i = 0; i < keyAmm; i++) {
        if (set->find(keyCodes[i]) == set->end()) {
            // does not contain
            return false;
        }
    }
    return true;
}

KeyboardListener::KeyboardListener() {
    hshortcuts = new std::vector<H_SHORTCUT>;
}
KeyboardListener::~KeyboardListener() {
    delete hshortcuts;
}

void KeyboardListener::addShortcut(H_SHORTCUT shortcut) {
    hshortcuts -> push_back(shortcut);
}

void KeyboardListener::startListening() {
    HHOOK kbd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
    MSG message;
    while(GetMessage(&message, 0, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

void KeyboardListener::matchShortcutEvent(std::set<char> *set) {
    for (auto itr = hshortcuts -> begin(); itr != hshortcuts -> end(); itr++) {
        if (shortcutMatches(set, *itr)) {
            itr -> eventProc();
        }
    }
}


KeyboardListener kListener = KeyboardListener();

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
            
    static std::set<char> pressedKeySet;

    KBDLLHOOKSTRUCT *kbd = (KBDLLHOOKSTRUCT *) lParam;
    char c = kbd -> vkCode;
    // std::cout << (int) kbd -> vkCode << std::endl;
    switch (wParam) {
        case WM_KEYDOWN: {
            pressedKeySet.insert(c);
        }
            break;
        case WM_KEYUP: {
            pressedKeySet.erase(c);
        }
            break;
        default:
            break;
    }

    kListener.matchShortcutEvent(&pressedKeySet);

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
