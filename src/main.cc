#include <codecvt>  // Required for std::wstring_convert and std::codecvt_utf8
#include <iomanip>
#include <iostream>
#include <limits>

#ifdef _WIN32
#include <conio.h>  // Add this for _getch()
#include <fcntl.h>
#include <io.h>
#include <windows.h>  // Add this for SetConsoleCP/SetConsoleOutputCP

#include <locale>
#endif

#include "src/terminal/terminal.h"

void SetupUTF8Console() {
#ifdef _WIN32
  // Set console input and output to UTF-8
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);
#endif
}

int main() {
  SetupUTF8Console();

  return 0;
}