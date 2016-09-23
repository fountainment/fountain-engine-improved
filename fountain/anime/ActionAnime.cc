#include "anime/ActionAnime.h"

#include "math/mathdef.h"

using fei::ActionAnime;

ActionAnime::ActionAnime()
: _state(0.0f),
  _timeStateMapFunc(nullptr),
  _stateOutputMapFunc(nullptr),
  _outputFunc(nullptr)
{
}

void ActionAnime::feiObjectUpdate(fei::RenderObj* rObj)
{
	if (!isStop() && _timeStateMapFunc) {
		_state = _timeStateMapFunc(getClock()->getTime());
		if (_state < 0.0f || _state > 1.0f) {
			stop();
			_state = fei::clamp(_state, 0.0f, 1.0f);
		}
		if (isPlay() && _stateOutputMapFunc) {
			float output = _stateOutputMapFunc(_state);
			if (_outputFunc) {
				_outputFunc(output);
			}
		}
	}
	update(rObj);
}

void ActionAnime::setTimeStateMapFunc(std::function<float(double)> func)
{
	_timeStateMapFunc = func;
}

void ActionAnime::setStateOutputMapFunc(std::function<float(float)> func)
{
	_stateOutputMapFunc = func;
}

void ActionAnime::setOutputFunc(std::function<void(float)> func)
{
	_outputFunc = func;
}
