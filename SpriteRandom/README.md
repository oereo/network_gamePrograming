# Sprite and Sound

## Introduce
 - network_gameprogramming lecture
 - 7th assignment - implement the character moving and game sound

## HOW!
 - code1 : when push the SPACE Button, character wield a knife
 - code2 : when push the Arrow keys, character moves
 - code3 : Random creation of 20 obstacles
 - code4 : When the character hits an obstacle, the blast expression and sound of the obstacle

 ```c++
 void CALLBACK _GameProc(HWND hWnd, UINT message, UINT wParam, DWORD lParam)
{
	RECT BackRect = { 0, 0, 640, 480 };
	RECT DispRect = { 0, 0, gWidth, gHeight };
	RECT SpriteRect, WinRect, dstRect;


	BackScreen->BltFast(0, 0, BackGround, &BackRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
	BackScreen->BltFast(640, 0, BackGround, &BackRect, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

	static int Frame = 0;

	SpriteRect.left = Frame * 100;
	SpriteRect.top = 0;
	SpriteRect.right = SpriteRect.left + 100;
	SpriteRect.bottom = 70;

	if (Click) {
		if (++Frame >= 4) {
			Frame = 0;
			Click = 0;
		}
	}

	if (MouseX <= 50) MouseX = 50;
	if (MouseX > gWidth - 50) MouseX = gWidth - 50;
	if (MouseY <= 35) MouseY = 35;
	if (MouseY > gHeight - 35) MouseY = gHeight - 35;

	BackScreen->BltFast(MouseX - 50, MouseY - 35, SpriteImage, &SpriteRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);




	//////////////////////////////
	// Enter splite animation here
	// use srand(int seed); rand();
	// stone            (380, 375)            (405, 395)
	// flare            (360, 425)            (390, 455)


	srand(100);
	numb += 3;
	for (int i = 0; i < 20; i++)
	{
		dstRect.left = (rand() - numb) % 1280;
		dstRect.top = rand() % 320;
		int a;
		a = rand() % 60;
		dstRect.right = dstRect.left + a;
		dstRect.bottom = dstRect.top + a;

		if ((MouseX >= dstRect.left && MouseX <= dstRect.right && MouseY <= dstRect.bottom && MouseY >= dstRect.top) ||
			(MouseX >= dstRect.left - 15 && MouseX <= dstRect.right + 15 && MouseY <= dstRect.bottom && MouseY >= dstRect.top - 30))
		{
			if (soundk == 0)
			{
				_Play(4);
				soundk = 1;
			}
			SpriteRect.left = 360;
			SpriteRect.top = 425;
			SpriteRect.right = 390;
			SpriteRect.bottom = 455;
			
		}
		else
		{
			SpriteRect.left = 380;
			SpriteRect.top = 375;
			SpriteRect.right = 405;
			SpriteRect.bottom = 395;
			soundk = 0;
		}

		BackScreen->Blt(&dstRect, Gunship, &SpriteRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	}

	if ((MouseX >= dstRect.left && MouseX <= dstRect.right && MouseY <= dstRect.bottom && MouseY >= dstRect.top) ||
		(MouseX >= dstRect.left - 15 && MouseX <= dstRect.right + 15 && MouseY <= dstRect.bottom && MouseY >= dstRect.top - 30))
	{
		//_Play(4);
		if (soundk == 0)
		{
			_Play(4);
			soundk = 1;
		}
	}
	else
	{
		soundk = 0;
	}

	/*dstRect.left = 400;
	dstRect.top = 300;
	dstRect.right = dstRect.left+30;
	dstRect.bottom = dstRect.top+30;
	*/
	//BackScreen->Blt(&dstRect, Gunship, &SpriteRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);


	if (gFullScreen)
		RealScreen->Flip(NULL, DDFLIP_WAIT);
	else {
		GetWindowRect(MainHwnd, &WinRect);
		RealScreen->Blt(&WinRect, BackScreen, &DispRect, DDBLT_WAIT, NULL);
	}
}
```

 ```c++
 long FAR PASCAL WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int Step = 5;


	switch (message)
	{

	case    WM_MOUSEMOVE:   MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		break;

	case	WM_LBUTTONDOWN: 	Click = 1;
		_Play(3);
		break;
	case	WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
		case VK_F12:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;

		case VK_LEFT:
			MouseX -= 10;
			return 0;

		case VK_RIGHT:
			MouseX += 10;
			return 0;

		case VK_UP:
			MouseY -= 10;
			return 0;

		case VK_DOWN:
			MouseY += 10;
			return 0;

		case VK_SPACE:
			Click = 1;
			_Play(3);
			break;
		}
		break;

	case    WM_DESTROY:  _ReleaseAll();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
 ```