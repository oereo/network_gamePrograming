# Sprite and Sound

## Introduce
 - network_gameprogramming lecture
 - 6th assignment - implement the character moving and game sound

## HOW!
 - code : when push the left button(Mouse)

 ```c++
 if (_GetKeyState(VK_LBUTTON)) {
		if (moving) {
			pos = pos + 100;
		}
		else {
			pos = pos - 100;
		}
		if (pos > 500) {
			moving = 0;
		}
		if (pos < 100) {
			moving = 1;
		}

		SpriteRect.left = Frame * 100 + pos;
		SpriteRect.top = 0;
		SpriteRect.right = SpriteRect.left + 100;
		SpriteRect.bottom = 70;

	}
```