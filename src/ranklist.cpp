
#include "ranklist.h"

RankListCtrl::RankListCtrl(wxWindow *parent) : wxListCtrl(
                                                   parent,
                                                   wxID_ANY,
                                                   wxDefaultPosition,
                                                   wxDefaultSize,
                                                   wxLC_REPORT)
{
    InsertColumn(Column_Index, _(RANK_COL_LABEL_INDEX));
    SetColumnWidth(Column_Index, wxLIST_AUTOSIZE_USEHEADER);
    InsertColumn(Column_Timestamp, _(RANK_COL_LABEL_TIMESTAMP));
    SetColumnWidth(Column_Timestamp, wxLIST_AUTOSIZE_USEHEADER);
    InsertColumn(Column_Status, _(RANK_COL_LABEL_STATUS));
    SetColumnWidth(Column_Status, wxLIST_AUTOSIZE_USEHEADER);
    Bind(wxEVT_LIST_COL_CLICK, &RankListCtrl::OnColClick, this);
}

void RankListCtrl::AddRank(RankItem r)
{
    r.index = wxString::Format(wxT("%zu"), rankIndex);
    long result = InsertItem(rankIndex, r.index);
    SetItem(result, Column_Timestamp, r.timestamp);
    SetItem(result, Column_Status, r.status);
    SetItemData(result, (long)rankIndex);
    m_ranks.push_back(r);
    rankIndex++;
}

void RankListCtrl::Reset()
{
    m_ranks.clear();
    this->DeleteAllItems();
    rankIndex = 0;
}

void RankListCtrl::OnColClick(wxListEvent &evt)
{
    int column = evt.GetColumn();
    direction = !direction;
    if (column < 0)
        return;
    if (direction)
        switch (column)
        {
        case Column_Index:
            SortItems(CompareIndexAsc, reinterpret_cast<wxIntPtr>(&m_ranks));
            break;
        case Column_Timestamp:
            SortItems(CompareTimestampAsc, reinterpret_cast<wxIntPtr>(&m_ranks));
            break;
        case Column_Status:
            SortItems(CompareStatusAsc, reinterpret_cast<wxIntPtr>(&m_ranks));
            break;
        default:
            wxFAIL;
        }
    else
        switch (column)
        {
        case Column_Index:
            SortItems(CompareIndexDesc, reinterpret_cast<wxIntPtr>(&m_ranks));
            break;
        case Column_Timestamp:
            SortItems(CompareTimestampDesc, reinterpret_cast<wxIntPtr>(&m_ranks));
            break;
        case Column_Status:
            SortItems(CompareStatusDesc, reinterpret_cast<wxIntPtr>(&m_ranks));
            break;
        default:
            wxFAIL;
        }
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
    return r1.index.CmpNoCase(r2.index);
}

int wxCALLBACK RankListCtrl::CompareTimestampAsc(
    wxIntPtr item1,
    wxIntPtr item2,
    wxIntPtr sortData)
{
    RankItem r1, r2;
    GetRanks(item1, item2, sortData, r1, r2);
    return r1.timestamp.CmpNoCase(r2.timestamp);
}

int wxCALLBACK RankListCtrl::CompareStatusAsc(
    wxIntPtr item1,
    wxIntPtr item2,
    wxIntPtr sortData)
{
    RankItem r1, r2;
    GetRanks(item1, item2, sortData, r1, r2);
    return r1.status.CmpNoCase(r2.status);
}

int wxCALLBACK RankListCtrl::CompareIndexDesc(
    wxIntPtr item1,
    wxIntPtr item2,
    wxIntPtr sortData)
{
    RankItem r1, r2;
    GetRanks(item1, item2, sortData, r1, r2);
    return r2.index.CmpNoCase(r1.index);
}

int wxCALLBACK RankListCtrl::CompareTimestampDesc(
    wxIntPtr item1,
    wxIntPtr item2,
    wxIntPtr sortData)
{
    RankItem r1, r2;
    GetRanks(item1, item2, sortData, r1, r2);
    return r2.timestamp.CmpNoCase(r1.timestamp);
}

int wxCALLBACK RankListCtrl::CompareStatusDesc(
    wxIntPtr item1,
    wxIntPtr item2,
    wxIntPtr sortData)
{
    RankItem r1, r2;
    GetRanks(item1, item2, sortData, r1, r2);
    return r2.status.CmpNoCase(r1.status);
}