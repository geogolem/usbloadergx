/* apploader.c
 *   by Alex Chadwick
 * 
 * Copyright (C) 2014, Alex Chadwick
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "apploader2.h"

#include <errno.h>
#include <ogc/cache.h>
#include <ogc/lwp.h>
#include <ogc/lwp_watchdog.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//#include "di/di.h"
#include "library/dolphin_os.h"
#include "library/event.h"
#include "modules/module.h"
#include "threads.h"

typedef struct {
    uint32_t boot_info_count;
    uint32_t partition_info_offset;
} contents_t;

typedef struct {
    uint32_t offset;
    uint32_t type;
} partition_info_t;

// types for the four methods called on the game's apploader
typedef void (*apploader_report_t)(const char *format, ...);
typedef void (*apploader_init_t)(apploader_report_t report_fn);
typedef int (*apploader_main_t)(void **dst, int *size, int *offset);
typedef apploader_game_entry_t (*apploader_final_t)(void);
typedef void (*apploader_entry_t)(
    apploader_init_t *init,
    apploader_main_t *main,
    apploader_final_t *final);

event_t apploader_event_disk_id;
event_t apploader_event_complete;
apploader_game_entry_t apploader_game_entry_fn = NULL;
uint8_t *apploader_app0_start = (void *) 0x80004000 ;
uint8_t *apploader_app0_end = (void *) 0x80900000 ;
uint8_t *apploader_app1_start = NULL;
uint8_t *apploader_app1_end = NULL;

#define APPLOADER_APP0_BOUNDARY ((void *)0x81200000)
#define APPLOADER_APP1_BOUNDARY ((void *)0x81400000)

//static u32 apploader_ipc_tmd[0x4A00 / 4] ATTRIBUTE_ALIGN(32);

static void *Aploader_Main(void *arg);

bool Apploader_Init(void) {
    return 
        Event_Init(&apploader_event_disk_id) &&
        Event_Init(&apploader_event_complete);
}

bool Apploader_RunBackground(void) {
    int ret;
    lwp_t thread;
    
    ret = LWP_CreateThread(
        &thread, &Aploader_Main,
        NULL, NULL, 0, THREAD_PRIO_IO);
        
    if (ret) {
        errno = ENOMEM;
        return false;
    }
    
    return true;
}

void Apploader_Report(const char *format, ...) {
#if 0
    /* debugging code, uncomment to display apploader logging messages */
    va_list args;

    va_start(args, format);
    vprintf(message, sizeof(message), format, args);
    va_end(args);
#endif
}
    
static void *Aploader_Main(void *arg) {

    Event_Trigger(&apploader_event_disk_id);
 
    Event_Wait(&module_event_list_loaded);

    Event_Trigger(&apploader_event_complete);
    
    return NULL;
}
