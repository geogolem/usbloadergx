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

typedef apploader_game_entry_t (*apploader_final_t)(void);

event_t apploader_event_complete;
apploader_game_entry_t apploader_game_entry_fn = NULL;
uint8_t *apploader_app0_start = (void *) 0x80004000 ;
uint8_t *apploader_app0_end = (void *) 0x80900000 ;

static void *Aploader_Main(void *arg);

bool Apploader_Init(u32 AppEntrypoint) {
    apploader_game_entry_fn = (void *) AppEntrypoint;
    return 
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
   
static void *Aploader_Main(void *arg) {
  
    Event_Wait(&module_event_list_loaded);
    
    // Some of this stuff needs to be here (or somewhere) refer to disc.c of usbloader and/or memory.h

    //os0->info.boot_type = OS_BOOT_NORMAL;
    //os0->info.version = 1;
    //os0->info.mem1_size = 0x01800000;
    //os0->info.console_type = 1 + ((*(uint32_t *)0xcc00302c) >> 28);
    
    /* // We definitely need this.. i think
    os0->info.arena_high = os0->info.arena_high - module_list_size;
    os0->info.fst = (char *)os0->info.fst - module_list_size;
    os0->info.fst_size += module_list_size;
    */

    //os0->threads.debug_monitor_location = (void *)0x81800000;
    //os0->threads.simulated_memory_size = 0x01800000;
    //os0->threads.bus_speed = 0x0E7BE2C0;
    //os0->threads.cpu_speed = 0x2B73A840;
    
    /* FIXME: We don't currently reload IOS. To prevent Error #002 we pretend
     * like we have. */
    
    //os1->ios_number = os1->expected_ios_number;
    //os1->ios_revision = os1->expected_ios_revision;

    //os1->fst = os0->info.fst;

    //DCFlushRange(os0, 0x3f00);
    
    Event_Trigger(&apploader_event_complete);
    
    return NULL;
}
