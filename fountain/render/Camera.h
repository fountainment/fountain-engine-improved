#if !defined(_FEI_CAMERA_H_)
#define _FEI_CAMERA_H_

#include "base/NodeBase.h"
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

	const Vec2 screenToWorld(const Vec2& scrPos);
	const Vec2 worldToScreen(const Vec2& wrdPos);

private:
	float width, height;
	float left, right, bottom, top, near, far;
	Type cameraType;
	float cameraScale;
	bool needDataUpdate;

	void updateCameraData();
};

} // namespace fei

#endif // _FEI_CAMERA_H_
