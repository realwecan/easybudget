//---------------------------------------------------------------------------

#ifndef untMainH
#define untMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TListView *lsvMain;
        TGroupBox *GroupBox1;
        TDateTimePicker *edtDate;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TComboBox *edtDescription;
        TEdit *edtSum;
        TLabel *Label5;
        TEdit *edtRemark;
        TSpeedButton *btnNew;
        TSpeedButton *btnModify;
        TSpeedButton *btnReport;
        TSpeedButton *btnOptions;
        TOpenDialog *dlgOpen;
        TSaveDialog *dlgSave;
        TPopupMenu *mnuOptions;
        TMenuItem *mnuPImport;
        TMenuItem *mnuPExport;
        TPopupMenu *mnuListView;
        TMenuItem *mnuDeleteSelected;
        TMenuItem *N1;
        TMenuItem *mnuEditSelected;
        TMenuItem *mnuClear;
        TComboBoxEx *edtType;
        TImageList *istMain;
        TMenuItem *N2;
        TMenuItem *mnuPHelpTopic;
        TMenuItem *mnuPAbout;
        TMenuItem *N3;
        TMenuItem *mnuPPreferences;
        TMenuItem *mnuSelectAll;
        TLabel *Label6;
        void __fastcall btnNewClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall lsvMainDblClick(TObject *Sender);
        void __fastcall btnModifyClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall lsvMainColumnClick(TObject *Sender,
          TListColumn *Column);
        void __fastcall lsvMainCompare(TObject *Sender, TListItem *Item1,
          TListItem *Item2, int Data, int &Compare);
        void __fastcall btnReportClick(TObject *Sender);
        void __fastcall btnOptionsClick(TObject *Sender);
        void __fastcall mnuDeleteSelectedClick(TObject *Sender);
        void __fastcall mnuClearClick(TObject *Sender);
        void __fastcall mnuPImportClick(TObject *Sender);
        void __fastcall mnuPExportClick(TObject *Sender);
        void __fastcall mnuPAboutClick(TObject *Sender);
        void __fastcall mnuPPreferencesClick(TObject *Sender);
        void __fastcall mnuPHelpTopicClick(TObject *Sender);
        void __fastcall mnuSelectAllClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
