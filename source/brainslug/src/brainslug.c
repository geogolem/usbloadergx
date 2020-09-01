/* main.c
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

#include "brainslug.h"

#include <fat.h>
#include <malloc.h>
#include <ogc/consol.h>
#include <ogc/lwp.h>
#include <ogc/system.h>
#include <ogc/video.h>
#include <sdcard/wiisd_io.h>
#include <stdio.h>
#include <stdlib.h>

#include "apploader/apploader2.h"
#include "library/dolphin_os.h"
#include "library/event.h"
#include "modules/module.h"
#include "search/search.h"
#include "threads.h"

//event_t main_event_fat_loaded;

static void Main_PrintSize(size_t size);

int BrainslugPatches() {

    SYS_SetArena1Hi((void *)0x81200000);

    if (!__io_wiisd.startup() || !__io_wiisd.isInserted()) {
        printf("Please insert an SD card.\n\n");
        do {
            __io_wiisd.shutdown();
        } while (!__io_wiisd.startup() || !__io_wiisd.isInserted());
    }
    __io_wiisd.shutdown();
    
    if (!fatMountSimple("sd", &__io_wiisd)) {
        fprintf(stderr, "Could not mount SD card.\n");
        return -1;
    }


    if (!Apploader_Init())
        return -1;
    if (!Module_Init())
        return -1;
    if (!Search_Init())
        return -1;
    
    /* main thread is UI, so set thread prior to UI */
    LWP_SetThreadPriority(LWP_GetSelf(), THREAD_PRIO_UI);
    
    /* spawn lots of worker threads to do stuff */
    if (!Apploader_RunBackground())
        return -1;
    if (!Module_RunBackground())
        return -1;
    if (!Search_RunBackground())
        return -1;
      
    Event_Wait(&module_event_list_loaded);
    // we make it here. if i put a return 0 in here the game launches.
    if (module_list_count == 0) {
        printf("No valid modules found!\n");
    } else {
        size_t module;
        
        printf(
            "%u module%s found.\n",
            module_list_count, module_list_count > 1 ? "s" : "");
        
        for (module = 0; module < module_list_count; module++) {
            printf(
                "\t%s %s by %s (", module_list[module]->name,
                module_list[module]->version, module_list[module]->author);
            Main_PrintSize(module_list[module]->size);
            puts(").");
        }
        
        Main_PrintSize(module_list_size);
        puts(" total.");
    }
    
    Event_Wait(&apploader_event_complete);
    Event_Wait(&module_event_complete);
    fatUnmount("sd");
    __io_wiisd.shutdown();
    
    if (module_has_error) {
        printf("\nPress RESET to exit.\n");
        return -1;
    }
    return 0;
}

static void Main_PrintSize(size_t size) {
    static const char *suffix[] = { "bytes", "KiB", "MiB", "GiB" };
    unsigned int magnitude, precision;
    float sizef;

    sizef = size;
    magnitude = 0;
    while (sizef > 512) {
        sizef /= 1024.0f;
        magnitude++;
    }
    
    assert(magnitude < 4);
    
    if (magnitude == 0)
        precision = 0;
    else if (sizef >= 100)
        precision = 0;
    else if (sizef >= 10)
        precision = 1;
    else
        precision = 2;
        
    printf("%.*f %s", precision, sizef, suffix[magnitude]);
}