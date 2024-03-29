#ifndef KEYHOOKS_H
#define KEYHOOKS_H
#include <set>
#include <vector>

#define KEY_TAB 9
#define KEY_CAPS_LOCK 20
#define KEY_LSHIFT 160
#define KEY_RSHIFT 161
#define KEY_LCONTROL 162
#define KEY_RCONTROL 163
#define KEY_LALT 164
#define KEY_RALT 165

typedef void (*EVENT_PROC) (void);

typedef struct KEYBOARD_SHORTCUT_HANDLE {
    int keyAmount;
    const char *keyCodes;
    EVENT_PROC eventProc;
} H_SHORTCUT;

class KeyboardListener {
    private:
        std::vector<H_SHORTCUT> *hshortcuts;
        std::set<char> pressedKeySet;
        bool shortcutMatches(std::set<char> *set, H_SHORTCUT hShortcut);

    public:
        KeyboardListener();
        ~KeyboardListener();

        void addShortcut(H_SHORTCUT shortcut);
        void startListening();
        void matchShortcutEvent(std::set<char> *set);
};

extern KeyboardListener kListener;

#endif