//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: openresourcedialogbase.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef _CODELITE_PLUGIN_OPENRESOURCEDIALOGBASE_BASE_CLASSES_H
#define _CODELITE_PLUGIN_OPENRESOURCEDIALOGBASE_BASE_CLASSES_H

// clang-format off
#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/dialog.h>
#include <wx/iconbndl.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include "clThemedTextCtrl.hpp"
#include <wx/dataview.h>
#include "clThemedListCtrl.h"
#include <wx/checkbox.h>
#include <wx/button.h>
#if wxVERSION_NUMBER >= 2900
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/persist/bookctrl.h>
#include <wx/persist/treebook.h>
#endif

#ifdef WXC_FROM_DIP
#undef WXC_FROM_DIP
#endif
#if wxVERSION_NUMBER >= 3100
#define WXC_FROM_DIP(x) wxWindow::FromDIP(x, NULL)
#else
#define WXC_FROM_DIP(x) x
#endif

// clang-format on

class OpenResourceDialogBase : public wxDialog
{
protected:
    clThemedTextCtrl* m_textCtrlResourceName;
    clThemedListCtrl* m_dataview;
    wxCheckBox* m_checkBoxFiles;
    wxCheckBox* m_checkBoxShowSymbols;
    wxStdDialogButtonSizer* m_stdBtnSizer2;
    wxButton* m_buttonOK;
    wxButton* m_button6;

protected:
    virtual void OnKeyDown(wxKeyEvent& event) { event.Skip(); }
    virtual void OnText(wxCommandEvent& event) { event.Skip(); }
    virtual void OnEnter(wxCommandEvent& event) { event.Skip(); }
    virtual void OnEntrySelected(wxDataViewEvent& event) { event.Skip(); }
    virtual void OnEntryActivated(wxDataViewEvent& event) { event.Skip(); }
    virtual void OnCheckboxfilesCheckboxClicked(wxCommandEvent& event) { event.Skip(); }
    virtual void OnCheckboxshowsymbolsCheckboxClicked(wxCommandEvent& event) { event.Skip(); }
    virtual void OnOK(wxCommandEvent& event) { event.Skip(); }
    virtual void OnOKUI(wxUpdateUIEvent& event) { event.Skip(); }

public:
    clThemedTextCtrl* GetTextCtrlResourceName() { return m_textCtrlResourceName; }
    clThemedListCtrl* GetDataview() { return m_dataview; }
    wxCheckBox* GetCheckBoxFiles() { return m_checkBoxFiles; }
    wxCheckBox* GetCheckBoxShowSymbols() { return m_checkBoxShowSymbols; }
    OpenResourceDialogBase(wxWindow* parent,
                           wxWindowID id = wxID_ANY,
                           const wxString& title = _("Open Resource"),
                           const wxPoint& pos = wxDefaultPosition,
                           const wxSize& size = wxSize(-1, -1),
                           long style = wxCAPTION | wxRESIZE_BORDER);
    virtual ~OpenResourceDialogBase();
};

#endif
