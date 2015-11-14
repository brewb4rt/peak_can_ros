//  pcanwrite.cpp
//
//  ~~~~~~~~~~~~
//
//  PCANBasic Example: Simple Write
//
//  ~~~~~~~~~~~~
//
//  ------------------------------------------------------------------
//  Author : Thomas Haber (thomas@toem.de)
//  Last change: 18.06.2010
//
//  Language: C++
//  ------------------------------------------------------------------
//
//  Copyright (C) 1999-2010  PEAK-System Technik GmbH, Darmstadt
//  more Info at http://www.peak-system.com
//  ------------------------------------------------------------------
//
// linux@peak-system.com
// www.peak-system.com
//
//  ------------------------------------------------------------------
//  History:
//  07-11-2013 Stephane Grosjean
//  - Move DWORD definition from "unsigned long" to "__u32" to run on 64-bits
//    Kernel
//  - Change initital bitrate from 250K to 500K (default pcan driver bitrate)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#include <stdio.h>
#include <unistd.h>
#include <asm/types.h>

#define DWORD  __u32
#define WORD   unsigned short
#define BYTE   unsigned char
#define LPSTR  char*
#include <PCANBasic.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Main entry-point for this application. </summary>
///
/// <remarks>	 </remarks>
///
/// <param name="argc">	The argc. </param>
/// <param name="argv">	[in,out] If non-null, the argv. </param>
///
/// <returns>	. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <pthread.h> 

/*
int main(int argc, char* argv[]){
  pthread_t f1_thread; 
  void* _main(void*);
  pthread_create(&f1_thread,NULL,_main,NULL);
  pthread_join(f1_thread,NULL);
}
*/
//void* _main(void*)
int main(int argc, char* argv[])
{
	TPCANMsg Message;
	TPCANStatus Status;
	unsigned long ulIndex = 0;

	Status = CAN_Initialize(PCAN_USBBUS1, PCAN_BAUD_500K, 0, 0, 0);
	printf("Initialize CAN: %i\n",(int)Status);

	Message.ID = 0x77;
	Message.LEN = 8;
	Message.MSGTYPE = PCAN_MESSAGE_EXTENDED;
	Message.DATA[0]=0;

	while(1)
	    while ((Status=CAN_Write(PCAN_USBBUS1,&Message)) == PCAN_ERROR_OK) {
        	Message.DATA[0]++;
	        ulIndex++;
	        if ((ulIndex % 1000) == 0)
		        printf("  - T Message %i\n", (int)ulIndex);
	    }

	printf("STATUS %i\n", (int)Status);

	return 0;
}
