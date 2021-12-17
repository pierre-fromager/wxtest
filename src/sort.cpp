#include "sort.h"

SortInfoStruct::SortInfoStruct(wxListCtrl *list)
{
    column = 0;
    type = static_cast<int>(SortInfoStruct::SortInfoType::string);
    direction = true;
    listCtrl = list;
}

int wxCALLBACK SortInfoStruct::sortlist(
    wxIntPtr item1,
    wxIntPtr item2,
    wxIntPtr sortData)
{
    SortInfoStruct *SortInfo = (SortInfoStruct *)sortData;
    wxListCtrl *sortList = SortInfo->listCtrl;
    wxListItem item;
    wxDateTime dt1, dt2;
    wxString str1, str2;
    switch (SortInfo->type)
    {
    case static_cast<int>(SortInfoStruct::SortInfoType::date):
        dt1 = item.GetData();
        dt2 = item.GetData();
        return (SortInfo->direction && dt1.IsLaterThan(dt2)) ? -1 : 1;

    case static_cast<int>(SortInfoStruct::SortInfoType::string):
        item.SetId(item1);
        item.SetColumn(SortInfo->column);
        item.SetMask(wxLIST_MASK_TEXT);
        sortList->GetItem(item);
        str1 = item.GetText();
        item2 = item1 + 1;
        item.SetId(item2);
        item.SetColumn(SortInfo->column);
        item.SetMask(wxLIST_MASK_TEXT);
        sortList->GetItem(item);
        str2 = item.GetText();
        return (SortInfo->direction && str1.CmpNoCase(str2) < 0) ? -1 : 1;
    }

    return 0;
}