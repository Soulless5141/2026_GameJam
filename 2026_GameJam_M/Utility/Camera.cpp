#include "Camera.h"
#include "DxLib.h"

void Camera::CameraUpdate(Vector2D location)
{
    // ‡@ ‰¡•ûŒü‚ÍŠ®‘SŒÅ’è
    camera_location.x = D_WIN_MAX_X / 2.0f;

    // ‡A ã•ûŒü‚¾‚¯’Ç]
    if (location.y < camera_location.y)
    {
        camera_location.y = location.y;
    }

    // ‡B ã’[§ŒÀ
    if (camera_location.y - (D_WIN_MAX_Y / 2.0f) <= 0.0f)
    {
        camera_location.y = (D_WIN_MAX_Y / 2.0f);
    }
    // ‡C ‰º’[§ŒÀ
    else if (camera_location.y + (D_WIN_MAX_Y / 2.0f) >= STAGE_SIZE_Y)
    {
        camera_location.y = STAGE_SIZE_Y - (D_WIN_MAX_Y / 2.0f);
    }

}

Vector2D Camera::ConvertLcoationToScreen(Vector2D location)
{
	screen_location_origin = {
		camera_location.x - D_WIN_MAX_X / 2.0f,
		camera_location.y - D_WIN_MAX_Y / 2.0f
	};


	screen_location = {
		location.x - screen_location_origin.x,
		location.y - screen_location_origin.y
	};
	return screen_location;
}

Vector2D Camera::GetCameraLocation()
{
	return camera_location;
}

void Camera::CameraInit()
{
	camera_location = 0;
}
