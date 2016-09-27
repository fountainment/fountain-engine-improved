#ifndef _FEI_CAMERA_H_
#define _FEI_CAMERA_H_

#include "base/NodeBase.h"
#include "math/Rect.h"
#include "math/Vec2.h"

namespace fei {

class Camera : public fei::NodeBase
{
public:
	enum class Type {
		ORTHOGRAPHIC = 1,
		PERSPECTIVE = 2
	};

	Camera();
	~Camera();

	void update();
	void setCameraType(Type type);
	Type getCameraType();
	void setCameraScale(float scale);
	float getCameraScale();
	void zoomCameraScale(float zoom);
	void zoomCameraScaleAtCenter(const Vec2& center, float zoom);
	void setCameraSize(const Vec2& v);
	const Vec2 getCameraSize();
	void setCameraRect(const Rect& r);
	const Rect getCameraRect();
	void setCameraZPos(float z);
	float getCameraZPos();

	const Vec2 screenToWorld(const Vec2& scrPos);
	const Vec2 worldToScreen(const Vec2& wrdPos);

	static constexpr float orthoCameraNear_ = -99999.0f;
	static constexpr float orthoCameraFar_ = 99999.0f;
	static constexpr float perspectiveCameraNear_ = 100.0f;
	static constexpr float perspectiveCameraFar_ = 2000.0f;

private:
	Type _cameraType;
	float _cameraScale;
	float _cameraZPos;
	float _width, _height;
	float _left, _right, _bottom, _top;
	bool _needDataUpdate;

	void updateCameraData();
};

} // namespace fei

#endif // _FEI_CAMERA_H_
