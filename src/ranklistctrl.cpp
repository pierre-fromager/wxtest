
#include "ranklistctrl.h"

RankListCtrl::RankListCtrl(wxWindow *parent) : wxListCtrl(
                                                   parent,
                                                   wxID_ANY,
                                                   wxDefaultPosition,
                                                   wxDefaultSize,
                                                   wxLC_REPORT | wxLC_SORT_ASCENDING | wxLC_SORT_DESCENDING)
{
    m_imageList = new wxImageList(16, 16, true);
    m_imageList->Add(wxBitmap(sort_null_xpm));
    m_imageList->Add(wxBitmap(sort_asc_xpm));
    m_imageList->Add(wxBitmap(sort_desc_xpm));
    SetImageList(m_imageList, wxIMAGE_LIST_SMALL);
    InsertColumn(Column_Index, _(RANK_COL_LABEL_INDEX));
    SetColumnWidth(Column_Index, wxLIST_AUTOSIZE_USEHEADER);
    InsertColumn(Column_Timestamp, _(RANK_COL_LABEL_TIMESTAMP));
    SetColumnWidth(Column_Timestamp, wxLIST_AUTOSIZE_USEHEADER);
    InsertColumn(Column_Status, _(RANK_COL_LABEL_STATUS));
    SetColumnWidth(Column_Status, wxLIST_AUTOSIZE_USEHEADER);
    Bind(wxEVT_LIST_COL_CLICK, &RankListCtrl::OnColClick, this);
}

RankListCtrl::~RankListCtrl()
{
    delete m_imageList;
}

void RankListCtrl::AddRank(RankItem r)
{
    r.index = wxString::Format(wxT("%zu"), rankIndex);
    long result = InsertItem(rankIndex, r.index);
    SetItem(result, Column_Timestamp, r.timestamp);
    SetItem(result, Column_Status, r.status);
    SetItemData(result, (long)rankIndex);
    m_ranks.push_back(r);
    wxGetApp().GetMqtt()->setPublishTopic("wxwidget/app/state/item");
    const wxString &pubitem = r.index + ";" + r.timestamp + ";" + r.status;
    const std::string mqttPayload = std::string(pubitem.mb_str());
    wxGetApp().GetMqtt()->publish(mqttPayload);
    rankIndex++;
}

void RankListCtrl::Reset()
{
    m_ranks.clear();
    this->DeleteAllItems();
    rankIndex = 0;
}

int RankListCtrl::GetRankId(wxIntPtr index)
{
    wxListItem listItem;
    listItem.m_mask = wxLIST_MASK_TEXT;
    listItem.m_itemId = index;
    listItem.m_col = Column_Index;
    GetItem(listItem);
    return wxAtoi(listItem.m_text);
}

RankItem RankListCtrl::GetRank(wxIntPtr index)
{
    return m_ranks[GetRankId(index)];
}

void RankListCtrl::SetColumnImage(int col, int image)
{
    wxListItem item;
    item.SetMask(wxLIST_MASK_IMAGE);
    item.SetImage(image);
    SetColumn(col, item);
}

void RankListCtrl::OnColClick(wxListEvent &evt)
{
    int column = evt.GetColumn();
    direction = !direction;
    if (column < 0 || this->GetItemCount() < 2)
        return;
    for (int c = Column_Index; c <= Column_Status; c++)
        SetColumnImage(c, 0);
    SetColumnImage(column, (direction) ? 2 : 1);
    const wxIntPtr dataPtr = reinterpret_cast<wxIntPtr>(&m_ranks);
    if (direction)
        switch (column)
        {
        case Column_Index:
            SortItems(CompareIndexAsc, dataPtr);
            break;
        case Column_Timestamp:
            SortItems(CompareTimestampAsc, dataPtr);
            break;
        case Column_Status:
            SortItems(CompareStatusAsc, dataPtr);
            break;
        default:
            wxFAIL;
        }
    else
        switch (column)
        {
        case Column_Index:
            SortItems(CompareIndexDesc, dataPtr);
            break;
        case Column_Timestamp:
            SortItems(CompareTimestampDesc, dataPtr);
            break;
        case Column_Status:
            SortItems(CompareStatusDesc, dataPtr);
            break;
        default:
            wxFAIL;
        }
}

int RankListCtrl::compareStr(wxString a, wxString b)
{
    return a.CmpNoCase(b);
}

int RankListCtrl::compareInt(wxString a, wxString b)
{
    return (wxAtoi(a) > wxAtoi(b));
}

void RankListCtrl::GetRanks(
    wxIntPtr item1,
    wxIntPtr item2,
    wxIntPtr sortData,
    RankItem &r1,
    RankItem &r2)
{
    RankList *ranks = reinterpret_cast<RankList *>(sortData);
    r1 = (*ranks)[static_cast<size_t>(item1)];
    r2 = (*ranks)[static_cast<size_t>(item2)];
}

int wxCALLBACK RankListCtrl::CompareIndexAsc(
    wxIntPtr item1,
    wxIntPtr item2,
    wxIntPtr sortData)
{
    RankItem r1, r2;
    GetRanks(item1, item2, sortData, r1, r2);
    return compareInt(r1.index, r2.index);
}

int wxCALLBACK RankListCtrl::CompareTimestampAsc(
    wxIntPtr item1,
    wxIntPtr item2,
    wxIntPtr sortData)
{
    RankItem r1, r2;
    GetRanks(item1, item2, sortData, r1, r2);
    return compareStr(r1.timestamp, r2.timestamp);
}

int wxCALLBACK RankListCtrl::CompareStatusAsc(
    wxIntPtr item1,
    wxIntPtr item2,
    wxIntPtr sortData)
{
    RankItem r1, r2;
    GetRanks(item1, item2, sortData, r1, r2);
    return compareInt(r1.status, r2.status);
}

int wxCALLBACK RankListCtrl::CompareIndexDesc(
    wxIntPtr item1,
    wxIntPtr item2,
    wxIntPtr sortData)
{
    RankItem r1, r2;
    GetRanks(item1, item2, sortData, r1, r2);
    return compareInt(r2.index, r1.index);
}

int wxCALLBACK RankListCtrl::CompareTimestampDesc(
    wxIntPtr item1,
    wxIntPtr item2,
    wxIntPtr sortData)
{
    RankItem r1, r2;
    GetRanks(item1, item2, sortData, r1, r2);
    return compareStr(r2.timestamp, r1.timestamp);
}

int wxCALLBACK RankListCtrl::CompareStatusDesc(
    wxIntPtr item1,
    wxIntPtr item2,
    wxIntPtr sortData)
{
    RankItem r1, r2;
    GetRanks(item1, item2, sortData, r1, r2);
    return compareInt(r2.status, r1.status);
}