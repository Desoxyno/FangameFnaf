#include "camera_system.h"

void Camera_System::InitializeCameras()
{
    cameras[0].camera.position = {14.8f, 4.6f, 0.8f};
    cameras[0].camera.target = {731.0f, -209.0f, -661.0f};
};

void Camera_System::Update()
{
    UpdateCamera(&cameras[current_camera].camera, CAMERA_CUSTOM);
};