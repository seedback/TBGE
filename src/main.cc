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
#include "src/panel/content/content.h"
#include "src/panel/content/panel_content_system.h"
#include "src/panel/panel.h"
#include "src/panel/panel_system.h"
#include "src/tui/tui.h"

#define ECS_CONFIG_64BIT

ECS::Coordinator gCoordinator;

void SetupUTF8Console() {
#ifdef _WIN32
  // Set console input and output to UTF-8
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);
#endif
}

ECS::Entity CreatePanel(tbge::tui::vec2i position,
                        tbge::tui::vec2i size, int z,
                        tbge::tui::Color color,
                        tbge::tui::Color border_color) {
  ECS::Entity entity = gCoordinator.CreateEntity();
  gCoordinator.AddComponent<panel::Panel>(
      entity, panel::Panel(position, size, z, color, border_color));
  return entity;
}

void DebugPrintZIndices(std::shared_ptr<panel::PanelSystem> system) {
  std::set<ECS::Entity> entities = system->get_entities();
  int i = 0;
  for (auto entity : entities) {
    tbge::tui::SetCursorPosition(0, i + 15);
    std::cout << "Entity " << entity << " Z: "
              << gCoordinator.GetComponent<panel::Panel>(entity).get_z_index()
              << std::endl;
    i++;
  }
}

int main() {
  SetupUTF8Console();

  gCoordinator.RegisterComponentType<panel::Panel>();
  gCoordinator.RegisterComponentType<panel::Content>();

  std::shared_ptr<panel::PanelSystem> panel_system =
      gCoordinator.RegisterSystem<panel::PanelSystem>();

  ECS::Signature signature;
  signature.set(gCoordinator.GetComponentTypeId<panel::Panel>());
  gCoordinator.SetSystemSignature<panel::PanelSystem>(signature);

  std::shared_ptr<panel::PanelContentSystem> content_system =
      gCoordinator.RegisterSystem<panel::PanelContentSystem>();

  ECS::Signature content_signature;
  content_signature.set(gCoordinator.GetComponentTypeId<panel::Content>());
  content_signature.set(gCoordinator.GetComponentTypeId<panel::Panel>());
  gCoordinator.SetSystemSignature<panel::PanelContentSystem>(content_signature);

  std::vector<ECS::Entity> entities;
  entities.push_back(CreatePanel({2, 3}, {8, 5}, 0, tbge::tui::Color::kBlue,
                                 tbge::tui::Color::kBlack));
  entities.push_back(CreatePanel({6, 5}, {12, 4}, 2, tbge::tui::Color::kYellow,
                                 tbge::tui::Color::kMagenta));
  entities.push_back(CreatePanel({9, 6}, {5, 7}, 3, tbge::tui::Color::kRed,
                                 tbge::tui::Color::kBrightYellow));

  std::vector<std::string> text;
  text.push_back("Panel 1");
  text.push_back("This is a test");
  text.push_back("This is a longer test text to check width adjustment");
  text.push_back("Something extra");
  gCoordinator.AddComponent<>(entities[0], panel::Content(text));
  gCoordinator.AddComponent<>(entities[1], panel::Content("This is a one-liner with padding", {4,2}));
  text.clear();
  text.push_back("Panel 3");
  text.push_back("some text");
  gCoordinator.AddComponent<>(entities[2], panel::Content(text));

  tbge::tui::ClearScreenAndReset();

  content_system->ReconfigurePanels();
  panel_system->Redraw();
  DebugPrintZIndices(panel_system);

  int key;
  while (true) {
    key = _getch();
    if (key == 'e' || key == 'E') break;

    // Put entity to front if 1-3 is pressed
    if (key >= '1' && key <= '3') {
      int index = key - '1';
      panel_system->PutEntityToFront(index);
    } else {
      panel_system->RotatePanelZs();
    }

    panel_system->Redraw();
    DebugPrintZIndices(panel_system);
    tbge::tui::SetCursorPosition(0, 0);
  }

  tbge::tui::SetCursorPosition(0, 0);
  return 0;
}