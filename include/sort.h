#ifndef APP_SORT_H
#define APP_SORT_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/listctrl.h>

class SortInfoStruct
{
public:
    enum class SortInfoType : int
    {
        string = 0,
        integer = 1,
        date = 2
    };
    SortInfoStruct(wxListCtrl *list);
    static int wxCALLBACK sortlist(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortData);
    int column;
    int type;
    bool direction;
    wxListCtrl *listCtrl = nullptr;
};

#endif