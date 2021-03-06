
#ifndef APP_RANKLISTCTRL_H
#define APP_RANKLISTCTRL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/icon.h>
#include <wx/imaglist.h>
#include <wx/listctrl.h>
#include <vector>
#include "listarrows_xpm.h"

#define RANK_COL_LABEL_INDEX "Index"
#define RANK_COL_LABEL_TIMESTAMP "Timestamp"
#define RANK_COL_LABEL_STATUS "Status"

struct RankItem
{
    wxString index;
    wxString timestamp;
    wxString status;
};

typedef std::vector<RankItem> RankList;

class RankListCtrl : public wxListCtrl
{
public:
    RankListCtrl(wxWindow *parent);
    virtual ~RankListCtrl();
    void AddRank(RankItem rank);
    int GetRankId(wxIntPtr index);
    RankItem GetRank(wxIntPtr index);
    void Reset();
    bool direction = true;

private:
    enum Columns
    {
        Column_Index = 0,
        Column_Timestamp,
        Column_Status
    };
    wxImageList *m_imageList;
    RankList m_ranks;
    size_t rankIndex = 0;
    void SetColumnImage(int col, int image);
    void OnColClick(wxListEvent &evt);
    static int compareStr(wxString a, wxString b);
    static int compareInt(wxString a, wxString b);
    static void GetRanks(
        wxIntPtr item1,
        wxIntPtr item2,
        wxIntPtr sortData,
        RankItem &r1,
        RankItem &r2);
    static int wxCALLBACK CompareIndexAsc(
        wxIntPtr item1,
        wxIntPtr item2,
        wxIntPtr sortData);
    static int wxCALLBACK CompareTimestampAsc(
        wxIntPtr item1,
        wxIntPtr item2,
        wxIntPtr sortData);
    static int wxCALLBACK CompareStatusAsc(
        wxIntPtr item1,
        wxIntPtr item2,
        wxIntPtr sortData);
    static int wxCALLBACK CompareIndexDesc(
        wxIntPtr item1,
        wxIntPtr item2,
        wxIntPtr sortData);
    static int wxCALLBACK CompareTimestampDesc(
        wxIntPtr item1,
        wxIntPtr item2,
        wxIntPtr sortData);
    static int wxCALLBACK CompareStatusDesc(
        wxIntPtr item1,
        wxIntPtr item2,
        wxIntPtr sortData);
};

#endif