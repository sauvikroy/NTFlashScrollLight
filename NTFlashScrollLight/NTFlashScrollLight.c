/*
** NTFlashScrollLight.c 
**
**  Copyright 1999 Mark J. McGinty, All Rights Reserved
**	 Free Usage granted to the public domain.
**
**
**	Short test program, to excersize NTKbdLites.c
**
*/


#include <windows.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "NTKbdLites.h"


#define CANCEL_EVENT_NAME	"TestThreadedFlasherEvent"

//#define USE_THREAD


void __cdecl main(int argc, char **argv)

#ifdef USE_THREAD
{
	HANDLE heventCancel = CreateEvent(NULL, FALSE, FALSE, CANCEL_EVENT_NAME);

	HANDLE hThread = FlashKeyboardLightInThread(KEYBOARD_SCROLL_LOCK_ON, 250, CANCEL_EVENT_NAME);


	printf("\r\n              NTFlashScrollLight");
	printf("\r\nCopyright 1999 Mark J. McGinty, All Rights Reserved");
	printf("\r\n     (Free Usage granted to the public domain.)");
	printf("\r\n\r\nSample usage of IOCTL_KEYBOARD_SET_INDICATORS");
	printf("\r\n\r\n (the Scroll Lock light should be flashing)");
	printf("\r\n\r\n\r\npress any key to exit...");
	_getch();

	printf("\r\n");

	SetEvent(heventCancel);

	WaitForSingleObject(hThread, 30000);

	CloseHandle(heventCancel);

	exit(0);
}

#else

	// A non-threaded way to do the same thing
	//

{
	HANDLE			hndKbdDev;
	int i;

	hndKbdDev = OpenKeyboardDevice(NULL);

	if (hndKbdDev == INVALID_HANDLE_VALUE)		// Was the device opened?
	{
		int e = GetLastError();
		printf("Unable to open the device. (error %d)\n", e);
		exit(1);
	}

	printf("\r\npress any key to exit...");

	i=1;
	do {
		FlashKeyboardLight(hndKbdDev, i, 100);
		 i = (i <= 4? (i << 1) : 1);
	} while(!_kbhit());

	CloseKeyboardDevice(hndKbdDev);
	exit(0);
}
#endif
