//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "untSplash.h"
#include "untMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSplash *frmSplash;
//---------------------------------------------------------------------------
__fastcall TfrmSplash::TfrmSplash(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSplash::FormCreate(TObject *Sender)
{
  frmSplash->Height = imgSplash->Height;
  frmSplash->Width = imgSplash->Width;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSplash::tmrSplashTimer(TObject *Sender)
{
  frmMain->Show();
  frmSplash->Hide();
  tmrSplash->Enabled = false;
}
//---------------------------------------------------------------------------
