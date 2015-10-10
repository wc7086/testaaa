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

#ifndef DRAW_H
#define DRAW_H

#include "themelist.h"

// Declarations
class Image;
class Panel;
class Panelitem;
class ClipRegionImp;
class WidgetVisitor;
class WidgetComposite;

// Global vars
extern int rtl;
extern Image box[BOX_NUM];
extern Image icon[ICON_NUM];
extern WidgetComposite *wPanels;

//{ Image
class Image
{
    HBITMAP bitmap;
    HGDIOBJ oldbitmap;
    HDC ldc;
    int sx,sy,hasalpha;
    int iscopy;

private:
    void loadFromFile(wchar_t *filename);
    void loadFromRes(int id);
    void createBitmap(BYTE *data,int sz);

public:
    enum align
    {
        RIGHT   = 1,
        BOTTOM  = 2,
        HCENTER = 4,
        VCENTER = 8,
    };
    enum fillmode
    {
        HTILE   =  1,
        VTILE   =  2,
        HSTR    =  4,
        VSTR    =  8,
        ASPECT  = 16,
    };

    Image():bitmap(nullptr),oldbitmap(nullptr),ldc(nullptr),sx(0),sy(0),hasalpha(0),iscopy(0){}
    void release();
    void makecopy(Image &t);
    void load(int i);
    bool isLoaded()const{return ldc;}
    void draw(HDC dc,int x1,int y1,int x2,int y2,int anchor,int fill);
};
//}

//{ ClipRegion
class ClipRegion
{
    ClipRegion(const ClipRegion&)=delete;
    void operator=(const ClipRegion&)=delete;

private:
    ClipRegionImp *imp;

public:
    ClipRegion();
    ClipRegion(int x1,int y1,int x2,int y2);
    ClipRegion(int x1,int y1,int x2,int y2,int r);
    void setRegion(int x1,int y1,int x2,int y2);
    ~ClipRegion();

    friend class Canvas;
};
//}

//{ Font
class Font
{
    Font(const Font&)=delete;
    void operator=(const Font&)=delete;

private:
    HFONT hFont;

public:
    Font():hFont(nullptr){}
    ~Font();
    void SetFont(const wchar_t *name,int size,int bold=false);
    HFONT get(){return hFont;}

    friend class Canvas;
};
//}

//{ Canvas
class Canvas
{
    Canvas(const Canvas &)=delete;
    Canvas &operator=(const Canvas &)=delete;

    int x,y;
    HDC localDC;
    HDC hdcMem;
    HBITMAP bitmap,oldbitmap;
    PAINTSTRUCT ps;
    HWND hwnd;
    HRGN clipping;

public:
    Canvas();
    ~Canvas();

    void CopyCanvas(Canvas *source,int x1,int y1);
    void begin(HWND hwnd,int x,int y);
    void end();

    void SetClipRegion(ClipRegion &clip);
    void ClearClipRegion();

    void DrawEmptyRect(int x1,int y1,int x2,int y2,int color);
    void DrawFilledRect(int x1,int y1,int x2,int y2,int color1,int color2,int w,int r);
    void DrawWidget(int x1,int y1,int x2,int y2,int i);
    void DrawImage(Image &image,int x1,int y1,int wx,int wy,int flags1,int flags2);
    void DrawLine(int x1,int y1,int x2,int y2);
    void DrawCheckbox(int x,int y,int wx,int wy,int checked,int active);
    void DrawConnection(int x,int pos,int ofsy,int curpos);
    void DrawIcon(int x1,int y1,const char *guid_driverpack,const GUID *guid_device);

    void SetTextColor(int color);
    void SetFont(Font *font);
    void DrawTextXY(int x,int y,const wchar_t *buf);
    void DrawTextRect(const wchar_t *bufw,RECT *rect);
    void CalcBoundingBox(const wchar_t *str,RECT *rect);
    int  GetTextExtent(const wchar_t *str);
};
//}

//{ ### Command ###
class Command
{
public:
    virtual ~Command(){}
    virtual void LeftClick(bool=false){}
    virtual void RightClick(int,int){}

    virtual void UpdateCheckbox(bool *){}
    virtual int  GetBitfieldState(){return 0;}
    virtual int  GetActionID(){return -1;}
};

// Checkboxes
class FiltersCommand:public Command
{
public:
    int action_id;

public:
    FiltersCommand(int a):action_id(a){}
    void UpdateCheckbox(bool *checked){*checked=(Settings.filters&(1<<action_id))?true:false;}
    int  GetBitfieldState(){return 1<<action_id;}
    int  GetActionID(){return action_id;}
};

class ExpertmodeCheckboxCommand:public Command
{
public:
    void UpdateCheckbox(bool *checked){*checked=Settings.expertmode;}
    void LeftClick(bool);
    int  GetActionID(){return ID_EXPERT_MODE;}
};

class RestPointCheckboxCommand:public Command
{
public:
    void LeftClick(bool);
    void RightClick(int x,int y);
    int  GetActionID(){return ID_RESTPNT;}
};

class RebootCheckboxCommand:public Command
{
public:
    void LeftClick(bool);
    int  GetActionID(){return ID_REBOOT;}
};

// Misc
class AboutCommand:public Command
{
public:
    void LeftClick(bool=false);
};

class SysInfoCommand:public Command
{
public:
    void LeftClick(bool=false);
    void RightClick(bool=false);
};

// Buttons
class OpenLogsCommand:public Command
{
public:
    void LeftClick(bool=false);
};

class SnapshotCommand:public Command
{
public:
    void LeftClick(bool=false);
};

class ExtractCommand:public Command
{
public:
    void LeftClick(bool=false);
};

class DrvDirCommand:public Command
{
public:
    void LeftClick(bool=false);
};

class InstallCommand:public Command
{
public:
    void LeftClick(bool=false);
};

class SelectAllCommand:public Command
{
public:
    void LeftClick(bool=false);
};

class SelectNoneCommand:public Command
{
public:
    void LeftClick(bool=false);
};
//}

//{ ### Widget ###
/*
    Widget
    ├───wLang
    │   └───wTheme
    ├───wCheckbox
    ├───wButton
    │   └───wButtonInst
    ├───wText
    │   ├───wTextSys1
    │   │   ├───wTextSys2
    │   │   └───wTextSys3
    │   └────TextRev
    └───WidgetComposite
        └───wPanel
            └───wLogo
*/

class Widget
{
protected:
    int x1,y1,wx,wy;

public:
    Command *command=nullptr;
    Widget *parent=nullptr;
    bool isSelected=false;
    int str_id;
    int flags=0;

public:
    Widget(int str_id_):str_id(str_id_){}
    virtual ~Widget(){delete command;}
    virtual void draw(Canvas &){}
    virtual void arrange(){}

    void setboundbox(int v1,int v2,int v3,int v4){x1=v1;y1=v2;wx=v3;wy=v4;}
    void hitscan(int x,int y);
    void invalidate();

    virtual void Accept(WidgetVisitor &);
};

// WidgetComposite
class WidgetComposite:public Widget
{
protected:
    int num=0;
    Widget *widgets[20];

public:
    virtual void Add(Widget *w)
    {
        widgets[num]=w;
        widgets[num]->parent=this;
        num++;
    }
    void Accept(WidgetVisitor &);
    WidgetComposite():Widget(0){}
    ~WidgetComposite()
    {
        for(int i=0;i<num;i++)delete widgets[i];
    }
    void draw(Canvas &canvas)
    {
        for(int i=0;i<num;i++)widgets[i]->draw(canvas);
    }
    void arrange()
    {
        for(int i=0;i<num;i++)widgets[i]->arrange();
    }
};

// wPanel
class wPanel:public WidgetComposite
{
    int sz,indofs,index;
    bool isAdvanced;

public:
    wPanel(int sz_,int ofs,bool isAdv=false):sz(sz_),indofs((ofs+1)*18),index(ofs),isAdvanced(isAdv){}
    void Accept(WidgetVisitor &);
    void arrange();
    void draw(Canvas &canvas);
};

// wText
class wText:public Widget
{
public:
    void Accept(WidgetVisitor &visitor);
    void draw(Canvas &canvas);
    wText(int str_id_):Widget(str_id_){}
};

// wLogo
class wLogo:public wPanel
{
public:
    void Accept(WidgetVisitor &visitor);
    wLogo(int sz_,int ofs):wPanel{sz_,ofs}{}
};

// wLang
class wLang:public Widget
{
public:
    void arrange();
    wLang():Widget(0){}
};

// wLang
class wTheme:public wLang
{
public:
    void arrange();
    wTheme():wLang(){}
};

// wTextRev
class wTextRev:public wText
{
public:
    void Accept(WidgetVisitor &visitor);
    void draw(Canvas &canvas);
    wTextRev():wText(0){}
};

// wTextSys1
class wTextSys1:public wText
{
public:
    void Accept(WidgetVisitor &visitor);
    void draw(Canvas &canvas);
    wTextSys1():wText(0){}
};

// wTextSys2
class wTextSys2:public wTextSys1
{
public:
    void draw(Canvas &canvas);
};

// wTextSys3
class wTextSys3:public wTextSys1
{
public:
    void draw(Canvas &canvas);
};

// wCheckbox
class wCheckbox:public Widget
{
public:
    bool checked=false;

public:
    void draw(Canvas &canvas);
    void Accept(WidgetVisitor &visitor);
    wCheckbox(int str_id_,Command *c):Widget(str_id_){command=c;}
};

// wButton
class wButton:public Widget
{
public:
    void Accept(WidgetVisitor &visitor);
    void draw(Canvas &canvas);
    wButton(int str_id_,Command *c):Widget(str_id_){command=c;}
};

// wButtonInst
class wButtonInst:public wButton
{
public:
    void draw(Canvas &canvas);
    wButtonInst(int str_id_,Command *c):wButton(str_id_,c){}
};
//}

//{ ### Visiters ###
class WidgetVisitor
{
public:
    virtual ~WidgetVisitor(){}

    virtual void VisitWidget(Widget *){}
    virtual void VisitWidgetComposite(WidgetComposite *a){VisitWidget(a);}
    virtual void VisitwText(wText *a){VisitWidget(a);}
    virtual void VisitwCheckbox(wCheckbox *a){VisitWidget(a);}
    virtual void VisitwButton(wButton *a){VisitWidget(a);}
    virtual void VisitwLogo(wLogo *a){VisitWidget(a);}
    virtual void VisitwTextRev(wTextRev *a){VisitwText(a);}
    virtual void VisitwTextSys1(wTextSys1 *a){VisitwText(a);}
};

class HoverVisiter:public WidgetVisitor
{
    int x,y;
    bool popup_active=false;

public:
    HoverVisiter(int xv,int yv):x(xv),y(yv){}
    ~HoverVisiter();

    void VisitWidget(Widget *);
    void VisitWidgetComposite(WidgetComposite *);
    void VisitwText(wText *);
    void VisitwLogo(wLogo *);
    void VisitwTextRev(wTextRev *);
    void VisitwTextSys1(wTextSys1 *);
};

enum class CHECKBOX
{
    SET,
    CLEAR,
    TOGGLE,
    GET,
};

class ClickVisiter:public WidgetVisitor
{
    int x,y;
    int action_id;
    int sum=0;

    CHECKBOX act;
    int value=0;
    bool right;

public:
    ClickVisiter(int xv,int yv,int rightv=false):x(xv),y(yv),action_id(0),act(CHECKBOX::TOGGLE),right(rightv){}
    ClickVisiter(int id,CHECKBOX c=CHECKBOX::TOGGLE):x(0),y(0),action_id(id),act(c),right(0){}
    ~ClickVisiter();
    int GetValue(){return value;}

    void VisitwCheckbox(wCheckbox *);
    void VisitwButton(wButton *);
    void VisitwLogo(wLogo *);
    void VisitwTextRev(wTextRev *);
    void VisitwTextSys1(wTextSys1 *);
};
//}

//{ ### Text ###
class textdata_t
{
protected:
    Canvas *pcanvas;

    int ofsx;
    int wy;
    int maxsz;

public:
    int col;
    int x;
    int y;

protected:
    void TextOut_CM(int x,int y,const wchar_t *str,int color,int *maxsz,int mode);

public:
    textdata_t(Canvas &canvas,int ofsx=0);

    void TextOutF(int col,const wchar_t *format,...);
    void TextOutF(const wchar_t *format,...);
    void ret();
    void nl();
    void ret_ofs(int a);
    int getX(){return x;}
    int getY(){return y;}
};

class textdata_horiz_t:public textdata_t
{
    int i;
    int *limits;
    int mode;

public:
    textdata_horiz_t(Canvas &canvas,int ofsx1,int *lim,int mode1):textdata_t(canvas,ofsx1),i(0),limits(lim),mode(mode1){}
    void limitskip();
    void TextOutP(const wchar_t *format,...);
};

class textdata_vert:public textdata_t
{

public:
    textdata_vert(Canvas &canvas,int ofsx1=0):textdata_t(canvas,ofsx1)
    {

    }
    void shift_r();
    void shift_l();
    int getMaxsz(){return maxsz;}
    void TextOutSF(const wchar_t *str,const wchar_t *format,...);
};
//}

// Popup
void popup_resize(int x,int y);
void popup_about(Canvas &canvas);
void format_size(wchar_t *buf,long long val,int isspeed);
void format_time(wchar_t *buf,long long val);

// Misc functions
int mirw(int x,int ofs,int w);

int Xm(int x,int o);
int Ym(int y);
int XM(int x,int o);
int YM(int y,int o);

int Xg(int x,int o);
int Yg(int y);
int XG(int x,int o);
int YG(int y,int o);

void drawpopup(int itembar,int type,int x,int y,HWND hwnd);
HICON CreateMirroredIcon(HICON hiconOrg);
void ShowProgressInTaskbar(HWND hwnd,bool show,long long complited=0,long long total=0);
void loadGUID(GUID *g,const char *s);
void drawnew(Canvas &canvas);
bool isRebootDesired();

//{ Combobox
class Combobox
{
    HWND handle;

public:
    /*Combobox(HWND hwnd,int id)
    {
        handle=CreateWindowMF(WC_COMBOBOX,L"",hwnd,(HMENU)id,CBS_DROPDOWNLIST|CBS_HASSTRINGS|WS_OVERLAPPED|WS_VSCROLL);
    }*/
    void reset()
    {
        SendMessage(handle,CB_RESETCONTENT,0,0);
    }
    int finditem(const wchar_t *str)
    {
        return SendMessage(handle,CB_FINDSTRINGEXACT,-1,(LPARAM)str);
    }

};
//}

#endif
