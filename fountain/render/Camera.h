#if !defined(_FEI_CAMERA_H_)
#define _FEI_CAMERA_H_

#include "base/NodeBase.h"

namespace fei {

class Camera : fei::NodeBase
{
public:
	enum class Type {
		PERSPECTIVE = 1,
		ORTHOGRAPHIC = 2
	};

	void update();
private:
	Type cameraType;
};

}

#endif
