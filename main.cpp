#include "keyHooks.h"
#include <windows.h>
#include <iostream>
#include <format>

// Add here the compiled .exe file if you want the application to start at Windows Start up
// %userprofile%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup

void powerShellProc() {
    std::string command = "start C:\\Windows\\system32\\WindowsPowerShell\\v1.0\\powershell.exe -NoExit -Command Set-Location -LiteralPath ";
    std::string path = "C:\\Users";
    system((command + path).c_str());
}

void programExit() {
    exit(0);
}

const char powerShellKeys[] = "CALM";
H_SHORTCUT powerShellShortcut = {
    .keyAmount = sizeof(powerShellKeys) - 1,
    .keyCodes = powerShellKeys,
    .eventProc = powerShellProc,
};

const char exitKeys[] = "EXIT";
H_SHORTCUT exitShortcut = {
    .keyAmount = sizeof(exitKeys) - 1,
    .keyCodes = exitKeys,
    .eventProc = programExit,
};

int main() {

    kListener.addShortcut(powerShellShortcut);
    kListener.addShortcut(exitShortcut);

    std::cout << "Shortcut Listener Started. You may close the window.";
    FreeConsole();
    kListener.startListening(); // blocking process
    return 0;
}