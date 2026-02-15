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

#include "absl/log/check.h"
#include "absl/log/initialize.h"
#include "absl/log/log.h"
#include "src/ecs/ecs.h"
#include "src/panel/panel.h"
#include "src/panel/panel_system.h"
#include "src/tui/tui.h"

ECS::Coordinator<ECS::Context<>> gCoordinator;

void SetupUTF8Console() {
#ifdef _WIN32
  // Set console input and output to UTF-8
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);
#endif
}

void CreatePanel(tbge::tui::vec2i position, tbge::tui::vec2i size, int z,
                 tbge::tui::Color color, tbge::tui::Color border_color) {
  ECS::Context<>::Entity entity = gCoordinator.CreateEntity();
  gCoordinator.AddComponent<>(
      entity, panel::Panel(position, size, z, color, border_color));
}

int main() {
  SetupUTF8Console();

  gCoordinator.RegisterComponentType<panel::Panel<>>();

  std::shared_ptr<panel::PanelSystem<>> panel_system =
      gCoordinator.RegisterSystem<panel::PanelSystem<>>();

  ECS::Context<>::Signature signature;
  signature.set(gCoordinator.GetComponentTypeId<panel::Panel<>>());
  gCoordinator.SetSystemSignature<panel::PanelSystem<>>(signature);

  CreatePanel({2, 3}, {8, 5}, 0, tbge::tui::Color::kBlue,
              tbge::tui::Color::kBlack);
  CreatePanel({12, 6}, {5, 7}, 3, tbge::tui::Color::kRed,
              tbge::tui::Color::kBrightYellow);
  CreatePanel({6, 5}, {12, 4}, 2, tbge::tui::Color::kYellow,
              tbge::tui::Color::kMagenta);

  tbge::tui::ClearScreenAndReset();

  panel_system->Redraw();
  tbge::tui::SetCursorPosition(0,0);

  _getch();
  return 0;
}