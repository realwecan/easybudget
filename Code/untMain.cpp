//---------------------------------------------------------------------------

#include <vcl.h>
#include <StrUtils.hpp> 
#pragma hdrstop

#include "untMain.h"
#include "untReport.h"
#include "untSplash.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
char Strsum[10];
int ColumnToSort = 0;
bool IsAscSort = false;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


int CheckSumInput()
{
  try {
    strcpy( Strsum , FloatToStrF(StrToFloat(frmMain->edtSum->Text),ffFixed,7,2).c_str() );
  }
  catch ( ... )
  {
    MessageDlg("您输入的金额不合法，应当以“16.8”这样的纯数字形式输入金额。",mtError,TMsgDlgButtons() << mbOK,0);
    return(0); //false
  }
  if ( StrToFloat(frmMain->edtSum->Text) == 0 ) {
    MessageDlg("您输入的金额为零，请重新输入。",mtError,TMsgDlgButtons() << mbOK,0);
    return(0); //false
  }
  return(1); //true
}
//---------------------------------------------------------------------------


void SaveData(AnsiString filename)
{
  int i;
  TStringList *savelist = new TStringList;
  for (i=0;i<frmMain->lsvMain->Items->Count;i++) {
    savelist->Add( frmMain->lsvMain->Items->Item[i]->Caption );
    savelist->Add( frmMain->lsvMain->Items->Item[i]->SubItems->Strings[0] );
    savelist->Add( frmMain->lsvMain->Items->Item[i]->SubItems->Strings[1] );
    savelist->Add( frmMain->lsvMain->Items->Item[i]->SubItems->Strings[2] );
    savelist->Add( frmMain->lsvMain->Items->Item[i]->SubItems->Strings[3] );
  }
  savelist->SaveToFile(filename);
  delete savelist;
}
//---------------------------------------------------------------------------


void LoadData(AnsiString filename)
{
  int i;
  TListItem *Item;
  
  TStringList *loadlist = new TStringList;

  frmMain->lsvMain->Clear();

  loadlist->LoadFromFile(filename);
  for ( i=0 ; i < ( loadlist->Count / 5 ) ; i++ ) {
    Item = frmMain->lsvMain->Items->Add();
    Item->Caption = loadlist->Strings[5*i];
    Item->SubItems->Add(loadlist->Strings[5*i+1]);
    Item->SubItems->Add(loadlist->Strings[5*i+2]);
    Item->SubItems->Add(loadlist->Strings[5*i+3]);
    Item->SubItems->Add(loadlist->Strings[5*i+4]);  
  }
  
  delete loadlist;
}
//---------------------------------------------------------------------------


AnsiString ExtractYearMonth(AnsiString fulldate)
{
  if ( RightStr(LeftStr(fulldate,7),1) == "-" )
    return LeftStr(fulldate,6);
  return LeftStr(fulldate,7);
}
//---------------------------------------------------------------------------


void MakeReport_MonthlyOut()
{
  AnsiString curdate;
  int i;
  float value=0;

  frmReport->srsMonthlyOut->Clear();

  {
    IsAscSort = true;
    ColumnToSort = 0;
    frmMain->lsvMain->AlphaSort();
  } //Sort by Date, Ascending

  curdate = ExtractYearMonth(frmMain->lsvMain->Items->Item[0]->Caption);
  //use curdate to check whether the next date has arrived

  for (i=0;i<frmMain->lsvMain->Items->Count;i++) {
    if ( frmMain->lsvMain->Items->Item[i]->SubItems->Strings[1] == "I、收入" )
      continue;
    if ( ExtractYearMonth(frmMain->lsvMain->Items->Item[i]->Caption) != curdate ) {
      if ( value > 0 )
        frmReport->srsMonthlyOut->Add(value,curdate,clTeeColor);
      curdate = ExtractYearMonth(frmMain->lsvMain->Items->Item[i]->Caption);
      value=0;
    }
    value += StrToFloat( frmMain->lsvMain->Items->Item[i]->SubItems->Strings[2] );
  }
  frmReport->srsMonthlyOut->Add(value,curdate,clTeeColor); //last date
}
//---------------------------------------------------------------------------


void MakeReport_MonthlyIn()
{
  AnsiString curdate;
  int i;
  float value=0;

  frmReport->srsMonthlyIn->Clear();

  {
    IsAscSort = true;
    ColumnToSort = 0;
    frmMain->lsvMain->AlphaSort();
  } //Sort by Date, Ascending

  curdate = ExtractYearMonth(frmMain->lsvMain->Items->Item[0]->Caption);
  //use curdate to check whether the next date has arrived

  for (i=0;i<frmMain->lsvMain->Items->Count;i++) {
    if ( frmMain->lsvMain->Items->Item[i]->SubItems->Strings[1] != "I、收入" )
      continue;
    if ( ExtractYearMonth(frmMain->lsvMain->Items->Item[i]->Caption) != curdate ) {
      if ( value > 0 )
        frmReport->srsMonthlyIn->Add(value,curdate,clTeeColor);
      curdate = ExtractYearMonth(frmMain->lsvMain->Items->Item[i]->Caption);
      value=0;
    }
    value += StrToFloat( frmMain->lsvMain->Items->Item[i]->SubItems->Strings[2] );
  }
  frmReport->srsMonthlyIn->Add(value,curdate,clTeeColor); //last date
}
//---------------------------------------------------------------------------


void MakeReport_TypeOut()
{
  AnsiString curtype;
  int i=0;
  float value=0;

  frmReport->srsTypeOut->Clear();

  {
    IsAscSort = true;
    ColumnToSort = 2;
    frmMain->lsvMain->AlphaSort();
  } //Sort by Type, Ascending

  while (frmMain->lsvMain->Items->Item[i]->SubItems->Strings[1] == "I、收入")
    i++; //Skip incomings in the front

  curtype = frmMain->lsvMain->Items->Item[i]->SubItems->Strings[1];
  //use curtype to check whether the next type has arrived

  for (;i<frmMain->lsvMain->Items->Count;i++) {
    if ( frmMain->lsvMain->Items->Item[i]->SubItems->Strings[1] == "I、收入" )
      continue;
    if (frmMain->lsvMain->Items->Item[i]->SubItems->Strings[1] != curtype ) {
      frmReport->srsTypeOut->Add(value,curtype,clTeeColor);
      curtype = frmMain->lsvMain->Items->Item[i]->SubItems->Strings[1];
      value=0;
    }
    value += StrToFloat( frmMain->lsvMain->Items->Item[i]->SubItems->Strings[2] );
  }
  frmReport->srsTypeOut->Add(value,curtype,clTeeColor); //last type
}
//---------------------------------------------------------------------------


void MakeReports()
{
  SaveData( ExtractFilePath(Application->ExeName) + "temp.dat" );
  {
    int i;
    for (i=0;i<frmMain->lsvMain->Items->Count;i++)
      frmMain->lsvMain->Items->Item[i]->Selected = ( !frmMain->lsvMain->Items->Item[i]->Selected );
    frmMain->lsvMain->DeleteSelected();
  } //Delete Un-selected items
  MakeReport_MonthlyOut();
  MakeReport_MonthlyIn();
  MakeReport_TypeOut();
  //any report(s) else....
  LoadData( ExtractFilePath(Application->ExeName) + "temp.dat" );
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btnNewClick(TObject *Sender)
{
  TListItem *Item;
  if (CheckSumInput() == true) {
    Item = lsvMain->Items->Add();
    Item->Caption = DateToStr(edtDate->Date); //DateToStr() cuts Time from Date
    Item->SubItems->Add(edtDescription->Text);
    Item->SubItems->Add(edtType->ItemsEx->Items[edtType->ItemIndex]->Caption);
    Item->SubItems->Add(Strsum);
    Item->SubItems->Add(edtRemark->Text);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
  edtDate->Date = Date();
  edtType->ItemIndex = 0;
  if (FileExists( ExtractFilePath(Application->ExeName) + "default.dat" ))
    LoadData( ExtractFilePath(Application->ExeName) + "default.dat" );
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::lsvMainDblClick(TObject *Sender)
{
  //check first if Selected <> nil
  if (lsvMain->ItemIndex >= 0) {
    edtDate->Date = StrToDate(lsvMain->Selected->Caption);
    edtDescription->Text = lsvMain->Selected->SubItems->Strings[0];
    edtType->ItemIndex = *(lsvMain->Selected->SubItems->Strings[1].c_str()) - 65;
    /*When need a char* type from AnsiString, use AnsiStringType.c_str() to get
    a char* pointer, and do the rest just like in C. */
    edtSum->Text = lsvMain->Selected->SubItems->Strings[2];
    edtRemark->Text = lsvMain->Selected->SubItems->Strings[3];
  }        
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btnModifyClick(TObject *Sender)
{
  if (CheckSumInput() == true) {
    lsvMain->Selected->Caption = DateToStr(edtDate->Date);
    lsvMain->Selected->SubItems->Strings[0] = edtDescription->Text;
    lsvMain->Selected->SubItems->Strings[1] = edtType->ItemsEx->Items[edtType->ItemIndex]->Caption;
    lsvMain->Selected->SubItems->Strings[2] = Strsum;
    lsvMain->Selected->SubItems->Strings[3] = edtRemark->Text;
  }
}
//---------------------------------------------------------------------------




void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
  SaveData( ExtractFilePath(Application->ExeName) + "default.dat" );
  frmSplash->Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::lsvMainColumnClick(TObject *Sender,
      TListColumn *Column)
{
  IsAscSort = !IsAscSort ;
  ColumnToSort = Column->Index;
  ((TCustomListView *)Sender)->AlphaSort();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::lsvMainCompare(TObject *Sender, TListItem *Item1,
      TListItem *Item2, int Data, int &Compare)
{
  if (ColumnToSort == 0) {
    if (IsAscSort)
      Compare = CompareText(Item1->Caption,Item2->Caption);
    else
      Compare = CompareText(Item2->Caption,Item1->Caption);
  }
  else {
    int ix = ColumnToSort - 1;
    if (IsAscSort)
      Compare = CompareText(Item1->SubItems->Strings[ix], Item2->SubItems->Strings[ix]);
    else
      Compare = CompareText(Item2->SubItems->Strings[ix], Item1->SubItems->Strings[ix]);
  }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btnReportClick(TObject *Sender)
{
  if (lsvMain->ItemIndex >= 0) {
    frmReport->Show();
    MakeReports();
  }
  else
    MessageDlg("生成报告前，必须选中要在报告中包含的条目。详情请参阅帮助文件。",mtError,TMsgDlgButtons() << mbOK,0);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btnOptionsClick(TObject *Sender)
{
  mnuOptions->Popup(Mouse->CursorPos.x,Mouse->CursorPos.y);         
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::mnuDeleteSelectedClick(TObject *Sender)
{
  lsvMain->DeleteSelected();        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuClearClick(TObject *Sender)
{
  if ( ( MessageDlg("即将删除所有条目，未保存的数据将全部丢失。是否继续？",mtConfirmation,TMsgDlgButtons() << mbYes << mbNo,0) ) == mrYes )
    lsvMain->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuPImportClick(TObject *Sender)
{
  if ( ( MessageDlg("如果导入数据自文件，当前未保存的数据将全部丢失。是否继续？",mtConfirmation,TMsgDlgButtons() << mbYes << mbNo,0) ) == mrYes ) {
    dlgOpen->Execute();
    if (ExtractFileName(dlgOpen->FileName) != "")
      LoadData(dlgOpen->FileName);
  }        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuPExportClick(TObject *Sender)
{
  dlgSave->Execute();
  if (ExtractFileName(dlgOpen->FileName) != "")
    SaveData(dlgSave->FileName);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuPAboutClick(TObject *Sender)
{
  MessageDlg("EasyBudget - 大学生日常收支管理软件 - 版本 0.1 SCUT Release - Copyleft(C)2006 by Wecan - http://wecan.name",mtInformation,TMsgDlgButtons() << mbOK,0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuPPreferencesClick(TObject *Sender)
{
  MessageDlg("该版本的首选项不可用，请关注 http://wecan.name 以获取最新的升级版本。",mtInformation,TMsgDlgButtons() << mbOK,0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuPHelpTopicClick(TObject *Sender)
{
  MessageDlg("该版本的联机帮助不可用，请关注 http://wecan.name 以获取最新的升级版本。",mtInformation,TMsgDlgButtons() << mbOK,0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuSelectAllClick(TObject *Sender)
{
  lsvMain->SelectAll();        
}
//---------------------------------------------------------------------------

