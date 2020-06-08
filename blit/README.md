# Sprite and Sound

## Introduce
 - network_gameprogramming lecture
 - 5th assignment - implement the character moving and game sound

## HOW!
 - code : Function of repeated increase and decrease of objects


 ```c++
 if (dwBlitExamples == SHRINK_N_GROW)
	{
		
		static bool	ShrinkOrGrow = 1;
		static int pos = 40;

		//증가
		if (ShrinkOrGrow) {
			pos++;
		}
		//감소
		else {
			pos--;
		}

		//position mapping
		if (pos > 100) {
			ShrinkOrGrow = 0;
		}
		if (pos < 10) {
			ShrinkOrGrow = 1;
		}

		rcDest.left = (DWORD)(640 / 2 - 120) - pos;
		rcDest.top = (DWORD)(480 / 2 - 120) - pos;
		rcDest.right = (DWORD)(640 / 2 + 120) + pos;
		rcDest.bottom = (DWORD)(480 / 2 + 120) + pos;
		ddrval = lpDDSBack->Blt(&rcDest, lpDDSFace, NULL, NULL, NULL);

		return;
		
	}

	/***************************************************************************/
}


static void finiObjects( void )
{
    if( lpDD != NULL )
    {
	if( lpDDSPrimary != NULL )
	{
	    lpDDSPrimary->Release();
	    lpDDSPrimary = NULL;
	}
	if ( lpDDSFace != NULL )
	{
		lpDDSFace->Release();
	    lpDDSFace = NULL;
	}
	lpDD->Release();
	lpDD = NULL;
    }
} /* finiObjects */


void DoFlip (void)
{
	while( 1 )
	{	
		HRESULT ddrval;
		
		ddrval = lpDDSPrimary->Flip( NULL, 0 );
		if( ddrval == DD_OK )
		    break;

		if( ddrval == DDERR_SURFACELOST )
		{
		    ddrval = lpDDSPrimary->Restore();
		    if( ddrval != DD_OK )
				break;
		}
		if( ddrval != DDERR_WASSTILLDRAWING )
		    break;
	}
```