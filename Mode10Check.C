/*
	Mode10Check.C
	Author: Nathan Heinrich
	This is a peice of code to check the fucntion of the changes to hcana 
	to do with the inclusion of mode 10 data.
*/

static const int HGCER_MAX = 16;
static const int HGC_PMT = 4;

// Standard
Double_t hgcer_adcCounterNdata;
Double_t hgcer_adcCounter[HGCER_MAX];
Double_t hgcer_adcPulseAmpRaw[HGCER_MAX];
Double_t hgcer_adcPulseIntRaw[HGCER_MAX];
Double_t hgcer_adcPulseTimeRaw[HGCER_MAX];
Double_t hgcer_adcPulseAmp[HGCER_MAX];
Double_t hgcer_adcPulseInt[HGCER_MAX];
Double_t hgcer_adcPulseTime[HGCER_MAX];

// Mode 10
Double_t hgcer_adcSampCounterNdata;
Double_t hgcer_adcSampCounter[HGCER_MAX];
Double_t hgcer_adcSampPulseAmpRaw[HGCER_MAX];
Double_t hgcer_adcSampPulseIntRaw[HGCER_MAX];
Double_t hgcer_adcSampPulseTimeRaw[HGCER_MAX];
Double_t hgcer_adcSampPulseAmp[HGCER_MAX];
Double_t hgcer_adcSampPulseInt[HGCER_MAX];
Double_t hgcer_adcSampPulseTime[HGCER_MAX];


// multi Pmt Histos
TH2D* hgcer_PMTvPulseAmpRaw;
TH2D* hgcer_PMTvPulseIntRaw;
TH2D* hgcer_PMTvPulseTimeRaw;
TH2D* hgcer_PMTvPulseAmp;
TH2D* hgcer_PMTvPulseInt;
TH2D* hgcer_PMTvPulseTime;

TH2D* hgcer_PMTvSampPulseAmpRaw;
TH2D* hgcer_PMTvSampPulseIntRaw;
TH2D* hgcer_PMTvSampPulseTimeRaw;
TH2D* hgcer_PMTvSampPulseAmp;
TH2D* hgcer_PMTvSampPulseInt;
TH2D* hgcer_PMTvSampPulseTime;

//single pmt comparison histos
TH1D* hgcer_PulseAmpRaw[HGC_PMT];
TH1D* hgcer_PulseIntRaw[HGC_PMT];
TH1D* hgcer_PulseTimeRaw[HGC_PMT];
TH1D* hgcer_PulseAmp[HGC_PMT];
TH1D* hgcer_PulseInt[HGC_PMT];
TH1D* hgcer_PulseTime[HGC_PMT];

TH1D* hgcer_SampPulseAmpRaw[HGC_PMT];
TH1D* hgcer_SampPulseIntRaw[HGC_PMT];
TH1D* hgcer_SampPulseTimeRaw[HGC_PMT];
TH1D* hgcer_SampPulseAmp[HGC_PMT];
TH1D* hgcer_SampPulseInt[HGC_PMT];
TH1D* hgcer_SampPulseTime[HGC_PMT];


void setBranchAddresses(TTree* DataTree)
{
	// regular set
	DataTree->SetBranchAddress("Ndata.T.hgcer.adcCounter", hgcer_adcCounterNdata);
	DataTree->SetBranchAddress("T.hgcer.adcCounter", hgcer_adcCounter);
	DataTree->SetBranchAddress("T.hgcer.adcPulseAmpRaw", hgcer_adcPulseAmpRaw);
	DataTree->SetBranchAddress("T.hgcer.adcPulseIntRaw", hgcer_adcPulseIntRaw);
	DataTree->SetBranchAddress("T.hgcer.adcPulseTimeRaw", hgcer_adcPulseTimeRaw);
	DataTree->SetBranchAddress("T.hgcer.adcPulseAmp", hgcer_adcPulseAmp);
	DataTree->SetBranchAddress("T.hgcer.adcPulseInt", hgcer_adcPulseInt);
	DataTree->SetBranchAddress("T.hgcer.adcPulseTime", hgcer_adcPulseTime);
	
	// Mode 10 set
	DataTree->SetBranchAddress("Ndata.T.hgcer.adcSampCounter", hgcer_adcSampCounterNdata);
	DataTree->SetBranchAddress("T.hgcer.adcSampCounter", hgcer_adcSampCounter);
	DataTree->SetBranchAddress("T.hgcer.adcSampPulseAmpRaw", hgcer_adcSampPulseAmpRaw);
	DataTree->SetBranchAddress("T.hgcer.adcSampPulseIntRaw", hgcer_adcSampPulseIntRaw);
	DataTree->SetBranchAddress("T.hgcer.adcSampPulseTimeRaw", hgcer_adcSampPulseTimeRaw);
	DataTree->SetBranchAddress("T.hgcer.adcSampPulseAmp", hgcer_adcSampPulseAmp);
	DataTree->SetBranchAddress("T.hgcer.adcSampPulseInt", hgcer_adcSampPulseInt);
	DataTree->SetBranchAddress("T.hgcer.adcSampPulseTime", hgcer_adcSampPulseTime);
	
	return;
}

void makeHistos()
{
	// multi Pmt Histos
	hgcer_PMTvPulseAmpRaw 		= new TH2D("hgcer_PMTvPulseAmpRaw","hgcer_PMTvPulseAmpRaw", HGC_PMT, -0.5, 3.5, 1000, 0, 1000);
	hgcer_PMTvPulseIntRaw 		= new TH2D("hgcer_PMTvPulseIntRaw","hgcer_PMTvPulseIntRaw", HGC_PMT, -0.5, 3.5, 1000, 0, 1000);
	hgcer_PMTvPulseTimeRaw 		= new TH2D("hgcer_PMTvPulseTimeRaw","hgcer_PMTvPulseTimeRaw", HGC_PMT, -0.5, 3.5, 1000, 0, 1000);
	hgcer_PMTvPulseAmp 			= new TH2D("hgcer_PMTvPulseAmp","hgcer_PMTvPulseAmp", HGC_PMT, -0.5, 3.5, 1000, 0, 1000);
	hgcer_PMTvPulseInt 			= new TH2D("hgcer_PMTvPulseInt","hgcer_PMTvPulseInt", HGC_PMT, -0.5, 3.5, 1000, 0, 1000);
	hgcer_PMTvPulseTime 		= new TH2D("hgcer_PMTvPulseTime","hgcer_PMTvPulseTime", HGC_PMT, -0.5, 3.5, 1000, 0, 1000);

	hgcer_PMTvSampPulseAmpRaw 	= new TH2D("hgcer_PMTvSampPulseAmpRaw","hgcer_PMTvSampPulseAmpRaw", HGC_PMT, -0.5, 3.5, 1000, 0, 1000);
	hgcer_PMTvSampPulseIntRaw 	= new TH2D("hgcer_PMTvSampPulseIntRaw","hgcer_PMTvSampPulseIntRaw", HGC_PMT, -0.5, 3.5, 1000, 0, 1000);
	hgcer_PMTvSampPulseTimeRaw 	= new TH2D("hgcer_PMTvSampPulseTimeRaw","hgcer_PMTvSampPulseTimeRaw", HGC_PMT, -0.5, 3.5, 1000, 0, 1000);
	hgcer_PMTvSampPulseAmp 		= new TH2D("hgcer_PMTvSampPulseAmp","hgcer_PMTvSampPulseAmp", HGC_PMT, -0.5, 3.5, 1000, 0, 1000);
	hgcer_PMTvSampPulseInt 		= new TH2D("hgcer_PMTvSampPulseInt","hgcer_PMTvSampPulseInt", HGC_PMT, -0.5, 3.5, 1000, 0, 1000);
	hgcer_PMTvSampPulseTime 	= new TH2D("hgcer_PMTvSampPulseTime","hgcer_PMTvSampPulseTime", HGC_PMT, -0.5, 3.5, 1000, 0, 1000);

	//single pmt comparison histos
	for(int i = 0; i< HGC_PMT; i++)
	{
		hgcer_PulseAmpRaw[i] 	= new TH1D(Form("hgcer_PulseAmpRaw_%d", i),Form("hgcer_PulseAmpRaw_%d", i), 1000, 0, 1000);
		hgcer_PulseIntRaw[i] 	= new TH1D(Form("hgcer_PulseIntRaw_%d", i),Form("hgcer_PulseIntRaw_%d", i), 1000, 0, 1000);
		hgcer_PulseTimeRaw[i] 	= new TH1D(Form("hgcer_PulseTimeRaw_%d", i),Form("hgcer_PulseTimeRaw_%d", i), 1000, 0, 1000);
		hgcer_PulseAmp[i] 		= new TH1D(Form("hgcer_PulseAmp_%d", i),Form("hgcer_PulseAmp_%d", i), 1000, 0, 1000);
		hgcer_PulseInt[i] 		= new TH1D(Form("hgcer_PulseInt_%d", i),Form("hgcer_PulseInt_%d", i), 1000, 0, 1000);
		hgcer_PulseTime[i] 		= new TH1D(Form("hgcer_PulseTime_%d", i),Form("hgcer_PulseTime_%d", i), 1000, 0, 1000);

		hgcer_SampPulseAmpRaw[i]	= new TH1D(Form("hgcer_SampPulseAmpRaw_%d", i),Form("hgcer_SampPulseAmpRaw_%d", i), 1000, 0, 1000);
		hgcer_SampPulseIntRaw[i] 	= new TH1D(Form("hgcer_SampPulseIntRaw_%d", i),Form("hgcer_SampPulseIntRaw_%d", i), 1000, 0, 1000);
		hgcer_SampPulseTimeRaw[i] 	= new TH1D(Form("hgcer_SampPulseTimeRaw_%d", i),Form("hgcer_SampPulseTimeRaw_%d", i), 1000, 0, 1000);
		hgcer_SampPulseAmp[i] 		= new TH1D(Form("hgcer_SampPulseAmp_%d", i),Form("hgcer_SampPulseAmp_%d", i), 1000, 0, 1000);
		hgcer_SampPulseInt[i] 		= new TH1D(Form("hgcer_SampPulseInt_%d", i),Form("hgcer_SampPulseInt_%d", i), 1000, 0, 1000);
		hgcer_SampPulseTime[i] 		= new TH1D(Form("hgcer_SampPulseTime_%d", i),Form("hgcer_SampPulseTime_%d", i), 1000, 0, 1000);
	}
	return;
}

fillHistos(DataTree)
{
	Int_t MaxEvents = DataTree->GetEntries();
	cout << "Begining to fill histograms, " << MaxEvents << " events will be processed!\n";
    for(Int_t iEntry = 0; iEntry < MaxEvents; iEntry++)
    {
        DataTree->GetEntry(iEntry)
		
		//regular
		for(int i = 0; i < hgcer_adcCounterNdata; i++)
		{
			hgcer_PMTvPulseAmpRaw->Fill(hgcer_adcCounter, hgcer_adcPulseAmpRaw);
			hgcer_PMTvPulseIntRaw->Fill(hgcer_adcCounter, hgcer_adcPulseIntRaw);
			hgcer_PMTvPulseTimeRaw->Fill(hgcer_adcCounter, hgcer_adcPulseTimeRaw);
			hgcer_PMTvPulseAmp->Fill(hgcer_adcCounter, hgcer_adcPulseAmp);
			hgcer_PMTvPulseInt->Fill(hgcer_adcCounter, hgcer_adcPulseInt);
			hgcer_PMTvPulseTime->Fill(hgcer_adcCounter, hgcer_adcPulseTime);
		
			hgcer_PulseAmpRaw[hgcer_adcCounter]->Fill(hgcer_adcPulseAmpRaw);
			hgcer_PulseIntRaw[hgcer_adcCounter]->Fill(hgcer_adcPulseIntRaw);
			hgcer_PulseTimeRaw[hgcer_adcCounter]->Fill(hgcer_adcPulseTimeRaw);
			hgcer_PulseAmp[hgcer_adcCounter]->Fill(hgcer_adcPulseAmp);
			hgcer_PulseInt[hgcer_adcCounter]->Fill(hgcer_adcPulseInt);
			hgcer_PulseTime[hgcer_adcCounter]->Fill(hgcer_adcPulseTime);
		}
		
		//Mode 10
		for(int i = 0; i < hgcer_adcCounterNdata; i++)
		{
			hgcer_PMTvSampPulseAmpRaw->Fill(hgcer_adcSampCounter, hgcer_adcSampPulseAmpRaw);
			hgcer_PMTvSampPulseIntRaw->Fill(hgcer_adcSampCounter, hgcer_adcSampPulseIntRaw);
			hgcer_PMTvSampPulseTimeRaw->Fill(hgcer_adcSampCounter, hgcer_adcSampPulseTimeRaw);
			hgcer_PMTvSampPulseAmp->Fill(hgcer_adcSampCounter, hgcer_adcSampPulseAmp);
			hgcer_PMTvSampPulseInt->Fill(hgcer_adcSampCounter, hgcer_adcSampPulseInt);
			hgcer_PMTvSampPulseTime->Fill(hgcer_adcSampCounter, hgcer_adcSampPulseTime);
		
			hgcer_SampPulseAmpRaw[hgcer_adcSampCounter]->Fill(hgcer_adcSampPulseAmpRaw);
			hgcer_SampPulseIntRaw[hgcer_adcSampCounter]->Fill(hgcer_adcSampPulseIntRaw);
			hgcer_SampPulseTimeRaw[hgcer_adcSampCounter]->Fill(hgcer_adcSampPulseTimeRaw);
			hgcer_SampPulseAmp[hgcer_adcSampCounter]->Fill(hgcer_adcSampPulseAmp);
			hgcer_SampPulseInt[hgcer_adcSampCounter]->Fill(hgcer_adcSampPulseInt);
			hgcer_SampPulseTime[hgcer_adcSampCounter]->Fill(hgcer_adcSampPulseTime);
		}
	}
	return;
}



void Mode10Check (TString inFile, int runNum)
{
	//get root file
    TFile* inFile = new TFile(rootFileName, "READ");
    
    if(!inFile->IsOpen())
    {
        cout << "File did not open properly.\nCheck That: '" << rootFileName << "' exists and is not corrupted.\n --- Ending --- \n";
        return;
    }
    
    //get tree from root file
    TTree *DataTree = dynamic_cast <TTree*> (inFile->Get("T"));
    
    setBranchAddresses(DataTree);
    
    //make histograms
    makeHistos();
    
    //fill histos and apply cuts
    fillHistos(DataTree);
    
    cout << "Finished filling plots, saving output!\n";
    
    //save plots
	
	// first set of 2D plots
	TCanvas *MultiCanRaw = new TCanvas(Form("Mode10_hgcerRaw_%d", runNum),Form("Mode10_hgcerRaw_%d", runNum), 1200, 1200);
	MultiCanRaw->Divide(2,3);
	MultiCanRaw->cd(1);
	hgcer_PMTvPulseAmpRaw->Draw();
	MultiCanRaw->cd(2);
	hgcer_PMTvPulseIntRaw->Draw();
	MultiCanRaw->cd(3);
	hgcer_PMTvPulseTimeRaw->Draw();
	MultiCanRaw->cd(4);
	hgcer_PMTvSampPulseAmpRaw->Draw();
	MultiCanRaw->cd(5);
	hgcer_PMTvSampPulseIntRaw->Draw();
	MultiCanRaw->cd(6);
	hgcer_PMTvSampPulseTimeRaw->Draw();
	
	MultiCanRaw->Print(Form("Mode10_hgcerRaw_%d", runNum), "png");
	
	// second set of 2d plots
	TCanvas *MultiCan = new TCanvas(Form("Mode10_hgcer_%d", runNum),Form("Mode10_hgcer_%d", runNum), 1200, 1200);
	MultiCan->Divide(2,3);
	MultiCan->cd(1);
	hgcer_PMTvPulseAmp->Draw();
	MultiCan->cd(2);
	hgcer_PMTvPulseInt->Draw();
	MultiCan->cd(3);
	hgcer_PMTvPulseTime->Draw();
	MultiCan->cd(4);
	hgcer_PMTvSampPulseAmp->Draw();
	MultiCan->cd(5);
	hgcer_PMTvSampPulseInt->Draw();
	MultiCan->cd(6);
	hgcer_PMTvSampPulseTime->Draw();

	MultiCan->Print(Form("Mode10_hgcer_%d", runNum), "png");

	//fill the other histograms
	TCanvas *HistCan[HGC_PMT]; 
	for(int i = 0; i < HGC_PMT; i++)
	{
		HistCan[i] = new TCanvas(Form("Mode10_hgcerHist%d_%d", i, runNum),Form("Mode10_hgcerHist%d_%d", i, runNum), 1200, 1200);
		HistCan->Divide(2,3);
		HistCan->cd(1);
		hgcer_PulseAmpRaw[i]->Draw();
		hgcer_SampPulseAmpRaw[i]-Draw("SAME");
		HistCan->cd(2);
		hgcer_PulseIntRaw[i]->Draw();
		hgcer_SampPulseIntRaw[i]-Draw("SAME");
		HistCan->cd(3);
		hgcer_PulseTimeRaw[i]->Draw();
		hgcer_SampPulseTimeRaw[i]-Draw("SAME");
		HistCan->cd(4);
		hgcer_PulseAmp[i]->Draw();
		hgcer_SampPulseAmp[i]-Draw("SAME");
		HistCan->cd(5);
		hgcer_PulseInt[i]->Draw();
		hgcer_SampPulseInt[i]-Draw("SAME");
		HistCan->cd(6);
		hgcer_PulseTime[i]->Draw();
		hgcer_SampPulseTime[i]-Draw("SAME");		
		
		HistCan[i]->Print(Form("Mode10_hgcerHist%d_%d", i, runNum), "png");
	}
	
	return;
}



