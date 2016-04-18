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

#ifndef LANGLIST_H
#define LANGLIST_H

enum
{
    STR_EMPTY=0,
    STR_EMPTY_H,

// Lang info
    STR_LANG_NAME,
    STR_LANG_ID,
    STR_LANG_GROUP,
    STR_LANG_CODE,
    STR_RTL,

// Left panel
    STR_SHOW_SYSINFO,
    STR_SHOW_SYSINFO_H,

    STR_INSTALL,
    STR_INSTALL_H,
    STR_SELECT_ALL,
    STR_SELECT_ALL_H,
    STR_SELECT_NONE,
    STR_SELECT_NONE_H,

    STR_LANG,
    STR_LANG_H,
    STR_THEME,
    STR_THEME_H,
    STR_EXPERT,
    STR_EXPERT_H,

    STR_OPENLOGS,
    STR_OPENLOGS_H,
    STR_SNAPSHOT,
    STR_SNAPSHOT_H,
    STR_EXTRACT,
    STR_EXTRACT_H,
    STR_DRVDIR,
    STR_DRVDIR_H,
    STR_OPTIONS_BTN,
    STR_OPTIONS_BTN_H,

    STR_SHOW_FOUND,
    STR_SHOW_FOUND_H,
    STR_SHOW_MISSING,
    STR_SHOW_MISSING_H,
    STR_SHOW_NEWER,
    STR_SHOW_NEWER_H,
    STR_SHOW_CURRENT,
    STR_SHOW_CURRENT_H,
    STR_SHOW_OLD,
    STR_SHOW_OLD_H,
    STR_SHOW_BETTER,
    STR_SHOW_BETTER_H,
    STR_SHOW_WORSE_RANK,
    STR_SHOW_WORSE_RANK_H,

    STR_SHOW_NOTFOUND,
    STR_SHOW_NOTFOUND_H,
    STR_SHOW_NF_MISSING,
    STR_SHOW_NF_MISSING_H,
    STR_SHOW_NF_UNKNOWN,
    STR_SHOW_NF_UNKNOWN_H,
    STR_SHOW_NF_STANDARD,
    STR_SHOW_NF_STANDARD_H,

    STR_SHOW_DISPLAY,
    STR_SHOW_DISPLAY_H,
    STR_SHOW_ONE,
    STR_SHOW_ONE_H,
    STR_SHOW_DUP,
    STR_SHOW_DUP_H,
    STR_SHOW_INVALID,
    STR_SHOW_INVALID_H,

    STR_OPTIONS,
    STR_OPTIONS_H,
    STR_REBOOT,
    STR_REBOOT_H,

// Sysinfo
    STR_SYSINF_WINDOWS,
    STR_SYSINF_VERSION,
    STR_SYSINF_PLATFORM,
    STR_SYSINF_UPDATE,
    STR_SYSINF_SERVICEPACK,
    STR_SYSINF_SUITEMASK,
    STR_SYSINF_PRODUCTTYPE,
    STR_SYSINF_ENVIRONMENT,
    STR_SYSINF_WINDIR,
    STR_SYSINF_TEMP,
    STR_SYSINF_MOTHERBOARD,
    STR_SYSINF_PRODUCT,
    STR_SYSINF_MODEL,
    STR_SYSINF_MANUF,
    STR_SYSINF_BATTERY,
    STR_SYSINF_AC_STATUS,
    STR_SYSINF_OFFLINE,
    STR_SYSINF_ONLINE,
    STR_SYSINF_UNKNOWN,
    STR_SYSINF_FLAGS,
    STR_SYSINF_HIGH,
    STR_SYSINF_LOW,
    STR_SYSINF_CRITICAL,
    STR_SYSINF_CHARGING,
    STR_SYSINF_NOBATTERY,
    STR_SYSINF_CHARGED,
    STR_SYSINF_LIFETIME,
    STR_SYSINF_FULLLIFETIME,
    STR_SYSINF_MINS,
    STR_SYSINF_MONITORS,
    STR_SYSINF_CM,
    STR_SYSINF_INCH,
    STR_SYSINF_WIDE,
    STR_SYSINF_MISC,
    STR_SYSINF_TYPE,
    STR_SYSINF_LAPTOP,
    STR_SYSINF_DESKTOP,
    STR_SYSINF_LOCALE,
    STR_SYSINF_CPU_ARCH,
    STR_SYSINF_32BIT,
    STR_SYSINF_64BIT,

// About
    STR_ABOUT_VER,
    STR_ABOUT_DEV_TITLE,
    STR_ABOUT_DEV_LIST,
    STR_ABOUT_TESTERS_TITLE,
    STR_ABOUT_TESTERS_LIST,
    STR_ABOUT_TRANS_TITLE,
    STR_ABOUT_LICENSE,
    //STR_ABOUT_SIZE, // deprecated
    STR_TRANSLATORS,

// Driver popup windows
    STR_HINT_UNKNOWN,
    STR_HINT_ANALYSIS,
    STR_HINT_SIGNATURE,
    STR_HINT_DRP,
    STR_HINT_DEVICE,
    STR_HINT_HARDWAREID,
    STR_HINT_COMPID,
    STR_HINT_INSTDRV,
    STR_HINT_AVAILDRV,
    STR_HINT_AVAILDRVS,
    STR_HINT_MANUF,
    STR_HINT_PROVIDER,
    STR_HINT_DATE,
    STR_HINT_VERSION,
    STR_HINT_ID,
    STR_HINT_INF,
    STR_HINT_SECTION,
    STR_HINT_SCORE,
    STR_HINT_SCROLL,

// Context menu
    STR_CONT_INSTALL,
    STR_CONT_SHOWALT,
    STR_CONT_OPENINF,
    STR_CONT_LOCATEINF,
    STR_CONT_HWID_SEARCH,
    STR_CONT_HWID_CLIP,

// Misc
    STR_OPENSNAPSHOT,
    STR_EXTRACTFOLDER,

// Device status
    STR_STATUS_NOTPRESENT,
    STR_STATUS_DISABLED,
    STR_STATUS_DEVPROBLEM,
    STR_STATUS_DRVPROBLEM,
    STR_STATUS_RUNNING,
    STR_STATUS_STOPPED,

// Driver status
    STR_STATUS_INVALID,
    STR_STATUS_MISSING,
    STR_STATUS_NOTSIGNED,
    STR_STATUS_BETTER_NEW,
    STR_STATUS_SAME_NEW,
    STR_STATUS_WORSE_NEW,
    STR_STATUS_BETTER_CUR,
    STR_STATUS_SAME_CUR,
    STR_STATUS_WORSE_CUR,
    STR_STATUS_BETTER_OLD,
    STR_STATUS_SAME_OLD,
    STR_STATUS_WORSE_OLD,
    STR_STATUS_DUP,
    STR_STATUS_NF_MISSING,
    STR_STATUS_NF_UNKNOWN,
    STR_STATUS_NF_STANDARD,

// Virus
    STR_VIRUS,
    STR_VIRUS_AUTORUN,
    STR_VIRUS_AUTORUN_H,
    STR_VIRUS_RECYCLER,
    STR_VIRUS_RECYCLER_H,
    STR_VIRUS_HIDDEN,
    STR_VIRUS_HIDDEN_H,

// Status
    STR_CLOSE_SNAPSHOT,
    STR_EMPTYDRP,
    STR_CLOSE_DRPEXT,
    STR_NOUPDATES,
    STR_INITIALIZING,

// Progress
    STR_INST_EXTRACT,
    STR_INST_INSTALL,
    STR_INST_OK,
    STR_INST_REBOOT,
    STR_INST_FAILED,

    STR_INST_INSTALLING,
    STR_INST_COMPLITED,
    STR_INST_COMPLITED_RB,
    STR_INST_CLOSE,

    STR_EXTR_EXTRACTING,
    STR_EXTR_OK,
    STR_EXTR_FAILED,

    STR_INST_STOPPING,
    STR_INDEXING,
    STR_INDEXLZMA,
    STR_OF,

    STR_RESTOREPOINT,
    STR_RESTOREPOINT_H,
    STR_REST_SCHEDULE,
    STR_REST_ROLLBACK,
    STR_REST_CREATING,
    STR_REST_CREATED,
    STR_REST_FAILED,

    STR_INST_QUIT_TITLE,
    STR_INST_QUIT_MSG,
    STR_HINT_STOPINST,
    STR_HINT_STOPEXTR,
    STR_HINT_DRIVER,

    STR_SYS_WINVER,
    STR_SYS_32,
    STR_SYS_64,
    STR_SYS_DEVICEMNG,
    STR_SYS_DISINSTALL,
    STR_SYS_DISRESTPNT,

// Update
    STR_UPD_DIALOG_TITLE,
    STR_UPD_DIALOG_MSG,
    STR_UPD_DIALOG_INDEX,
    STR_UPD_TITLE,
    STR_UPD_BTN_ALL,
    STR_UPD_BTN_NONE,
    STR_UPD_BTN_THISPC,
    STR_UPD_BTN_THISPC_H,
    STR_UPD_ONLYUPDATES,
    STR_UPD_TOTALSIZE,
    STR_UPD_BTN_OK,
    STR_UPD_BTN_CANCEL,
    STR_UPD_BTN_ACCEPT,
    STR_UPD_COL_NAME,
    STR_UPD_COL_SIZE,
    STR_UPD_COL_PER,
    STR_UPD_COL_NEW,
    STR_UPD_COL_CUR,
    STR_UPD_COL_THISPC,
    STR_UPD_WEBSTATUS,
    STR_UPD_YES,
    STR_UPD_NO,
    STR_UPD_UNKNOWN,
    STR_UPD_MISSING,
    STR_UPD_BYTES,
    STR_UPD_KB,
    STR_UPD_MB,
    STR_UPD_GB,
    STR_UPD_SEC,
    STR_UPD_TSEC,
    STR_UPD_TMIN,
    STR_UPD_THOUR,
    STR_UPD_TDAY,
    STR_UPD_BASEFILES,
    STR_UPD_APP,
    STR_UPD_INDEXES,
    STR_UPD_UPDATEHINT1,
    STR_UPD_UPDATEHINT2,

// Update hint
    STR_UPD_AVAIL1,
    STR_UPD_AVAIL2,
    STR_UPD_AVAIL3,
    STR_UPD_START,
    STR_UPD_PROGRES,
    STR_UPD_MODIFY,

    STR_DWN_DOWNLOADED,
    STR_DWN_DOWNLOADED_F,
    STR_DWN_UPLOADED,
    STR_DWN_ELAPSED,
    STR_DWN_REMAINING,

    STR_DWN_STATUS,
    STR_DWN_ERROR,
    STR_DWN_DOWNLOADSPEED,
    STR_DWN_UPLOADSPEED,

    STR_DWN_SEEDS_F,
    STR_DWN_SEEDS,
    STR_DWN_PEERS,
    STR_DWN_WASTED,
    STR_DWN_WASTED_F,

    STR_DWN_ERRSES,
    STR_DWN_ERRTOR,

    STR_TR_ST0,
    STR_TR_ST1,
    STR_TR_ST2,
    STR_TR_ST3,
    STR_TR_ST4,
    STR_TR_ST5,
    STR_TR_ST6,
    STR_TR_ST7,

// Options dialog
    STR_OPTION_TITLE,
    STR_OPTION_VIEW_TAB,
    STR_OPTION_UPDATES_TAB,
    STR_OPTION_OK_BUTTON,
    STR_OPTION_CANCEL_BUTTON,

// View tab
    STR_OPTION_DRPNAMES,
    STR_OPTION_HIDE_NAMES,
    STR_OPTION_SHOW_RIGHT,
    STR_OPTION_SHOW_ABOVE,
    STR_OPTION_SCALLING,
    STR_OPTION_CONSOLE,

// Update tab
    STR_OPTION_CHECKUPDATES,
    STR_OPTION_ONLYUPDATES,
    STR_OPTION_TORRENT,
    STR_OPTION_PORT,
    STR_OPTION_MAX_DOWNLOAD,
    STR_OPTION_MAX_UPLOAD,

    STR_NM
};

#endif
