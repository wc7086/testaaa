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

#include <shobjidl.h>       // for ShowProgressInTaskbar()
int getbaseboard(wchar_t *manuf,wchar_t *model,wchar_t *product,wchar_t *cs_manuf,wchar_t *cs_model,int *type);
void ShowProgressInTaskbar(HWND hwnd,TBPFLAG flags,long long complited,long long total);
