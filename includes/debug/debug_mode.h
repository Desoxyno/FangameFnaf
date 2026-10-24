// #ifdef DEBUG_BUILD

// #pragma once

// #include "models/gameobject.h"
// #include "raylib.h"

// #include <cfloat>
// #include <string>

// #include "scenes/scene.h"
// #include "ennemies/springtrap/springtrap.h"

// // #include "utils/dropdown.h"

// class DebugMode
// {
// public:
//     enum class Mode
//     {
//         Position,
//         Scale
//     };
//     enum class SubMode
//     {
//         X,
//         Y,
//         Z
//     };

//     // Dropdown level_menu{{10, 10, 180, 30}, {"Main Menu", "Night1"}};
//     float amount_to_move = 1.0f;
//     float scrollSpeed = 0.05f;

//     Scenes requestedScene;

//     Mode mode = Mode::Position;
//     SubMode submode = SubMode::X;
//     Ray ray = {0};
//     RayCollision collision = {0};
//     Scene* current_scene = nullptr;
//     GameObject* selected_object;

//     void ActivateDebugMode(Scene* scene);
//     void Update();
//     void Draw();
//     void Reset();

//     std::string ModeToString(Mode mode)
//     {
//         switch (mode)
//         {
//             case Mode::Position:
//                 return "Position";
//             case Mode::Scale:
//                 return "Scale";
//             default:
//                 return "Unknown";
//         }
//     }

//     std::string SubModeToString(SubMode submode)
//     {
//         switch (submode)
//         {
//             case SubMode::X:
//                 return "X";

//             case SubMode::Y:
//                 return "Y";

//             case SubMode::Z:
//                 return "Z";

//             default:
//                 return "Unknown";
//         }
//     }
// };

// inline void DebugMode::ActivateDebugMode(Scene* scene)
// {
//     current_scene = scene;
//     selected_object = nullptr;
// }

// inline void DebugMode::Update()
// {
//     if (!current_scene)
//     {
//         return;
//     }

//     amount_to_move += GetMouseWheelMove() * scrollSpeed;
//     amount_to_move = Clamp(amount_to_move, 0.01f, 100.0f);

//     Camera& camera = current_scene->camera;
//     auto scene_objects = current_scene->GetSceneObjects();

//     if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
//     {
//         UpdateCamera(&camera, CAMERA_FREE);
//     }

//     if (IsKeyPressed(KEY_W))
//     {
//         switch (mode)
//         {
//             case Mode::Position:
//                 mode = Mode::Scale;
//                 break;

//             case Mode::Scale:
//                 mode = Mode::Position;
//                 break;
//         }
//     }

//     if (IsKeyPressed(KEY_X))
//     {
//         switch (submode)
//         {
//             case SubMode::X:
//                 submode = SubMode::Y;
//                 break;

//             case SubMode::Y:
//                 submode = SubMode::Z;
//                 break;

//             case SubMode::Z:
//                 submode = SubMode::X;
//                 break;
//         }
//     }

//     if (selected_object)
//     {
//         float direction = 0;

//         if (IsKeyPressed(KEY_LEFT))
//         {
//             direction = -amount_to_move;
//         }

//         if (IsKeyPressed(KEY_RIGHT))
//         {
//             direction = amount_to_move;
//         }

//         if (direction != 0)
//         {
//             if (mode == Mode::Position)
//             {
//                 switch (submode)
//                 {
//                     case SubMode::X:
//                         selected_object->GetPosition()->x += direction;
//                         break;

//                     case SubMode::Y:
//                         selected_object->GetPosition()->y += direction;
//                         break;

//                     case SubMode::Z:
//                         selected_object->GetPosition()->z += direction;
//                         break;
//                 }
//             }
//             else
//             {
//                 *selected_object->GetScale() += direction;
//             }
//         }
//     }

//     if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
//     {
//         return;
//     }

//     ray = GetScreenToWorldRay(GetMousePosition(), camera);

//     selected_object = nullptr;

//     float closestDistance = FLT_MAX;

//     for (GameObject *object : *scene_objects)
//     {
//         for (int i = 0; i < object->GetModel()->meshCount; i++)
//         {
//             RayCollision hit = GetRayCollisionMesh(ray, object->GetModel()->meshes[i], MatrixIdentity());

//             if (hit.hit && hit.distance < closestDistance)
//             {
//                 closestDistance = hit.distance;
//                 collision = hit;
//                 selected_object = object;
//             }
//         }
//     }
// }

// inline void DebugMode::Draw()
// {
//     DrawText("Debug Mode", 10, 10, 20, RAYWHITE);

//     DrawText(ModeToString(mode).c_str(), 10, 160, 20, RAYWHITE);

//     DrawText(SubModeToString(submode).c_str(), 10, 180, 20, RAYWHITE);

//     DrawText(std::to_string(amount_to_move).c_str(), 10, 200, 20, RAYWHITE);

//     std::string cam_target = "Camera Target X:" + std::to_string(current_scene->camera.target.x) +
//                              " Y:" + std::to_string(current_scene->camera.target.y) +
//                              " Z:" + std::to_string(current_scene->camera.target.z);

//     std::string cam_pos = "Camera Position X:" + std::to_string(current_scene->camera.position.x) +
//                           " Y:" + std::to_string(current_scene->camera.position.y) +
//                           " Z:" + std::to_string(current_scene->camera.position.z);

//     DrawText(cam_target.c_str(), 10, 220, 20, RAYWHITE);

//     DrawText(cam_pos.c_str(), 10, 240, 20, RAYWHITE);

//     BeginMode3D(current_scene->camera);

//     for (GameObject *object : *current_scene->GetSceneObjects())
//     { 
//             if (object->type == Animatronic) {

//                 DrawCube({object->positionM.x, 1, object->positionM.z} , 0.25f, 0.25f, 0.25f, RED);

//                 Springtrap* springtrap = dynamic_cast<Springtrap*>(object);

//                  for (auto& node : springtrap->all_nodes) {
//                      DrawCube(node->position, 0.5f, 0.5f, 0.5f, RED);
//                      for (auto& Nnode : node->neighbors_nodes) {
//                          DrawLine3D(node->position, Nnode->position, GREEN);
//                     }
                    
//                 }
//         }
//     }

//     EndMode3D();

//     if (!selected_object || !current_scene)
//     {
//         return;
//     }

//     std::string position = "Position X:" + std::to_string(selected_object->GetPosition()->x) +
//                            " Y:" + std::to_string(selected_object->GetPosition()->y) +
//                            " Z:" + std::to_string(selected_object->GetPosition()->z);

//     std::string scale = "Scale:" + std::to_string(*selected_object->GetScale());

//     DrawText(position.c_str(), 10, 100, 20, RAYWHITE);

//     DrawText(scale.c_str(), 10, 120, 20, RAYWHITE);
// }

// inline void DebugMode::Reset()
// {
//     current_scene = nullptr;
//     selected_object = nullptr;
// }

// #endif