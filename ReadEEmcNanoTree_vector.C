// Filename: ReadEEmcNanoTree.C
// Description: 
// Author: Latif Kabir < kabir@bnl.gov >
// Created: Wed Dec  4 13:09:18 2019 (-0500)
// URL: jlab.org/~latif


#include "StRoot/BrContainers/TStEventData.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <cmath>


using namespace std;

void ReadEEmcNanoTree_vector()
{
    TString filePath_eemc = "/gpfs/mnt/gpfs01/star/pwg/ananyapaul/jobOutput/Run15trans/RunEEmcNanoDstMaker_16064078.root";
    TChain *ch_eemc = new TChain("T");
    ch_eemc->Add(filePath_eemc);
    cout <<"EEmc Chain Entries: "<< ch_eemc->GetEntries()<<endl;


    TFile *file = new TFile("EEmcNanoTreeQA_16064078.root", "RECREATE");
    TStEventData *event = new TStEventData;
    TClonesArray *array_ph = new TClonesArray("EEmcParticleCandidate_t");
    TClonesArray *array_pi = new TClonesArray("EEmc2ParticleCandidate_t");
    ch_eemc->SetBranchAddress("event", &event);
    ch_eemc->SetBranchAddress("eemcPhoton", &array_ph);
    ch_eemc->SetBranchAddress("eemcPion", &array_pi);

    TH1F *phE = new TH1F("phE","phE", 100, 0, 100.0);
    TH1F *pi0M = new TH1F("pi0M","pi0M", 100, 0, 1.0);
    TH1F *pi0E = new TH1F("pi0E","pi0E", 100, 0, 100.0);
    TH1F *pi0Z = new TH1F("pi0Z","pi0Z", 100, 0, 1.0);
    TH1F *pi0D = new TH1F("pi0D","pi0D", 100, 0, 0.0);
    TH2D *pi0Pos = new TH2D("pi0Pos", "pi0Pos", 250, -250, 250, 250, -250, 250);


 
    const int Entries = ch_eemc->GetEntries();
    int sum_of_elems = 0;
    int PhotonTot = 0;
    int PionTot = 0;
    int NoOfTrig = 0;
    int TrigID = 0;
    std::vector<int> vecPhoton;
    std::vector<int> vecPion;
    std::vector<int> vecRunNum;
    std::vector<int> vecFillNum;


	ofstream outfile;
outfile.open("EEmcNanoTreeQAinfo_16064078.txt");
if (!outfile){cout<<"Error: File could not be opened"<<endl;
	exit(1);}



//outfile<<"Events"<<"\t"<<"nTrigs"<<"\t"<<"TrigID"<<"\t"<<"nPhotons"<<"\t"<<"nPions"<<"\t"<<endl;
    for(Int_t iEvent= 0; iEvent < ch_eemc->GetEntries(); ++iEvent)
    {
//      	if(iEvent % 1000 == 0)
//	    cout << "Events processed: "<< iEvent <<endl;

	 ch_eemc->GetEntry(iEvent);

	 //Access Event information
	 //	 cout << "Run number: " << event->GetRunNumber() <<endl;
	 vecRunNum.push_back(event->GetRunNumber());
	 //	 cout << "Fill number: " << event->GetFillNumber() <<endl;
	 vecFillNum.push_back(event->GetFillNumber());

	 

	 //	 cout<<" Run Number = "<<event->GetRunNumber()<<endl;

	 NoOfTrig = event->GetNtrigs();
//       	cout<<"No. of Trigs = "<<NoOfTrig<<endl;

	 for(int j=0; j<=NoOfTrig; j++){
	   TrigID = event->GetTrigger(j);
//	   cout<<"Trig ID = "<<TrigID<<endl;
	 }

	int nPhotons = array_ph->GetEntriesFast();
//	cout<<"nPhotons = "<<nPhotons<<endl;


	vecPhoton.push_back(array_ph->GetEntriesFast());

	for(int i = 0; i < nPhotons; i++)
	{
	    EEmcParticleCandidate_t *photon = (EEmcParticleCandidate_t*) array_ph->At(i);

	    phE->Fill(photon->E);
	}
	 
	int nPions = array_pi->GetEntriesFast();

//	cout<<"nPions = "<<nPions<<endl;
	


	vecPion.push_back(array_pi->GetEntriesFast());

	for(int i = 0; i < nPions; i++)
	{
	    EEmc2ParticleCandidate_t *pion = (EEmc2ParticleCandidate_t*) array_pi->At(i);

	    pi0M->Fill(pion->M);
	    pi0E->Fill(pion->E);
	    pi0Z->Fill(pion->Z);
	    pi0D->Fill(pion->D);
	    pi0Pos->Fill(pion->position.X(), pion->position.Y());
	}
	

    }

	//outfile<<iEvent<<"\t"<<NoOfTrig<<"\t"<<TrigID<<"\t"<<nPhotons<<"\t"<<nPions<<endl;	
//cout<<iEvent<<"\t"<<NoOfTrig<<"\t"<<TrigID<<"\t"<<nPhotons<<"\t"<<nPions<<endl;
		 

    for(std::vector<int>::iterator it = vecPhoton.begin(); it != vecPhoton.end(); ++it)
      PhotonTot += *it;

    for(std::vector<int>::iterator it = vecPion.begin(); it != vecPion.end(); ++it)
      PionTot += *it;


     cout<<"Total Photons = "<<PhotonTot<<endl;
     cout<<"Total Pions = "<<PionTot<<endl;

	outfile<<"Total Photons = "<<PhotonTot<<endl;
	outfile<<"Total Pions = "<<PionTot<<endl;


    file->Write();
	outfile.close();
    
}




