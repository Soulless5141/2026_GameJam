#pragma once
#include "Vector2D.h"
#include "Singleton.h"

#define D_WIN_MAX_X		(1920)	// スクリーンサイズ（幅）
#define D_WIN_MAX_Y		(1080)	// スクリーンサイズ（高さ）
#define STAGE_SIZE_X	(1920)
#define STAGE_SIZE_Y	(-480)
#define OBJECT_SIZE (32)
#define D_COLOR_BIT		(32)	// カラービット

class Camera :public Singleton<Camera>
{
private:
	Vector2D camera_location;			//
	Vector2D screen_location_origin;	//
	Vector2D screen_location;

public:
	void CameraInit();
	void CameraUpdate(Vector2D location);
	Vector2D ConvertLcoationToScreen(Vector2D location);
	Vector2D GetCameraLocation();

};

