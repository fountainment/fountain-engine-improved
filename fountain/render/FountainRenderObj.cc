#include "render/FountainRenderObj.h"

using fei::FountainRenderObj;

FountainRenderObj::FountainRenderObj()
{
};

void FountainRenderObj::setShader(fei::FountainShader* shader)
{
	fei::RenderObj::setShader(shader);
}
