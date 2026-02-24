#include "Camera.h"
#include "DxLib.h"

void Camera::CameraUpdate(Vector2D location)
{
		// プレイヤーの中心がカメラより右に来たら、カメラを右へ追従させる
		if (location.y + OBJECT_SIZE / 2 < camera_location.y)
		{
			camera_location = location + OBJECT_SIZE / 2;
		}

		// カメラの左端がステージ外（0より左）に出ないように制限する
		if (camera_location.y - (D_WIN_MAX_Y / 2.0f) <= 0.0f)
		{
			// 左端に固定
			camera_location.y = (D_WIN_MAX_Y / 2.0f);
		}
		// カメラの右端がステージ外に出ないように制限する
		else if (camera_location.x + (D_WIN_MAX_X / 2.0f) >= STAGE_SIZE_X)
		{
			// 右端に固定
			camera_location.x = D_WIN_MAX_X / 2.0f;
		}

		// カメラの上端がステージ外に出ないように制限する
		if (camera_location.y - (D_WIN_MAX_Y / 2.0f) <= 0.0f)
		{
			// 上端に固定
			camera_location.y = (D_WIN_MAX_Y / 2.0f);
		}
		// カメラの下端がステージ外に出ないように制限する
		else if (camera_location.y + (D_WIN_MAX_Y / 2.0f) >= STAGE_SIZE_Y)
		{
			// 下端に固定
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
