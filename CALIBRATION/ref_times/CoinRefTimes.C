
Double_t pTrig1_Roc1_Raw, pTrig1_Roc1;
Double_t pTrig1_Roc2_Raw, pTrig1_Roc2;
Double_t pTrig4_Roc1_Raw, pTrig4_Roc1;
Double_t pTrig4_Roc2_Raw, pTrig4_Roc2;
Double_t pTref2;
Double_t Cointime_ROC1_RAW, Cointime_ROC2_RAW, Ctime_ePi_Roc1, Ctime_ePi_Roc2;
Double_t MMpi;
Double_t bcm;
Double_t Paero, Hcal, Hcer;

TH1D *pTRIG1_ROC1_tdcTimeRaw, *pTRIG1_ROC1_tdcTime;
TH1D *pTRIG1_ROC2_tdcTimeRaw, *pTRIG1_ROC2_tdcTime;

TH1D *pTRIG4_ROC1_tdcTimeRaw, *pTRIG4_ROC1_tdcTime;
TH1D *pTRIG4_ROC2_tdcTimeRaw, *pTRIG4_ROC2_tdcTime;

TH1D *pT2_tdcTimeRaw;

TH1D *CoinTime_RAW_ROC1, *CoinTime_RAW_ROC2;
TH1D *ePiCoinTime_ROC1, *ePiCoinTime_ROC2;

TH1D *MMpi_hist;

void fillHistos(TTree *DataTree)
{
    Int_t MaxEvents = DataTree->GetEntries();
    cout << "Begining to fill histograms, " << MaxEvents << " events will be processed!\n";
    int coinCounter = 0;
    int coinCounter2 = 0;
    int PidCounter = 0;
    for(Int_t iEntry = 0; iEntry < MaxEvents; iEntry++)
    {
        DataTree->GetEntry(iEntry);
        
        if( iEntry % 10000 == 0 ) cout << iEntry << "\n"; //status report
        
        pTRIG1_ROC1_tdcTimeRaw->Fill(pTrig1_Roc1_Raw);
        pTRIG1_ROC2_tdcTimeRaw->Fill(pTrig1_Roc2_Raw);
        
        pTRIG4_ROC1_tdcTimeRaw->Fill(pTrig4_Roc1_Raw);
        pTRIG4_ROC2_tdcTimeRaw->Fill(pTrig4_Roc2_Raw);
        
        pTRIG1_ROC1_tdcTime->Fill(pTrig1_Roc1);
        pTRIG1_ROC2_tdcTime->Fill(pTrig1_Roc2);
        
        pTRIG4_ROC1_tdcTime->Fill(pTrig4_Roc1);
        pTRIG4_ROC2_tdcTime->Fill(pTrig4_Roc2);
        
        pT2_tdcTimeRaw->Fill(pTref2);
        
        CoinTime_RAW_ROC1->Fill(Cointime_ROC1_RAW);
        CoinTime_RAW_ROC2->Fill(Cointime_ROC2_RAW);
        
        ePiCoinTime_ROC1->Fill(Ctime_ePi_Roc1);
        ePiCoinTime_ROC2->Fill(Ctime_ePi_Roc2);
        
        if((Cointime_ROC2_RAW > 150) & (Cointime_ROC2_RAW < 400))
        {
            MMpi_hist->Fill(MMpi);
        }
        
        if((Ctime_ePi_Roc1 > ((0)-((2.004)/2.0)-(0.25))) & (Ctime_ePi_Roc1 < ((0)+((2.004)/2.0)+(0.25))))
        {
            coinCounter++;
            if (abs(bcm - 70) < 10.0)
            {
                coinCounter2++;
                if ((Paero > 1.5) & (Hcal > 0.7) & (Hcer > 0.3))
                {
                    PidCounter++;
                }
            }
        }
        
    }
    cout << "inside Coin Cut: " << coinCounter;
    cout << "\ninside bcm and coin cut: " << coinCounter2<< endl;
    cout << "PID counter: " << PidCounter << endl;
    return;
}

void CoinRefTimes( TString rootFileName, Int_t RunNumber)
{
    gROOT->SetBatch(kTRUE);
    //get root file
    TFile* inFile = new TFile(rootFileName, "READ");
    
    if(!inFile->IsOpen())
    {
        cout << "File did not open properly.\nCheck That: '" << rootFileName << "' exists and is not corrupted.\n --- Ending --- \n";
        return;
    }
    
    
    //get tree from root file
    TTree *DataTree = dynamic_cast <TTree*> (inFile->Get("T"));
    
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC1_tdcTimeRaw", &pTrig1_Roc1_Raw);
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC1_tdcTime", &pTrig1_Roc1);
    
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTimeRaw", &pTrig1_Roc2_Raw);
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTime", &pTrig1_Roc2);
    
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcTimeRaw", &pTrig1_Roc2_Raw);
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcTime", &pTrig1_Roc2);
    
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC1_tdcTimeRaw", &pTrig4_Roc1_Raw);
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC1_tdcTime", &pTrig4_Roc1);
    
    DataTree->SetBranchAddress("T.coin.pT2_tdcTimeRaw", &pTref2);
    
    DataTree->SetBranchAddress("CTime.CoinTime_RAW_ROC1", &Cointime_ROC1_RAW);
    DataTree->SetBranchAddress("CTime.CoinTime_RAW_ROC2", &Cointime_ROC2_RAW);
    DataTree->SetBranchAddress("CTime.ePiCoinTime_ROC1", &Ctime_ePi_Roc1);
    DataTree->SetBranchAddress("CTime.ePiCoinTime_ROC2", &Ctime_ePi_Roc2);
    
    DataTree->SetBranchAddress("P.kin.secondary.MMpi", &MMpi);
    
    DataTree->SetBranchAddress("H.bcm.bcm2.AvgCurrent", &bcm);
    DataTree->SetBranchAddress("P.aero.npeSum", &Paero);
    DataTree->SetBranchAddress("H.cal.etottracknorm", &Hcal);
    DataTree->SetBranchAddress("H.cer.npeSum", &Hcer);
    
    pTRIG1_ROC1_tdcTimeRaw = new TH1D("T.coin.pTRIG1_ROC1_tdcTimeRaw","T.coin.pTRIG1_ROC1_tdcTimeRaw",5000, 0, 10000);
    pTRIG4_ROC1_tdcTimeRaw = new TH1D("T.coin.pTRIG4_ROC1_tdcTimeRaw","T.coin.pTRIG4_ROC1_tdcTimeRaw",5000, 0, 10000);
    pTRIG1_ROC2_tdcTimeRaw = new TH1D("T.coin.pTRIG1_ROC2_tdcTimeRaw","T.coin.pTRIG1_ROC2_tdcTimeRaw",5000, 0, 10000);
    pTRIG4_ROC2_tdcTimeRaw = new TH1D("T.coin.pTRIG4_ROC2_tdcTimeRaw","T.coin.pTRIG4_ROC2_tdcTimeRaw",5000, 0, 10000);
    
    pTRIG1_ROC1_tdcTime = new TH1D("T.coin.pTRIG1_ROC1_tdcTime","T.coin.pTRIG1_ROC1_tdcTime",1000, -1000, 1000);
    pTRIG4_ROC1_tdcTime = new TH1D("T.coin.pTRIG4_ROC1_tdcTime","T.coin.pTRIG4_ROC1_tdcTime",1000, -1000, 1000);
    pTRIG1_ROC2_tdcTime = new TH1D("T.coin.pTRIG1_ROC2_tdcTime","T.coin.pTRIG1_ROC2_tdcTime",1000, -1000, 1000);
    pTRIG4_ROC2_tdcTime = new TH1D("T.coin.pTRIG4_ROC2_tdcTime","T.coin.pTRIG4_ROC2_tdcTime",1000, -1000, 1000);
    
    pT2_tdcTimeRaw = new TH1D("T.coin.pT2_tdcTimeRaw","T.coin.pT2_tdcTimeRaw",5000, 0, 10000);
    
    CoinTime_RAW_ROC1 = new TH1D("CTime.CoinTime_RAW_ROC1","CTime.CoinTime_RAW_ROC1",50,-25,25);
    CoinTime_RAW_ROC2 = new TH1D("CTime.CoinTime_RAW_ROC2","CTime.CoinTime_RAW_ROC2",50,-25,25);
    
    ePiCoinTime_ROC1 = new TH1D("CTime.ePiCoinTime_ROC1","CTime.ePiCoinTime_ROC1",1000,-1000,1000);
    ePiCoinTime_ROC2 = new TH1D("CTime.ePiCoinTime_ROC2","CTime.ePiCoinTime_ROC2",1000,-1000,1000);
    
    MMpi_hist = new TH1D("MMpi{150<CTime.CoinTime_RAW_ROC2<400}", "MMpi{150<CTime.CoinTime_RAW_ROC2<400}", 100,0,1.5);
    
    fillHistos(DataTree);
    
    //write histogrames to pdf
    TCanvas* canvas = new TCanvas("PDFOutput", "PDFOutput", 600, 600);
    gPad->SetLogy();
    
    pTRIG1_ROC1_tdcTimeRaw->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf(",RunNumber),  pTRIG1_ROC1_tdcTimeRaw->GetName());
    pTRIG1_ROC2_tdcTimeRaw->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG1_ROC2_tdcTimeRaw->GetName());
    pTRIG4_ROC1_tdcTimeRaw->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG4_ROC1_tdcTimeRaw->GetName());
    pTRIG4_ROC2_tdcTimeRaw->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG4_ROC2_tdcTimeRaw->GetName());
    
    pTRIG1_ROC1_tdcTime->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG1_ROC1_tdcTime->GetName());
    pTRIG1_ROC2_tdcTime->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG1_ROC2_tdcTime->GetName());
    pTRIG4_ROC1_tdcTime->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG4_ROC1_tdcTime->GetName());
    pTRIG4_ROC2_tdcTime->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG4_ROC2_tdcTime->GetName());
    
    pT2_tdcTimeRaw->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pT2_tdcTimeRaw->GetName());
    
    CoinTime_RAW_ROC1->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  CoinTime_RAW_ROC1->GetName());
    CoinTime_RAW_ROC2->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  CoinTime_RAW_ROC2->GetName());
    
    ePiCoinTime_ROC1->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  ePiCoinTime_ROC1->GetName());
    ePiCoinTime_ROC2->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  ePiCoinTime_ROC2->GetName());
    
    MMpi_hist->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf)",RunNumber),  ePiCoinTime_ROC2->GetName());
}


        
        
        
        
        
        
