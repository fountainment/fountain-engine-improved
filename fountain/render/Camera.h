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
	void update();
	void setCameraType(Type type);
	Type getCameraType();
	void setCameraScale(float scale);
	void setCameraSize(fei::Vec2 v);
private:
	float width, height;
	float left, right, bottom, top, near, far;
	Type cameraType;
	float cameraScale;
	bool needDataUpdate;

	void updateCameraData();
};

}

#endif
