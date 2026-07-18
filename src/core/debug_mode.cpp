#include "debug_mode.h"

#include "../core/global_variable.h"

void DebugMode::ActivateDebugMode(PlayerCamera& pcamera, std::vector<GameObject>* objects)
{
    camera = &pcamera;
    scene_objects = objects;
}

void DebugMode::Update()
{
    UpdateCamera(&camera->camera, CAMERA_FREE);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        ray = GetScreenToWorldRay(GetMousePosition(), camera->camera);

        collision.hit = false;
        selected_object = nullptr;

        for (GameObject& object : *scene_objects)
        {
            Matrix transform = object.GetTransform();

            for (int i = 0; i < object.model.meshCount; i++)
            {
                collision = GetRayCollisionMesh(ray, object.model.meshes[i], transform);

                if (collision.hit)
                {
                    // objet sélectionné
                }
            }
        }
    }
}

void DebugMode::Draw() {}