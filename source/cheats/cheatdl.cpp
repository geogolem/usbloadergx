/***************************************************************************
 * Copyright (C) 2020
 * by oddx
 ***************************************************************************/
#include <string.h>
#include "usbloader/disc.h"
#include "settings/CSettings.h"
#include "language/gettext.h"
#include "network/networkops.h"
#include "network/http.h"
#include "prompts/PromptWindows.h"
#include "FileOperations/fileops.h"
#include "prompts/ProgressWindow.h"
#include "cheats/cheatdl.h"
#include "Channels/channels.h"
#include "usbloader/GameList.h"
#include "GameCube/GCGames.h"

void GetMissingCheatCodes()
{
    if (!CreateSubfolder(Settings.TxtCheatcodespath))
	{
		WindowPrompt(tr( "Error !" ), tr( "Can't create directory" ), tr( "OK" ));
		return;
	}

    int dlcount = 0;
	if (!IsNetworkInit()) Initialize_Network();

	if (IsNetworkInit())
	{
        ProgressCancelEnable(true);
        StartProgress(tr("Downloading Cheat Codes..."), tr("Please wait"), 0, false, false);
        ShowProgress(0, 1);

        vector<struct discHdr> fulllist;
        vector<struct discHdr> & WiiList = gameList.GetFullGameList();
        vector<struct discHdr> & GCList = GCGames::Instance()->GetHeaders();
        vector<struct discHdr> & NANDList = Channels::Instance()->GetNandHeaders();
        vector<struct discHdr> & EmuList = Channels::Instance()->GetEmuHeaders();
        fulllist.reserve(WiiList.size() + GCList.size() + NANDList.size() + EmuList.size());
        fulllist.insert(fulllist.end(), WiiList.begin(), WiiList.end());
        fulllist.insert(fulllist.end(), GCList.begin(), GCList.end());
        fulllist.insert(fulllist.end(), NANDList.begin(), NANDList.end());
        fulllist.insert(fulllist.end(), EmuList.begin(), EmuList.end());

        u32 fileCount = fulllist.size();
        for (u32 i = 0; i < fileCount; ++i)
        {
            if(ProgressCanceled()) {
				break;
            }

            struct discHdr *header = &fulllist[i];

            char txtpath[250];
            snprintf(txtpath, sizeof(txtpath), "%s%s.txt", Settings.TxtCheatcodespath, header->id);

            char txtstatus[25];
            snprintf(txtstatus, sizeof(txtstatus), "Downloading...%d/%d", (int)i, (int)fileCount);

            ShowProgress(txtstatus, (char*)header->id, 0, i, fileCount, false, false);

            if(CheckFile(txtpath)) continue;

            char codeurl[250];
            snprintf(codeurl, sizeof(codeurl), "http://web.archive.org/web/1000id_/geckocodes.org/txt.php?txt=%s", header->id);

            struct block file = downloadfile(codeurl);

            if (file.data != NULL)
            {
                if (strncmp((char*)file.data, (char*)header->id,4) == 0)
                {
                    FILE * pfile = fopen(txtpath, "wb");
                    if(pfile)
                    {
                        fwrite(file.data, 1, file.size, pfile);
                        fclose(pfile);
                        dlcount++;
                    }
                }

            }
            free(file.data);
        }

    }

    char dlcounttxt[5];
    snprintf(dlcounttxt, sizeof(dlcounttxt), "%d", dlcount);
    WindowPrompt(tr( "Cheat Code Files Downloaded:" ), dlcounttxt, tr( "OK" ));

	ProgressStop();
	ProgressCancelEnable(false);
}
