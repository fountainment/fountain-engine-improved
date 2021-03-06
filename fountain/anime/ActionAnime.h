#ifndef _FEI_ACTIONANIME_H_
#define _FEI_ACTIONANIME_H_

#include "anime/Anime.h"
#include "base/basedef.h"
#include "render/RenderObj.h"

namespace fei {

class ActionAnime : public Anime
{
public:
	ActionAnime();

	virtual void feiObjectUpdate(RenderObj* rObj) override;

	void setTimeStateMapFunc(std::function<float(double)> func);
	void setStateOutputMapFunc(std::function<float(float)> func);
	void setOutputFunc(std::function<void(float)> func);

private:
	float _state;

	std::function<float(double)> _timeStateMapFunc;
	std::function<float(float)> _stateOutputMapFunc;
	std::function<void(float)> _outputFunc;
};

} // namespace fei

#endif // _FEI_ACTIONANIME_H_
