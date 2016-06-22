#ifndef _FEI_FOUNTAINRENDEROBJ_H_
#define _FEI_FOUNTAINRENDEROBJ_H_

#include "render/FountainShader.h"
#include "render/RenderObj.h"
#include "render/Texture.h"

namespace fei {

class FountainRenderObj : public RenderObj
{
public:
	FountainRenderObj();

	void setShader(FountainShader* shader);

	void bindEmitTex(Texture* tex);
	void bindNormalTex(Texture* tex);
	void bindCullTex(Texture* tex);

	void setUseEmitTex(bool useEmitTex);
	void setUseNormalTex(bool useNormalTex);
	void setUseCullTex(bool useCullTex);
	void setUseLight(bool useLight);

private:
	int _renderMode;
	
};

} // namespace fei

#endif // _FEI_FOUNTAINRENDEROBJ_H_

