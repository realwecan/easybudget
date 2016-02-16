//---------------------------------------------------------------------------

#ifndef untReportH
#define untReportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmReport : public TForm
{
__published:	// IDE-managed Components
        TPageControl *pgeReport;
        TTabSheet *tabMonthlyOut;
        TChart *chtMonthlyOut;
        TBarSeries *srsMonthlyOut;
        TTabSheet *tabMonthlyIn;
        TChart *chtMonthlyIn;
        TBarSeries *srsMonthlyIn;
        TTabSheet *tabTypeOut;
        TChart *chtTypeOut;
        TPieSeries *srsTypeOut;
        TLabel *Label1;
private:	// User declarations
public:		// User declarations
        __fastcall TfrmReport(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmReport *frmReport;
//---------------------------------------------------------------------------
#endif
