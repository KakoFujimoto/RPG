#include "Input.h"
#include <DxLib.h>

void Input::update()
{

}

bool Input::isPressed(GameKey key) const
{
	switch (key)
	{
	case GameKey::Cancel:
		return CheckHitKey(KEY_INPUT_ESCAPE) != 0;
	case GameKey::Decide:
		return CheckHitKey(KEY_INPUT_RETURN) != 0;
	case GameKey::Up:
		return CheckHitKey(KEY_INPUT_UP) != 0;
	case GameKey::Down:
		return CheckHitKey(KEY_INPUT_DOWN) != 0;
	case GameKey::Left:
		return CheckHitKey(KEY_INPUT_LEFT) != 0;
	case GameKey::Right:
		return CheckHitKey(KEY_INPUT_RIGHT) != 0;
	}
	return false;
}
