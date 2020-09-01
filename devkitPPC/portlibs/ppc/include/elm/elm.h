/*---------------------------------------------------------------------------/
/  LibELM - Devoptab functions for ELM FatFs                (C)SquidMan, 2009
/----------------------------------------------------------------------------/
/ LibELM is an open source FAT driver for the Nintendo Wii, based on the ELM
/ FatFs module.
/
/  Copyright (C) 2009, SquidMan, all right reserved.
/
/ * LibELM is free software and there is NO WARRANTY.
/ * This product may not be sold for profit, but may be used in any way
/   otherwise.
/ * Redistributions of source code must retain the above copyright notice.
/----------------------------------------------------------------------------/
/ FatFs module is an open source software to implement FAT file system to
/ small embedded systems. This is a free software and is opened for education,
/ research and commercial developments under license policy of following trems.
/
/  Copyright (C) 2009, ChaN, all right reserved.
/
/ * The FatFs module is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/----------------------------------------------------------------------------*/

#ifndef __ELMDEVOPTAB_H__
#define __ELMDEVOPTAB_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FRESMADE
#define FRESMADE
#define FR_OK			0
#define FR_DISK_ERR		1
#define FR_INT_ERR		2
#define FR_NOT_READY		3
#define FR_NO_FILE		4
#define FR_NO_PATH		5
#define FR_INVALID_NAME		6
#define FR_DENIED		7
#define FR_EXIST		8
#define FR_INVALID_OBJECT	9
#define FR_WRITE_PROTECTED	10
#define FR_INVALID_DRIVE	11
#define FR_NOT_ENABLED		12
#define FR_NO_FILESYSTEM	13
#define FR_MKFS_ABORTED		14
#define FR_TIMEOUT		15
#define FRESULT			int
#endif

#ifndef ELM_SD
#define ELM_SD			0
#endif
#ifndef ELM_USB
#define ELM_USB			1
#endif
#ifndef ELM_GCA
#define ELM_GCA			2
#endif
#ifndef ELM_GCB
#define ELM_GCB			3
#endif

int ELM_Mount();
int ELM_MountDevice(int device);
void ELM_UnmountDevice(int device);
void ELM_Unmount();
int ELM_GetError();

#ifdef __cplusplus
}
#endif		
		
#endif /* __ELMDEVOPTAB_H__ */

