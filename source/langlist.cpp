/*
This file is part of Snappy Driver Installer.

Snappy Driver Installer is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Snappy Driver Installer is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Snappy Driver Installer.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "com_header.h"
#include <stddef.h>
#include "theme.h"

#include <windows.h>


entry_t language[STR_NM]=
{
    DEF_STR("STR_EMPTY")
    DEF_STR("STR_EMPTY_H")

// Lang info
    DEF_STR("STR_LANG_NAME")
    DEF_VAL("STR_LANG_ID")
    DEF_VAL("STR_LANG_CODE")
    DEF_VAL("STR_RTL")

// Left panel
    DEF_STR("STR_SHOW_SYSINFO")
    DEF_STR("STR_SHOW_SYSINFO_H")

    DEF_STR("STR_INSTALL")
    DEF_STR("STR_INSTALL_H")
    DEF_STR("STR_SELECT_ALL")
    DEF_STR("STR_SELECT_ALL_H")
    DEF_STR("STR_SELECT_NONE")
    DEF_STR("STR_SELECT_NONE_H")

    DEF_STR("STR_LANG")
    DEF_STR("STR_LANG_H")
    DEF_STR("STR_THEME")
    DEF_STR("STR_THEME_H")
    DEF_STR("STR_EXPERT")
    DEF_STR("STR_EXPERT_H")

    DEF_STR("STR_OPENLOGS")
    DEF_STR("STR_OPENLOGS_H")
    DEF_STR("STR_SNAPSHOT")
    DEF_STR("STR_SNAPSHOT_H")
    DEF_STR("STR_EXTRACT")
    DEF_STR("STR_EXTRACT_H")
    DEF_STR("STR_DRVDIR")
    DEF_STR("STR_DRVDIR_H")

    DEF_STR("STR_SHOW_FOUND")
    DEF_STR("STR_SHOW_FOUND_H")
    DEF_STR("STR_SHOW_MISSING")
    DEF_STR("STR_SHOW_MISSING_H")
    DEF_STR("STR_SHOW_NEWER")
    DEF_STR("STR_SHOW_NEWER_H")
    DEF_STR("STR_SHOW_CURRENT")
    DEF_STR("STR_SHOW_CURRENT_H")
    DEF_STR("STR_SHOW_OLD")
    DEF_STR("STR_SHOW_OLD_H")
    DEF_STR("STR_SHOW_BETTER")
    DEF_STR("STR_SHOW_BETTER_H")
    DEF_STR("STR_SHOW_WORSE_RANK")
    DEF_STR("STR_SHOW_WORSE_RANK_H")

    DEF_STR("STR_SHOW_NOTFOUND")
    DEF_STR("STR_SHOW_NOTFOUND_H")
    DEF_STR("STR_SHOW_NF_MISSING")
    DEF_STR("STR_SHOW_NF_MISSING_H")
    DEF_STR("STR_SHOW_NF_UNKNOWN")
    DEF_STR("STR_SHOW_NF_UNKNOWN_H")
    DEF_STR("STR_SHOW_NF_STANDARD")
    DEF_STR("STR_SHOW_NF_STANDARD_H")

    DEF_STR("STR_SHOW_DISPLAY")
    DEF_STR("STR_SHOW_DISPLAY_H")
    DEF_STR("STR_SHOW_ONE")
    DEF_STR("STR_SHOW_ONE_H")
    DEF_STR("STR_SHOW_DUP")
    DEF_STR("STR_SHOW_DUP_H")
    DEF_STR("STR_SHOW_INVALID")
    DEF_STR("STR_SHOW_INVALID_H")

    DEF_STR("STR_OPTIONS")
    DEF_STR("STR_OPTIONS_H")
    DEF_STR("STR_REBOOT")
    DEF_STR("STR_REBOOT_H")

// Sysinfo
    DEF_STR("STR_SYSINF_WINDOWS")
    DEF_STR("STR_SYSINF_VERSION")
    DEF_STR("STR_SYSINF_PLATFORM")
    DEF_STR("STR_SYSINF_UPDATE")
    DEF_STR("STR_SYSINF_SERVICEPACK")
    DEF_STR("STR_SYSINF_SUITEMASK")
    DEF_STR("STR_SYSINF_PRODUCTTYPE")
    DEF_STR("STR_SYSINF_ENVIRONMENT")
    DEF_STR("STR_SYSINF_WINDIR")
    DEF_STR("STR_SYSINF_TEMP")
    DEF_STR("STR_SYSINF_MOTHERBOARD")
    DEF_STR("STR_SYSINF_PRODUCT")
    DEF_STR("STR_SYSINF_MODEL")
    DEF_STR("STR_SYSINF_MANUF")
    DEF_STR("STR_SYSINF_BATTERY")
    DEF_STR("STR_SYSINF_AC_STATUS")
    DEF_STR("STR_SYSINF_OFFLINE")
    DEF_STR("STR_SYSINF_ONLINE")
    DEF_STR("STR_SYSINF_UNKNOWN")
    DEF_STR("STR_SYSINF_FLAGS")
    DEF_STR("STR_SYSINF_HIGH")
    DEF_STR("STR_SYSINF_LOW")
    DEF_STR("STR_SYSINF_CRITICAL")
    DEF_STR("STR_SYSINF_CHARGING")
    DEF_STR("STR_SYSINF_NOBATTERY")
    DEF_STR("STR_SYSINF_CHARGED")
    DEF_STR("STR_SYSINF_LIFETIME")
    DEF_STR("STR_SYSINF_FULLLIFETIME")
    DEF_STR("STR_SYSINF_MINS")
    DEF_STR("STR_SYSINF_MONITORS")
    DEF_STR("STR_SYSINF_CM")
    DEF_STR("STR_SYSINF_INCH")
    DEF_STR("STR_SYSINF_WIDE")
    DEF_STR("STR_SYSINF_MISC")
    DEF_STR("STR_SYSINF_TYPE")
    DEF_STR("STR_SYSINF_LAPTOP")
    DEF_STR("STR_SYSINF_DESKTOP")
    DEF_STR("STR_SYSINF_LOCALE")
    DEF_STR("STR_SYSINF_CPU_ARCH")
    DEF_STR("STR_SYSINF_32BIT")
    DEF_STR("STR_SYSINF_64BIT")

// About
    DEF_STR("STR_ABOUT_VER")
    DEF_STR("STR_ABOUT_DEV_TITLE")
    DEF_STR("STR_ABOUT_DEV_LIST")
    DEF_STR("STR_ABOUT_TESTERS_TITLE")
    DEF_STR("STR_ABOUT_TESTERS_LIST")
    DEF_STR("STR_ABOUT_LICENSE")
    DEF_STR("STR_ABOUT_SIZE") // deprecated

// Driver popup windows
    DEF_STR("STR_HINT_UNKNOWN")
    DEF_STR("STR_HINT_ANALYSIS")
    DEF_STR("STR_HINT_SIGNATURE")
    DEF_STR("STR_HINT_DRP")
    DEF_STR("STR_HINT_DEVICE")
    DEF_STR("STR_HINT_HARDWAREID")
    DEF_STR("STR_HINT_COMPID")
    DEF_STR("STR_HINT_INSTDRV")
    DEF_STR("STR_HINT_AVAILDRV")
    DEF_STR("STR_HINT_AVAILDRVS")
    DEF_STR("STR_HINT_MANUF")
    DEF_STR("STR_HINT_PROVIDER")
    DEF_STR("STR_HINT_DATE")
    DEF_STR("STR_HINT_VERSION")
    DEF_STR("STR_HINT_ID")
    DEF_STR("STR_HINT_INF")
    DEF_STR("STR_HINT_SECTION")
    DEF_STR("STR_HINT_SCORE")
    DEF_STR("STR_HINT_SCROLL")

// Context menu
    DEF_STR("STR_CONT_INSTALL")
    DEF_STR("STR_CONT_SHOWALT")
    DEF_STR("STR_CONT_OPENINF")
    DEF_STR("STR_CONT_LOCATEINF")
    DEF_STR("STR_CONT_HWID_SEARCH")
    DEF_STR("STR_CONT_HWID_CLIP")

// Misc
    DEF_STR("STR_OPENSNAPSHOT")
    DEF_STR("STR_EXTRACTFOLDER")

// Device status
    DEF_STR("STR_STATUS_NOTPRESENT")
    DEF_STR("STR_STATUS_DISABLED")
    DEF_STR("STR_STATUS_DEVPROBLEM")
    DEF_STR("STR_STATUS_DRVPROBLEM")
    DEF_STR("STR_STATUS_RUNNING")
    DEF_STR("STR_STATUS_STOPPED")

// Driver status
    DEF_STR("STR_STATUS_INVALID")
    DEF_STR("STR_STATUS_MISSING")
    DEF_STR("STR_STATUS_NOTSIGNED")
    DEF_STR("STR_STATUS_BETTER_NEW")
    DEF_STR("STR_STATUS_SAME_NEW")
    DEF_STR("STR_STATUS_WORSE_NEW")
    DEF_STR("STR_STATUS_BETTER_CUR")
    DEF_STR("STR_STATUS_SAME_CUR")
    DEF_STR("STR_STATUS_WORSE_CUR")
    DEF_STR("STR_STATUS_BETTER_OLD")
    DEF_STR("STR_STATUS_SAME_OLD")
    DEF_STR("STR_STATUS_WORSE_OLD")
    DEF_STR("STR_STATUS_DUP")
    DEF_STR("STR_STATUS_NF_MISSING")
    DEF_STR("STR_STATUS_NF_UNKNOWN")
    DEF_STR("STR_STATUS_NF_STANDARD")

// Virus
    DEF_STR("STR_VIRUS")
    DEF_STR("STR_VIRUS_AUTORUN")
    DEF_STR("STR_VIRUS_AUTORUN_H")
    DEF_STR("STR_VIRUS_RECYCLER")
    DEF_STR("STR_VIRUS_RECYCLER_H")
    DEF_STR("STR_VIRUS_HIDDEN")
    DEF_STR("STR_VIRUS_HIDDEN_H")

// Status
    DEF_STR("STR_CLOSE_SNAPSHOT")
    DEF_STR("STR_EMPTYDRP")
    DEF_STR("STR_CLOSE_DRPEXT")
    DEF_STR("STR_NOUPDATES")
    DEF_STR("STR_INITIALIZING")

// Progress
    DEF_STR("STR_INST_EXTRACT")
    DEF_STR("STR_INST_INSTALL")
    DEF_STR("STR_INST_OK")
    DEF_STR("STR_INST_REBOOT")
    DEF_STR("STR_INST_FAILED")

    DEF_STR("STR_INST_INSTALLING")
    DEF_STR("STR_INST_COMPLITED")
    DEF_STR("STR_INST_COMPLITED_RB")
    DEF_STR("STR_INST_CLOSE")

    DEF_STR("STR_EXTR_EXTRACTING")
    DEF_STR("STR_EXTR_OK")
    DEF_STR("STR_EXTR_FAILED")

    DEF_STR("STR_INST_STOPPING")
    DEF_STR("STR_INDEXING")
    DEF_STR("STR_INDEXLZMA")
    DEF_STR("STR_OF")

    DEF_STR("STR_RESTOREPOINT")
    DEF_STR("STR_RESTOREPOINT_H")
    DEF_STR("STR_REST_SCHEDULE")
    DEF_STR("STR_REST_ROLLBACK")
    DEF_STR("STR_REST_CREATING")
    DEF_STR("STR_REST_CREATED")
    DEF_STR("STR_REST_FAILED")

    DEF_STR("STR_INST_QUIT_TITLE")
    DEF_STR("STR_INST_QUIT_MSG")
    DEF_STR("STR_HINT_STOPINST")
    DEF_STR("STR_HINT_STOPEXTR")
    DEF_STR("STR_HINT_DRIVER")

    DEF_STR("STR_SYS_WINVER")
    DEF_STR("STR_SYS_32")
    DEF_STR("STR_SYS_64")
    DEF_STR("STR_SYS_DEVICEMNG")
    DEF_STR("STR_SYS_DISINSTALL")
    DEF_STR("STR_SYS_DISRESTPNT")

// Update
    DEF_STR("STR_UPD_DIALOG_TITLE")
    DEF_STR("STR_UPD_DIALOG_MSG")
    DEF_STR("STR_UPD_DIALOG_INDEX")
    DEF_STR("STR_UPD_TITLE")
    DEF_STR("STR_UPD_BTN_ALL")
    DEF_STR("STR_UPD_BTN_NONE")
    DEF_STR("STR_UPD_BTN_THISPC")
    DEF_STR("STR_UPD_BTN_THISPC_H")
    DEF_STR("STR_UPD_ONLYUPDATES")
    DEF_STR("STR_UPD_TOTALSIZE")
    DEF_STR("STR_UPD_BTN_OK")
    DEF_STR("STR_UPD_BTN_CANCEL")
    DEF_STR("STR_UPD_BTN_ACCEPT")
    DEF_STR("STR_UPD_COL_NAME")
    DEF_STR("STR_UPD_COL_SIZE")
    DEF_STR("STR_UPD_COL_PER")
    DEF_STR("STR_UPD_COL_NEW")
    DEF_STR("STR_UPD_COL_CUR")
    DEF_STR("STR_UPD_COL_THISPC")
    DEF_STR("STR_UPD_WEBSTATUS")
    DEF_STR("STR_UPD_YES")
    DEF_STR("STR_UPD_NO")
    DEF_STR("STR_UPD_UNKNOWN")
    DEF_STR("STR_UPD_MISSING")
    DEF_STR("STR_UPD_BYTES")
    DEF_STR("STR_UPD_KB")
    DEF_STR("STR_UPD_MB")
    DEF_STR("STR_UPD_GB")
    DEF_STR("STR_UPD_SEC")
    DEF_STR("STR_UPD_TSEC")
    DEF_STR("STR_UPD_TMIN")
    DEF_STR("STR_UPD_THOUR")
    DEF_STR("STR_UPD_TDAY")
    DEF_STR("STR_UPD_BASEFILES")
    DEF_STR("STR_UPD_APP")
    DEF_STR("STR_UPD_INDEXES")
    DEF_STR("STR_UPD_UPDATEHINT1")
    DEF_STR("STR_UPD_UPDATEHINT2")

// Update hint
    DEF_STR("STR_UPD_AVAIL1")
    DEF_STR("STR_UPD_AVAIL2")
    DEF_STR("STR_UPD_AVAIL3")
    DEF_STR("STR_UPD_START")
    DEF_STR("STR_UPD_PROGRES")
    DEF_STR("STR_UPD_MODIFY")

    DEF_STR("STR_DWN_DOWNLOADED")
    DEF_STR("STR_DWN_DOWNLOADED_F")
    DEF_STR("STR_DWN_UPLOADED")
    DEF_STR("STR_DWN_ELAPSED")
    DEF_STR("STR_DWN_REMAINING")

    DEF_STR("STR_DWN_STATUS")
    DEF_STR("STR_DWN_ERROR")
    DEF_STR("STR_DWN_DOWNLOADSPEED")
    DEF_STR("STR_DWN_UPLOADSPEED")

    DEF_STR("STR_DWN_SEEDS_F")
    DEF_STR("STR_DWN_SEEDS")
    DEF_STR("STR_DWN_PEERS")
    DEF_STR("STR_DWN_WASTED")
    DEF_STR("STR_DWN_WASTED_F")

    DEF_STR("STR_DWN_ERRSES")
    DEF_STR("STR_DWN_ERRTOR")

    DEF_STR("STR_TR_ST0")
    DEF_STR("STR_TR_ST1")
    DEF_STR("STR_TR_ST2")
    DEF_STR("STR_TR_ST3")
    DEF_STR("STR_TR_ST4")
    DEF_STR("STR_TR_ST5")
    DEF_STR("STR_TR_ST6")
    DEF_STR("STR_TR_ST7")
};
