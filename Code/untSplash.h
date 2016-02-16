//---------------------------------------------------------------------------

#ifndef untSplashH
#define untSplashH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Chartfx3.hpp>
#include <OleCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmSplash : public TForm
{
__published:	// IDE-managed Components
        TImage *imgSplash;
        TTimer *tmrSplash;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall tmrSplashTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmSplash(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSplash *frmSplash;
//---------------------------------------------------------------------------
#endif
