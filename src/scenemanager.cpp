#include <memory>
#include "scene.hpp"
#include "scenemanager.hpp"


        void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene) 
        {
            if (current_scene) {
                current_scene->Exit();
            }

            newScene->SetShader(&shader);

            current_scene = std::move(newScene);
            current_scene->Enter();
        }

        void SceneManager::Update()
        {
            if (current_scene)
            {
                current_scene->Update();

                if (current_scene->nextScene)
                {
                    ChangeScene(std::move(current_scene->nextScene));
                }
            }
            
        }

        void SceneManager::Draw() 
        {
            current_scene->Draw();
        }

