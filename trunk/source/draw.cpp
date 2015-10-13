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
#include "logging.h"
#include "matcher.h"
#include "settings.h"
#include "common.h"
#include "manager.h"
#include "gui.h"

#include <windows.h>

// Depend on Win32API
#include "draw.h"     // todo: lots of Win32
#include "system.h"
#include "theme.h"    // todo: HWND
#include "enum.h"     // needs Version from indexing.h
#include "main.h"     // todo: lots of Win32

#include <setupapi.h>       // for SetupDiGetClassDescription()
#ifdef _MSC_VER
#include "webp\decode.h"
#else
#include <webp\decode.h>
#endif
#include <memory>

//{ Global vars
int rtl=0;
//}

//{ Image
void Image::MakeCopy(Image &t)
{
    Release();
    bitmap=t.bitmap;
    ldc=t.ldc;
    sx=t.sx;
    sy=t.sy;
    hasalpha=t.hasalpha;
    iscopy=1;
}

void Image::Load(int i)
{
    wchar_t *filename=D_STR(i);

    Release();

    if(wcsstr(filename,L"RES_"))
        LoadFromRes(_wtoi_my(filename+4));
    else
        LoadFromFile(filename);
}

bool Image::IsLoaded()const{return ldc!=nullptr;}

void Image::Release()
{
    if(bitmap&&!iscopy)
    {
        SelectObject(ldc,oldbitmap);
        int r=DeleteDC(ldc);
        if(!r)Log.print_err("ERROR in box_init(): failed DeleteDC\n");
        r=DeleteObject(bitmap);
        if(!r)Log.print_err("ERROR in box_init(): failed DeleteObject\n");
    }
    bitmap=nullptr;
    ldc=nullptr;
    iscopy=0;
}

void Image::LoadFromFile(wchar_t *filename)
{
    wchar_t buf[BUFLEN];
    FILE *f;
    size_t sz;

    if(!filename||!*filename)return;
    wsprintf(buf,L"%s\\themes\\%s",Settings.data_dir,filename);
    f=_wfopen(buf,L"rb");
    if(!f)
    {
        Log.print_err("ERROR in image_loadFile(): file '%S' not found\n",buf);
        return;
    }
    fseek(f,0,SEEK_END);
    sz=ftell(f);
    fseek(f,0,SEEK_SET);
    std::unique_ptr<BYTE[]> imgbuf(new BYTE[sz]);

    sz=fread(imgbuf.get(),1,sz,f);
    if(!sz)
    {
        Log.print_err("ERROR in image_loadFile(): cannnot read from file '%S'\n",buf);
        return;
    }
    fclose(f);
    CreateMyBitmap(imgbuf.get(),sz);
}

void Image::LoadFromRes(int id)
{
    int sz;
    HGLOBAL myResourceData;

    get_resource(id,&myResourceData,&sz);
    if(!sz)
    {
        Log.print_err("ERROR in image_loadRes(): failed get_resource\n");
        return;
    }
    CreateMyBitmap((BYTE *)myResourceData,sz);
}

void Image::CreateMyBitmap(BYTE *data,size_t sz)
{
    BYTE *big;
    hasalpha=sx=sy=0;
    ldc=nullptr;
#ifdef CONSOLE_MODE
    UNREFERENCED_PARAMETER(data)
    UNREFERENCED_PARAMETER(sz)
    return;
#else
    int ret=WebPGetInfo(data,sz,&sx,&sy);
    if(!ret)
    {
        Log.print_err("ERROR in image_load(): failed WebPGetInfo(%d)\n",ret);
        return;
    }
    big=WebPDecodeBGRA(data,sz,&sx,&sy);
    if(!big)
    {
        Log.print_err("ERROR in image_load(): failed WebPDecodeBGRA\n");
        return;
    }
#endif
    BITMAPINFO bmi;
    ZeroMemory(&bmi,sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth=sx;
    bmi.bmiHeader.biHeight=-sy;
    bmi.bmiHeader.biPlanes=1;
    bmi.bmiHeader.biBitCount=32;
    bmi.bmiHeader.biCompression=BI_RGB;
    bmi.bmiHeader.biSizeImage=sx*sy*4;

    BYTE *bits;
    ldc=CreateCompatibleDC(nullptr);
    bitmap=CreateDIBSection(ldc,&bmi,DIB_RGB_COLORS,(void **)&bits,nullptr,0);
    if(!bitmap)
    {
        Log.print_err("ERROR in CreateMyBitmap(): failed CreateDIBSection\n");
        free(big);
        return;
    }

    BYTE *p2=big;
    for(int i=0;i<sy*sx;i++)
    {
        BYTE B,G,R,A;
        B=*p2++;
        G=*p2++;
        R=*p2++;
        A=*p2++;
        double dA=A/255.;
        if(A!=255)hasalpha=1;

        *bits++=(BYTE)(B*dA);
        *bits++=(BYTE)(G*dA);
        *bits++=(BYTE)(R*dA);
        *bits++=A;
    }
    SelectObject(ldc,bitmap);
    free(big);
    //    Log.print_con("%dx%d:%d,%d\n",sx,sy,hasalpha,index);
}

void Image::Draw(HDC dc,int x1,int y1,int x2,int y2,int anchor,int fill)
{
    BLENDFUNCTION blend={AC_SRC_OVER,0,255,AC_SRC_ALPHA};
    int xi,yi,wx,wy,wx1,wy1,wx2,wy2;

    if(!sx)return;

    SetLayout(ldc,rtl?LAYOUT_RTL:0);

    wx=(fill&HSTR)?x2-x1:sx;
    wy=(fill&VSTR)?y2-y1:sy;
    if(fill&ASPECT)
    {
        if(fill&HSTR)wy=(int)(sy*((double)wx/sx));
        if(fill&VSTR)wx=(int)(sx*((double)wy/sy));
    }

    for(xi=0;xi<x2;xi+=wx)
    {
        for(yi=0;yi<y2;yi+=wy)
        {
            int x=x1+xi,y=y1+yi;
            if(anchor&RIGHT)  x=x2-xi-wx;
            if(anchor&BOTTOM) y=y2-yi-wy;
            if(anchor&HCENTER)x=(x2-x1-wx)/2;
            if(anchor&VCENTER)y=(y2-y1-wy)/2;

            wx1=(x+wx>x2)?x2-x:wx;
            wy1=(y+wy>y2)?y2-y:wy;
            wx2=(x+wx>x2)?wx1:sx;
            wy2=(y+wy>y2)?wy1:sy;

            if(hasalpha)
                AlphaBlend(dc,x,y,wx1,wy1,ldc,0,0,wx2,wy2,blend);
            else if(wx==wx2&&wy==wy2)
                BitBlt(dc,x,y,wx1,wy1,ldc,0,0,SRCCOPY);
            else
                StretchBlt(dc,x,y,wx1,wy1,ldc,0,0,wx2,wy2,SRCCOPY);

            if((fill&VTILE)==0)break;
        }
        if((fill&HTILE)==0)break;
    }
    //drawrect(dc,x1,y1,x2,y2,0xFF000000,0xFF00,1,0);
}
//}

//{ Canvas
void Canvas::DrawConnection(int x1,int pos,int ofsy,int curpos)
{
    HPEN oldpen,newpen;

    newpen=CreatePen(PS_SOLID,D(DRVITEM_LINE_WIDTH),D(DRVITEM_LINE_COLOR));
    oldpen=(HPEN)SelectObject(hdcMem,newpen);
    MoveToEx(hdcMem,x1-D(DRVITEM_LINE_INTEND)/2,curpos-D(DRVITEM_DIST_Y0)+D(DRVITEM_WY)-ofsy,nullptr);
    LineTo(hdcMem,x1-D(DRVITEM_LINE_INTEND)/2,pos+D(DRVITEM_WY)/2);
    LineTo(hdcMem,x1,pos+D(DRVITEM_WY)/2);
    SelectObject(hdcMem,oldpen);
    DeleteObject(newpen);
}

Canvas::Canvas():
    x(0),
    y(0),
    localDC(nullptr),
    hdcMem(CreateCompatibleDC(nullptr)),
    bitmap(nullptr),
    oldbitmap(nullptr),
    //ps(nullptr),
    hwnd(nullptr),
    clipping(nullptr)
{
    if(!hdcMem)
        Log.print_err("ERROR in canvas_init(): failed CreateCompatibleDC\n");
    else
    {
        int r=SetBkMode(hdcMem,TRANSPARENT);
        if(!r)Log.print_err("ERROR in canvas_init(): failed SetBkMode\n");
    }
}

Canvas::~Canvas()
{
    if(hdcMem)
    {
        int r=DeleteDC(hdcMem);
        if(!r)Log.print_err("ERROR in canvas_free(): failed DeleteDC\n");
        hdcMem=nullptr;
    }

    if(bitmap)
    {
        //r=(int)SelectObject(hdcMem,oldbitmap);
        //if(!r)Log.log_err("ERROR in canvas_free(): failed SelectObject\n");
        int r=DeleteObject(bitmap);
        if(!r)Log.print_err("ERROR in canvas_free(): failed DeleteObject\n");
        bitmap=nullptr;
    }
}

void Canvas::begin(HWND nhwnd,int nx,int ny)
{
    unsigned r32;

    hwnd=nhwnd;
    localDC=BeginPaint(hwnd,&ps);
    if(!localDC)Log.print_err("ERROR in canvas_begin(): failed BeginPaint\n");

    if(x!=nx||y!=ny)
    {
        x=nx;
        y=ny;
        if(bitmap)
        {
            HGDIOBJ r=SelectObject(hdcMem,oldbitmap);
            if(!r)Log.print_err("ERROR in canvas_begin(): failed SelectObject(oldbitmap)\n");
            r32=DeleteObject(bitmap);
            if(!r32)Log.print_err("ERROR in canvas_begin(): failed DeleteObject\n");
        }
        bitmap=CreateCompatibleBitmap(localDC,x,y);
        if(!bitmap)
            Log.print_err("ERROR in canvas_begin(): failed CreateCompatibleBitmap\n");
        else
        {
            oldbitmap=(HBITMAP)SelectObject(hdcMem,bitmap);
            if(!oldbitmap)Log.print_err("ERROR in canvas_begin(): failed SelectObject(bitmap)\n");
        }
    }
    clipping=CreateRectRgnIndirect(&ps.rcPaint);
    if(!clipping)Log.print_err("ERROR in canvas_begin(): failed BeginPaint\n");
    SetStretchBltMode(hdcMem,HALFTONE);
    r32=SelectClipRgn(hdcMem,clipping);
    if(!r32)Log.print_err("ERROR in canvas_begin(): failed SelectClipRgn\n");
    SetLayout(hdcMem,rtl?LAYOUT_RTL:0);
}

void Canvas::end()
{
    int r;

    r=BitBlt(localDC,
             ps.rcPaint.left,ps.rcPaint.top,ps.rcPaint.right,ps.rcPaint.bottom,
             hdcMem,
             ps.rcPaint.left,ps.rcPaint.top,
             SRCCOPY);
    SelectClipRgn(hdcMem,nullptr);
    if(!r)Log.print_err("ERROR in canvas_end(): failed BitBlt\n");
    r=DeleteObject(clipping);
    if(!r)Log.print_err("ERROR in canvas_end(): failed DeleteObject\n");
    EndPaint(hwnd,&ps);
}
//}

//{ Text
textdata_t::textdata_t(Canvas &canvas_,int xofs):
    pcanvas(&canvas_),
    ofsx(xofs),
    wy(D(POPUP_WY)),
    maxsz(0),
    col(D(POPUP_TEXT_COLOR)),
    x(D(POPUP_OFSX)+xofs),
    y(D(POPUP_OFSY))
{
}

void textdata_t::ret()
{
    x=D(POPUP_OFSX)+ofsx;
}

void textdata_t::ret_ofs(int a)
{
    x=D(POPUP_OFSX)+a;
}

void textdata_t::nl()
{
    y+=wy;
}

void textdata_horiz_t::limitskip()
{
    x+=limits[i++];
}

void textdata_vert::shift_r(){maxsz+=(int)POPUP_SYSINFO_OFS;}
void textdata_vert::shift_l(){maxsz-=(int)POPUP_SYSINFO_OFS;}

void textdata_t::TextOut_CM(int x1,int y1,const wchar_t *str,int color,int *maxsz1,int mode1)
{
    int ss=pcanvas->GetTextExtent(str);
    if(ss>*maxsz1)*maxsz1=ss;

    if(!mode1)return;
    pcanvas->SetTextColor(color);
    pcanvas->DrawTextXY(x1,y1,str);
}

void textdata_horiz_t::TextOutP(const wchar_t *format,...)
{
    wchar_t buffer[BUFLEN];
    va_list args;
    va_start(args,format);
    _vsnwprintf(buffer,BUFLEN,format,args);

    TextOut_CM(x,y,buffer,col,&limits[i],mode);
    x+=limits[i];
    i++;
    va_end(args);
}

void textdata_t::TextOutF(int col1,const wchar_t *format,...)
{
    wchar_t buffer[BUFLEN];
    va_list args;
    va_start(args,format);
    _vsnwprintf(buffer,BUFLEN,format,args);

    TextOut_CM(x,y,buffer,col1,&maxsz,1);
    y+=wy;
    va_end(args);
}

void textdata_t::TextOutF(const wchar_t *format,...)
{
    wchar_t buffer[BUFLEN];
    va_list args;
    va_start(args,format);
    _vsnwprintf(buffer,BUFLEN,format,args);

    TextOut_CM(x,y,buffer,col,&maxsz,1);
    y+=wy;
    va_end(args);
}

void textdata_vert::TextOutSF(const wchar_t *str,const wchar_t *format,...)
{
    wchar_t buffer[BUFLEN];
    va_list args;
    va_start(args,format);
    _vsnwprintf(buffer,BUFLEN,format,args);
    TextOut_CM(x,y,str,col,&maxsz,1);
    TextOut_CM((int)(x+POPUP_SYSINFO_OFS),y,buffer,col,&maxsz,1);
    y+=wy;
    va_end(args);
}
//}

//{Popup
void popup_resize(int x,int y)
{
    if(Popup.floating_x!=x||Popup.floating_y!=y)
    {
        POINT p1;

        Popup.floating_x=x;
        Popup.floating_y=y;
        GetCursorPos(&p1);
        SetCursorPos(p1.x+1,p1.y);
        SetCursorPos(p1.x,p1.y);
    }
}

void popup_about(Canvas &canvas)
{
    textdata_vert td(canvas);

    td.ret();
    td.TextOutF(L"Snappy Driver Installer %s",STR(STR_ABOUT_VER));
    td.nl();

    RECT rect;
    rect.left=td.getX();
    rect.top=td.getY();
    rect.right=D(POPUP_WX)-D(POPUP_OFSX)*2;
    rect.bottom=900;
    canvas.CalcBoundingBox(STR(STR_ABOUT_LICENSE),&rect);
    canvas.DrawTextRect(STR(STR_ABOUT_LICENSE),&rect);

    td.nl();
    td.nl();
    td.nl();
    td.TextOutF(L"%s%s",STR(STR_ABOUT_DEV_TITLE),STR(STR_ABOUT_DEV_LIST));
    td.TextOutF(L"%s%s",STR(STR_ABOUT_TESTERS_TITLE),STR(STR_ABOUT_TESTERS_LIST));

    popup_resize(D(POPUP_WX),rect.bottom+D(POPUP_OFSY));
}

void format_size(wchar_t *buf,long long val,int isspeed)
{
#ifdef USE_TORRENT
    StrFormatSize(val,buf,BUFLEN);
#else
    buf[0]=0;
    UNREFERENCED_PARAMETER(val);
#endif
    if(isspeed)wcscat(buf,STR(STR_UPD_SEC));
}

void format_time(wchar_t *buf,long long val)
{
    long long days,hours,mins,secs;

    secs=val/1000;
    mins=secs/60;
    hours=mins/60;
    days=hours/24;

    secs%=60;
    mins%=60;
    hours%=24;

    wcscpy(buf,L"\x221E");
    if(secs) wsprintf(buf,L"%d %s",(int)secs,STR(STR_UPD_TSEC));
    if(mins) wsprintf(buf,L"%d %s %d %s",(int)mins,STR(STR_UPD_TMIN),(int)secs,STR(STR_UPD_TSEC));
    if(hours)wsprintf(buf,L"%d %s %d %s",(int)hours,STR(STR_UPD_THOUR),(int)mins,STR(STR_UPD_TMIN));
    if(days) wsprintf(buf,L"%d %s %d %s",(int)days,STR(STR_UPD_TDAY),(int)hours,STR(STR_UPD_THOUR));
}
//}

//{ Draw
int mirw(int x,int ofs,int w)
{
    UNREFERENCED_PARAMETER(w);
    return x+ofs;
}
void Canvas::DrawTextXY(int x1,int y1,LPCTSTR buf)
{
    TextOut(hdcMem,x1,y1,buf,(int)wcslen(buf));
}
int Xm(int x,int o)
{
    UNREFERENCED_PARAMETER(o);
    return x>=0?x:(MainWindow.main1x_c+x);
}
int Ym(int y){return y>=0?y:(MainWindow.main1y_c+y);}
int XM(int w,int x){return w>=0?w:(w+MainWindow.main1x_c-x);}
int YM(int y,int o){return y>=0?y:(MainWindow.main1y_c+y-o);}

int Xg(int x,int o)
{
    UNREFERENCED_PARAMETER(o);
    return x>=0?x:(MainWindow.mainx_c+x);
}
int Yg(int y){return y>=0?y:(MainWindow.mainy_c+y);}
int XG(int x,int o){return x>=0?x:(MainWindow.mainx_c+x-o);}
int YG(int y,int o){return y>=0?y:(MainWindow.mainy_c+y-o);}

bool isRebootDesired()
{
    ClickVisiter cv{ID_REBOOT,CHECKBOX::GET};
    wPanels->Accept(cv);
    return cv.GetValue()!=0;
}

//{ ClipRegion
class ClipRegionImp
{
    ClipRegionImp(const ClipRegionImp&)=delete;
    ClipRegionImp &operator = (const ClipRegionImp&)=delete;

private:
    HRGN hrgn;
public:
    ClipRegionImp():hrgn(nullptr){}
    ClipRegionImp(int x1,int y1,int x2,int y2);
    ClipRegionImp(int x1,int y1,int x2,int y2,int r);
    ~ClipRegionImp();

    void setRegion(int x1,int y1,int x2,int y2);

    friend class Canvas;
};

ClipRegionImp::ClipRegionImp(int x1,int y1,int x2,int y2):
    hrgn(CreateRectRgn(x1,y1,x2,y2))
{
    if(!hrgn)Log.print_err("ERROR in ClipRegion(): failed CreateRectRgn\n");
}

ClipRegionImp::ClipRegionImp(int x1,int y1,int x2,int y2,int r):
    hrgn(CreateRoundRectRgn(x1,y1,x2,y2,r,r))
{
    if(!hrgn)Log.print_err("ERROR in ClipRegion(): failed CreateRoundRectRgn\n");
}

void ClipRegionImp::setRegion(int x1,int y1,int x2,int y2)
{
    if(hrgn)DeleteObject(hrgn);
    hrgn=CreateRectRgn(x1,y1,x2,y2);
    if(!hrgn)Log.print_err("ERROR in ClipRegion(): failed setRegion\n");
}

ClipRegionImp::~ClipRegionImp()
{
    if(hrgn)DeleteObject(hrgn);
}

ClipRegion::ClipRegion(int x1,int y1,int x2,int y2):imp(new ClipRegionImp(x1,y1,x2,y2)){}
ClipRegion::ClipRegion(int x1,int y1,int x2,int y2,int r):imp(new ClipRegionImp(x1,y1,x2,y2,r)){}
ClipRegion::ClipRegion():imp(new ClipRegionImp()){}
ClipRegion::~ClipRegion(){delete imp;}
void ClipRegion::setRegion(int x1,int y1,int x2,int y2){imp->setRegion(x1,y1,x2,y2);}
//}

void Font::SetFont(const wchar_t *name,int size,int bold)
{
    if(hFont&&!DeleteObject(hFont))
        Log.print_err("ERROR in setfont(): failed DeleteObject\n");

    hFont=CreateFont(-size,0,0,0,bold?FW_BOLD:FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                     CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH,name);

    if(!hFont)Log.print_err("ERROR in setfont(): failed CreateFont\n");
}

Font::~Font()
{
    if(hFont&&!DeleteObject(hFont))
        Log.print_err("ERROR in manager_free(): failed DeleteObject\n");
}

void Canvas::SetTextColor(int color)
{
    ::SetTextColor(hdcMem,color);
}

void Canvas::SetFont(Font *font)
{
    SelectObject(hdcMem,font->hFont);
}

void Canvas::SetClipRegion(ClipRegion &clip)
{
    SelectClipRgn(hdcMem,clip.imp->hrgn);
}

void Canvas::ClearClipRegion()
{
    SelectClipRgn(hdcMem,nullptr);
}

void Canvas::CalcBoundingBox(const wchar_t *str,RECT *rect)
{
    DrawText(hdcMem,str,-1,rect,DT_WORDBREAK|DT_CALCRECT);
}

void Canvas::DrawTextRect(const wchar_t *bufw,RECT *rect)
{
    DrawText(hdcMem,bufw,-1,rect,DT_WORDBREAK);
}

int  Canvas::GetTextExtent(const wchar_t *str)
{
    SIZE ss;
    GetTextExtentPoint32(hdcMem,str,(int)wcslen(str),&ss);
    return ss.cx;
}

void Canvas::DrawImage(Image &image,int x1,int y1,int wx,int wy,int flags1,int flags2)
{
    image.Draw(hdcMem,x1,y1,wx,wy,flags1,flags2);
}

void Canvas::CopyCanvas(Canvas *source,int x1,int y1)
{
    BitBlt(hdcMem,0,0,x,y,source->hdcMem,x1,y1,SRCCOPY);
}

void loadGUID(GUID *g,const char *s)
{
    char d[3];
    d[2]=0;
    g->Data1=strtol(s+1,nullptr,16);
    g->Data2=strtol(s+10,nullptr,16)&0xFFFF;
    g->Data3=strtol(s+15,nullptr,16)&0xFFFF;
    memcpy(d,s+15+5,2);g->Data4[0]=strtol(d,nullptr,16)&0xFF;
    memcpy(d,s+15+5+2,2);g->Data4[1]=strtol(d,nullptr,16)&0xFF;
    memcpy(d,s+15+6+4,2);g->Data4[2]=strtol(d,nullptr,16)&0xFF;
    memcpy(d,s+15+6+6,2);g->Data4[3]=strtol(d,nullptr,16)&0xFF;
    memcpy(d,s+15+6+8,2);g->Data4[4]=strtol(d,nullptr,16)&0xFF;
    memcpy(d,s+15+6+10,2);g->Data4[5]=strtol(d,nullptr,16)&0xFF;
    memcpy(d,s+15+6+12,2);g->Data4[6]=strtol(d,nullptr,16)&0xFF;
    memcpy(d,s+15+6+14,2);g->Data4[7]=strtol(d,nullptr,16)&0xFF;

    /*Log.print_con("%s\n",s);
    Log.print_con("{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}\n\n",g->Data1,g->Data2,g->Data3,
    (int)(g->Data4[0]),(int)(g->Data4[1]),
    (int)(g->Data4[2]),(int)(g->Data4[3]),(int)(g->Data4[4]),
    (int)(g->Data4[5]),(int)(g->Data4[6]),(int)(g->Data4[7]));*/
}

void Canvas::DrawIcon(int x1,int y1,const char *guid_driverpack,const GUID *guid_device)
{
    HICON hIcon;
    BOOL ret=false;
    if(guid_driverpack)
    {
        GUID gd;
        loadGUID(&gd,guid_driverpack);
        ret=SetupDiLoadClassIcon(&gd,&hIcon,nullptr);
    }
    if(!ret)ret=SetupDiLoadClassIcon(guid_device,&hIcon,nullptr);
    if(ret)
    {
        if(rtl)
        {
            HICON miricon;
            miricon=CreateMirroredIcon(hIcon);
            DestroyIcon(hIcon);
            hIcon=miricon;
        }
        DrawIconEx(hdcMem,x1,y1,hIcon,D(ITEM_ICON_SIZE),D(ITEM_ICON_SIZE),0,nullptr,DI_NORMAL);
        DestroyIcon(hIcon);
    }
}

void Canvas::DrawEmptyRect(int x1,int y1,int x2,int y2,int color)
{
    SelectObject(hdcMem,GetStockObject(DC_BRUSH));
    SelectObject(hdcMem,GetStockObject(DC_PEN));
    SetDCBrushColor(hdcMem,color);
    Rectangle(hdcMem,x1,y1,x2,y2);
}

void Canvas::DrawLine(int x1,int y1,int x2,int y2)
{
    MoveToEx(hdcMem,x1,y1,nullptr);
    LineTo(hdcMem,x2,y2);
}

void Canvas::DrawFilledRect(int x1,int y1,int x2,int y2,int color1,int color2,int w,int rn)
{
    HPEN newpen,oldpen;
    HBRUSH newbrush,oldbrush;
    HGDIOBJ r;
    unsigned r32;

    //oldbrush=(HBRUSH)SelectObject(hdc,GetStockObject(color1&0xFF000000?NULL_BRUSH:DC_BRUSH));
    newbrush=CreateSolidBrush(color1);
    oldbrush=(HBRUSH)SelectObject(hdcMem,newbrush);
    if(color1&0xFF000000)(HBRUSH)SelectObject(hdcMem,GetStockObject(NULL_BRUSH));

    if(!oldbrush)Log.print_err("ERROR in drawrect(): failed SelectObject(GetStockObject)\n");
    r32=SetDCBrushColor(hdcMem,color1);
    if(r32==CLR_INVALID)Log.print_err("ERROR in drawrect(): failed SetDCBrushColor\n");

    newpen=CreatePen(w?PS_SOLID:PS_NULL,w,color2);
    if(!newpen)Log.print_err("ERROR in drawrect(): failed CreatePen\n");
    oldpen=(HPEN)SelectObject(hdcMem,newpen);
    if(!oldpen)Log.print_err("ERROR in drawrect(): failed SelectObject(newpen)\n");

    if(rn)
        RoundRect(hdcMem,x1,y1,x2,y2,rn,rn);
    else
        Rectangle(hdcMem,x1,y1,x2,y2);

    if(oldpen)
    {
        r=SelectObject(hdcMem,oldpen);
        if(!r)Log.print_err("ERROR in drawrect(): failed SelectObject(oldpen)\n");
    }
    r=SelectObject(hdcMem,oldbrush);
    if(!r)Log.print_err("ERROR in drawrect(): failed SelectObject(oldbrush)\n");
    if(newpen)r32=DeleteObject(newpen);
    if(!r32)Log.print_err("ERROR in drawrect(): failed DeleteObject(newpen)\n");
    r32=DeleteObject(newbrush);
    if(!r32)Log.print_err("ERROR in drawrect(): failed DeleteObject(newbrush)\n");
}

void Canvas::DrawWidget(int x1,int y1,int x2,int y2,int id)
{
    if(id<0||id>=BOX_NUM)
    {
        Log.print_err("ERROR in box_draw(): invalid id=%d\n",id);
        return;
    }
    int i=boxindex[id];
    if(i<0||i>=THEME_NM)
    {
        Log.print_err("ERROR in box_draw(): invalid index=%d\n",i);
        return;
    }
    DrawFilledRect(x1,y1,x2,y2,D(i),D(i+1),D(i+2),D(i+3));
    DrawImage(*vTheme->GetImage(id),x1,y1,x2,y2,D(i+5),D(i+6));
}

void Canvas::DrawCheckbox(int x1,int y1,int wx,int wy,int checked,int active)
{
    RECT rect;
    int i=4+(active?1:0)+(checked?2:0);

    rect.left=x1;
    rect.top=y1;
    rect.right=x1+wx;
    rect.bottom=y1+wy;

    if(vTheme->GetIcon(i)->IsLoaded())
        DrawImage(*vTheme->GetIcon(i),x1,y1,x1+wx,y1+wy,0,Image::HSTR|Image::VSTR);
    else
        DrawFrameControl(hdcMem,&rect,DFC_BUTTON,DFCS_BUTTONCHECK|(checked?DFCS_CHECKED:0));
}

void drawpopup(int itembar,int type,int x,int y,HWND hwnd)
{
    POINT p={x,y};
    HMONITOR hMonitor;
    MONITORINFO mi;
    int needupdate;

    if((type==FLOATING_CMPDRIVER||type==FLOATING_DRIVERLST)&&itembar<0)type=FLOATING_NONE;
    if(type==FLOATING_TOOLTIP&&(itembar<=1||!*STR(itembar)))type=FLOATING_NONE;

    if(rtl)p.x+=Popup.floating_x;
    ClientToScreen(hwnd,&p);
    needupdate=Popup.floating_itembar!=itembar||Popup.floating_type!=type;
    Popup.floating_itembar=itembar;
    Popup.floating_type=type;

    if(type!=FLOATING_NONE)
    {
        //if(type==FLOATING_ABOUT)p.y=p.y-floating_y-30;
        //if(type==FLOATING_CMPDRIVER||type==FLOATING_DRIVERLST)
        {
            hMonitor=MonitorFromPoint(p,MONITOR_DEFAULTTONEAREST);
            mi.cbSize=sizeof(MONITORINFO);
            GetMonitorInfo(hMonitor,&mi);

            mi.rcWork.right-=15;
            if(p.x+Popup.floating_x>mi.rcWork.right)p.x=mi.rcWork.right-Popup.floating_x;
            if(p.x<5)p.x=5;
            if(p.y+Popup.floating_y>mi.rcWork.bottom-20)p.y=p.y-Popup.floating_y-30;
            if(p.y<5)p.y=5;
        }

        MoveWindow(Popup.hPopup,p.x+10,p.y+20,Popup.floating_x,Popup.floating_y,1);
        if(needupdate)InvalidateRect(Popup.hPopup,nullptr,0);

        TRACKMOUSEEVENT tme;
        tme.cbSize=sizeof(tme);
        tme.hwndTrack=hwnd;
        tme.dwFlags=TME_LEAVE|TME_HOVER;
        tme.dwHoverTime=(MainWindow.ctrl_down||MainWindow.space_down)?1:Settings.hintdelay;
        TrackMouseEvent(&tme);
    }
    if(type==FLOATING_NONE)ShowWindow(Popup.hPopup,SW_HIDE);
}

HICON CreateMirroredIcon(HICON hiconOrg)
{
    HDC hdcScreen,hdcBitmap,hdcMask=nullptr;
    HBITMAP hbm,hbmMask,hbmOld,hbmOldMask;
    BITMAP bm;
    ICONINFO ii;
    HICON hicon=nullptr;

    hdcBitmap=CreateCompatibleDC(nullptr);
    if(hdcBitmap)
    {
        hdcMask=CreateCompatibleDC(nullptr);
        if(hdcMask)
        {
            SetLayout(hdcBitmap,LAYOUT_RTL);
            SetLayout(hdcMask,LAYOUT_RTL);
        }
        else
        {
            DeleteDC(hdcBitmap);
            hdcBitmap=nullptr;
        }
    }
    hdcScreen=GetDC(nullptr);
    if(hdcScreen)
    {
        if(hdcBitmap&&hdcMask)
        {
            if(hiconOrg)
            {
                if(GetIconInfo(hiconOrg,&ii)&&GetObject(ii.hbmColor,sizeof(BITMAP),&bm))
                {
                    // Do the cleanup for the bitmaps.
                    DeleteObject(ii.hbmMask);
                    DeleteObject(ii.hbmColor);
                    ii.hbmMask=ii.hbmColor=nullptr;
                    hbm=CreateCompatibleBitmap(hdcScreen,bm.bmWidth,bm.bmHeight);
                    hbmMask=CreateBitmap(bm.bmWidth,bm.bmHeight,1,1,nullptr);
                    hbmOld=(HBITMAP)SelectObject(hdcBitmap,hbm);
                    hbmOldMask=(HBITMAP)SelectObject(hdcMask,hbmMask);
                    DrawIconEx(hdcBitmap,0,0,hiconOrg,bm.bmWidth,bm.bmHeight,0,nullptr,DI_IMAGE);
                    DrawIconEx(hdcMask,0,0,hiconOrg,bm.bmWidth,bm.bmHeight,0,nullptr,DI_MASK);
                    SelectObject(hdcBitmap,hbmOld);
                    SelectObject(hdcMask,hbmOldMask);

                    // Create the new mirrored icon and delete bitmaps
                    ii.hbmMask=hbmMask;
                    ii.hbmColor=hbm;
                    hicon=CreateIconIndirect(&ii);
                    DeleteObject(hbm);
                    DeleteObject(hbmMask);
                }
            }
        }
        ReleaseDC(nullptr,hdcScreen);
    }
    if(hdcBitmap)DeleteDC(hdcBitmap);
    if(hdcMask)DeleteDC(hdcMask);
    return hicon;
}
//}
