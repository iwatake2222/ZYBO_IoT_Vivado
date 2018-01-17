/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "sleep.h"
#include "xparameters.h"
#include "mypwm.h"
#include "myip.h"

void testMyPWM()
{
//	MYPWM_mWriteReg(XPAR_MYPWM_0_S00_AXI_BASEADDR, MYPWM_S00_AXI_SLV_REG3_OFFSET, 100);
//	MYPWM_mWriteReg(XPAR_MYPWM_0_S00_AXI_BASEADDR, MYPWM_S00_AXI_SLV_REG4_OFFSET, 0);
//	MYPWM_mWriteReg(XPAR_MYPWM_0_S00_AXI_BASEADDR, MYPWM_S00_AXI_SLV_REG5_OFFSET, 0);

	while(1) {
		for (int dutyR = 0; dutyR < 100; dutyR += 1) {
			printf("R = %d\n", dutyR);
			for (int dutyG = 0; dutyG < 100; dutyG += 1) {
				for (int dutyB = 0; dutyB < 100; dutyB += 1) {
					MYPWM_mWriteReg(XPAR_MYPWM_0_S00_AXI_BASEADDR, MYPWM_S00_AXI_SLV_REG0_OFFSET, dutyR);
					MYPWM_mWriteReg(XPAR_MYPWM_0_S00_AXI_BASEADDR, MYPWM_S00_AXI_SLV_REG1_OFFSET, dutyG);
					MYPWM_mWriteReg(XPAR_MYPWM_0_S00_AXI_BASEADDR, MYPWM_S00_AXI_SLV_REG2_OFFSET, dutyB);
					usleep(1*10);
				}
			}
		}
	}
}

void testMyIP()
{
	while(1) {
		int btn;
		btn = MYIP_mReadReg(XPAR_MYIP_0_S00_AXI_BASEADDR, MYIP_S00_AXI_SLV_REG1_OFFSET);
		MYIP_mWriteReg(XPAR_MYIP_0_S00_AXI_BASEADDR, MYIP_S00_AXI_SLV_REG0_OFFSET, btn & 0x0F);

		btn = MYIP_mReadReg(XPAR_MYIP_0_S00_AXI_BASEADDR, MYIP_S00_AXI_SLV_REG2_OFFSET);
		printf("%04X\n", btn & 0x0F);
	}

}

int main()
{
	init_platform();

	print("Hello World\n\r");

//	testMyPWM();


	testMyIP();


	cleanup_platform();
	return 0;
}
