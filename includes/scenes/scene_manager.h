#pragma once

#include <cassert>
#include <memory>
#include <raylib.h>
#include "global_variables.h"
#include "scene.h"

#include "config/global_paths.h"
#include "scenes/mainmenu.h"
#include "scenes/night.h"

class SceneManager {
    std::unique_ptr<Scene> current_scene = std::make_unique<MainMenu>(mainmenu_paths);
    std::unique_ptr<Scene> pending_scene;

    public:
        void Tick() {

            if (CheckIfExit()) {
                current_scene = std::move(pending_scene);
            }

            current_scene->Update();

            BeginDrawing();
                ClearBackground(BLACK);
                current_scene->Draw();
            EndDrawing();
        }

        bool CheckIfExit() {
            switch (current_scene->SceneWanted) {
                case NO_CHANGE:
                    return false;
                case MAIN_MENU: 
                    pending_scene = std::make_unique<MainMenu>(mainmenu_paths);
                    pending_scene->camera = camera_mainmenu;
                    return true;
                case NIGHT1:
                    pending_scene = std::make_unique<Night1>(night1_paths);
                    pending_scene->camera = camera_night1;
                    return true;
            }
            return false;
        }
};