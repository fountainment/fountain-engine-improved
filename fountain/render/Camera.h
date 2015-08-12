#if !defined(_FEI_CAMERA_H_)
#define _FEI_CAMERA_H_

#include "base/NodeBase.h"

namespace fei {

class Camera : fei::NodeBase
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
private:
	Type cameraType;
	float cameraScale;
};

}

#endif
