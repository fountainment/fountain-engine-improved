#include "anime/ActionAnime.h"

using fei::ActionAnime;

ActionAnime::ActionAnime()
: _timeStateMapFunc(nullptr),
  _stateOutputMapFunc(nullptr),
  _outputFunc(nullptr)
{
}

void ActionAnime::feiObjectUpdate(fei::RenderObj* rObj)
{
	if (_timeStateMapFunc) {
		_state = _timeStateMapFunc(getClock()->getTime());
		if (_stateOutputMapFunc) {
			float output = _stateOutputMapFunc(_state);
			if (_outputFunc) {
				_outputFunc(output);
			}
		}
	}
	update(rObj);
}
