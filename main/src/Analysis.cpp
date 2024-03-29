#include <array>
#include <iomanip>
#include <iostream>

#include "../include/Headers.hpp"
#include "../include/Particle.hpp"
#include "../include/ParticleType.hpp"
#include "../include/ResonanceType.hpp"
#include "TApplication.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TMath.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TRint.h"
#include "TStyle.h"
#include "TSystem.h"

// Draw with Plain style in ROOT
void SetStyle() {
  gROOT->SetStyle("Default");
  gStyle->SetOptStat(1122);
  gStyle->SetOptFit(1111);
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(1);
}

void analysis() {
  // Loading old ROOT File
  TFile *file = new TFile("/home/chiara/lab_2/main/simulations.root", "READ");
  // Creating ROOT File
  TFile *file2 = new TFile("/home/chiara/lab_2/main/analysis.root", "RECREATE");

  // Reading histograms in ROOT File
  TH1F *h1 = (TH1F *)file->Get("HistoParticles");
  TH1F *h2 = (TH1F *)file->Get("HistoPolarAngles");
  TH1F *h3 = (TH1F *)file->Get("HistoAzimuthalAngles");
  TH1F *h4 = (TH1F *)file->Get("HistoP");
  TH1F *h5 = (TH1F *)file->Get("HistoPTransversal");
  TH1F *h6 = (TH1F *)file->Get("HistoEnergy");
  TH1F *h7 = (TH1F *)file->Get("HistoInvMass_conc");
  TH1F *h8 = (TH1F *)file->Get("HistoInvMass_disc");
  TH1F *h9 = (TH1F *)file->Get("HistoInvMass_PionKaon_conc");
  TH1F *h10 = (TH1F *)file->Get("HistoInvMass_PionKaon_disc");
  TH1F *h11 = (TH1F *)file->Get("HistoInvMass_dec");
 
  // Creating Canvas
  TCanvas *c1 = new TCanvas("c1", "Particle Distribution", 200, 10, 900, 500);
  c1->Divide(2, 2);
  TCanvas *c2 = new TCanvas("c2", "Impulse", 200, 10, 900, 500);
  c2->Divide(1, 2);
  TCanvas *c3 = new TCanvas("c3", "Energy", 200, 10, 900, 500);
  TCanvas *c4 = new TCanvas("c4", "Invariant Mass", 200, 10, 900, 500);
  c4->Divide(2, 2);
  TCanvas *c5 = new TCanvas("c5", "Invariant Mass Decayed Particles", 200, 10, 900, 500);
  TCanvas *c6 = new TCanvas("c6", "1st Difference", 200, 10, 900, 500);
  TCanvas *c7 = new TCanvas("c7", "2nd Difference", 200, 10, 900, 500);

  // Creating functions for fitting
  TF1 *f1 = new TF1(" funiform1 ", " pol0 ", 0.,  TMath ::Pi());
  TF1 *f2 = new TF1(" funiform2 ", " pol0 ", 0., 2 * TMath ::Pi());
  TF1 *f3 = new TF1(" fexpo ", " expo ", 0., 10.);
  TF1 *f4 = new TF1(" fgaus1 ", " gaus ", 0.3, 1.5);
  TF1 *f5 = new TF1(" fgaus2 ", " gaus ", 0.6, 1.2);
  TF1 *f6 = new TF1(" fgaus3 ", " gaus ", 0.6, 1.2);

  // Creating histograms of differences using copy constructor
  TH1F *hDiff1 = new TH1F(*h8);
  TH1F *hDiff2 = new TH1F(*h10);

  hDiff1->SetTitle("Difference between invariant mass of particles with discordant and concordant charge");
  hDiff2->SetTitle("Difference between invariant mass of discordant and concordant Pion-Kaon pairs");
  hDiff1->Add(h8, h7, 1, -1);
  hDiff2->Add(h10, h9, 1, -1);
  // Creating array that contains all TH1F histograms
  std::array<TH1F *, 13> histos{h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11, hDiff1, hDiff2};

  // Setting parameters
  double const kMass{0.89166};
  double const kWidth{0.050};
  f1->SetParameter(0, 1e4);
  f2->SetParameter(0, 1e4);
  f3->SetParameters(0, -1);
  f4->SetParameter(1, kMass);
  f4->SetParameter(2, kWidth);
  f5->SetParameter(1, kMass);
  f5->SetParameter(2, kWidth);
  f6->SetParameter(1, kMass);
  f6->SetParameter(2, kWidth);

  // Setting parameters names
  f1->SetParNames(" Constant ");
  f2->SetParNames(" Constant ");
  f3->SetParNames(" Constant ", " Tau ");
  f4->SetParNames(" Constant ", " MassK *", " WidthK *");
  f5->SetParNames(" Constant ", " MassK *", " WidthK *");
  f6->SetParNames(" Constant ", " MassK *", " WidthK *");

  // Cosmetics
  f1->SetLineColor(kYellow);
  f2->SetLineColor(kYellow);
  f3->SetLineColor(kRed);
  f4->SetLineColor(kRed);
  f5->SetLineColor(kRed);
  f6->SetLineColor(kRed);
  f1->SetLineWidth(3);
  f2->SetLineWidth(3);
  f3->SetLineWidth(3);
  f4->SetLineWidth(3);
  f5->SetLineWidth(3);
  f6->SetLineWidth(3);
  f1->SetLineStyle(2);
  f2->SetLineStyle(2);
  f3->SetLineStyle(2);
  f4->SetLineStyle(2);
  f5->SetLineStyle(2);
  f6->SetLineStyle(2);

  // Fitting
  h2->Fit(" funiform1 ", "BQR ");
  h3->Fit(" funiform2 ", "BQR ");
  h4->Fit(" fexpo ", "BQR ");
  h11->Fit(" fgaus3 ", "BQR ");
  hDiff1->Fit(" fgaus1 ", "BQR ");
  hDiff2->Fit(" fgaus2 ", "BQR ");

  // Native array of particles ’name
  const char *label[7]{"Pion+", "Pion-", "Kaon+", "Kaon-", "Proton+", "Proton-", " Kaon*"};

  // Drawing histograms on Canvas
  std::for_each(histos.begin(), histos.end(), [&](TH1F *h) {
    if (h == h1) {
      c1->cd(1);
      h->GetXaxis()->SetBinLabel(1, "#Pion+");
      h->GetXaxis()->SetBinLabel(2, "#Pion-");
      h->GetXaxis()->SetBinLabel(3, label[2]);
      h->GetXaxis()->SetBinLabel(4, label[3]);
      h->GetXaxis()->SetBinLabel(5, label[4]);
      h->GetXaxis()->SetBinLabel(6, label[5]);
      h->GetXaxis()->SetBinLabel(7, label[6]);
      h->GetXaxis()->SetTitle(" Particles ");
    } else if (h == h2) {
      c1->cd(2);
      h->GetXaxis()->SetTitle("# theta [ rad ]");
      h->SetMaximum(12000);
      h->SetMinimum(8000);
    } else if (h == h3) {
      c1->cd(3);
      h->GetXaxis()->SetTitle("# phi [ rad ]");
      h->SetMaximum(12000);
      h->SetMinimum(8000);
    } else if (h == h4) {
      c2->cd(1);
      h->GetXaxis()->SetTitle(" Impulse [ GeV /c]");
    } else if (h == h5) {
      c2->cd(2);
      h->GetXaxis()->SetTitle(" Impulse [ GeV /c]");
    } else if (h == h6) {
      c3->cd();
      h->GetXaxis()->SetTitle(" Energy [ GeV ]");
      h->SetAxisRange(0., 6., "X");
    } else if (h == h7) {
      c4->cd(1);
      h->GetXaxis()->SetTitle(" Mass [ GeV /c ^{2}] ");
    } else if (h == h8) {
      c4->cd(2);
      h->GetXaxis()->SetTitle(" Mass [ GeV /c ^{2}] ");
    } else if (h == h9) {
      c4->cd(3);
      h->GetXaxis()->SetTitle(" Mass [ GeV /c ^{2}] ");
    } else if (h == h10) {
      c4->cd(4);
      h->GetXaxis()->SetTitle(" Mass [ GeV /c ^{2}] ");
    } else if (h == h11) {
      c5->cd();
      h->GetXaxis()->SetTitle(" Mass [ GeV /c ^{2}] ");
      h->SetAxisRange(0.5, 1.5, "X");
    } else if (h == hDiff1) {
      c6->cd();
      h->GetXaxis()->SetTitle(" Mass [ GeV /c ^{2}] ");
      h->SetAxisRange(0., 2.5, "X");
    } else if (h == hDiff2) {
      c7->cd();
      h->GetXaxis()->SetTitle(" Mass [ GeV /c ^{2}] ");
      h->SetAxisRange(0., 2.5, "X");
    }

    // Cosmetics
    h->SetMarkerStyle(20);
    h->SetMarkerSize(0.5);
    h->SetLineColor(kBlue + 4);
    h->SetFillColor(kBlue - 2);
    h->GetYaxis()->SetTitleOffset(1.2);
    h->GetXaxis()->SetTitleSize(0.04);
    h->GetYaxis()->SetTitleSize(0.04);
    h->GetYaxis()->SetTitle(" Entries ");
    gStyle->SetOptStat(1002200);
    gStyle->SetOptFit(1111);
    h->DrawCopy("H");
    h->DrawCopy("E,P, SAME ");
  });


  // Printing name and entries for all histograms
  std::for_each(histos.begin(), histos.end(), [&](TH1F *h) {
    std::cout << std::left << std::setw(10) << "\nName :" << h->GetTitle() << std::left << std::setw(10)
              << "\nEntries :" << h->Integral() << '\n';
    if (h == h1) {
      for (int i{1}; i != h->GetNbinsX() + 1; ++i) {
        std::cout << "\n\u0025 of " << label[i - 1] << std::left << std::setw(10)
                  << " generated : " << (h->GetBinContent(i) / h->GetEntries()) * 100. << "\u0025\n"
                  << label[i - 1] << " in " << i << std::left << std::setw(12) << " bin :" << h->GetBinContent(i)
                  << " \u00b1 " << h->GetBinError(i) << '\n';
      }
    }
  });

  // Adding legend
  TLegend *leg1 = new TLegend(.1, .7, .3, .9);
  TLegend *leg2 = new TLegend(.1, .7, .3, .9);
  TLegend *leg3 = new TLegend(.7, .3458, .9, .536);
  TLegend *leg4 = new TLegend(.1, .7, .3, .9);
  TLegend *leg5 = new TLegend(.1, .7, .3, .9);
  TLegend *leg6 = new TLegend(.1, .7, .3, .9);
  leg1->SetFillColor(0);
  leg1->AddEntry(h2, "# theta distribution ");
  leg1->AddEntry(f1, " Uniform distribution ");
  c1->cd(2);
  leg1->Draw(" SAME ");
  leg2->SetFillColor(0);
  leg2->AddEntry(h3, "# phi distribution ");
  leg2->AddEntry(f2, " Uniform distribution ");
  c1->cd(3);

  leg2->Draw(" SAME ");
  leg3->SetFillColor(0);
  leg3->AddEntry(h4, " Impulse distribution ");
  leg3->AddEntry(f3, " Exponential distribution ");
  c2->cd(1);
  leg3->Draw(" SAME ");
  leg4->SetFillColor(0);
  leg4->AddEntry(h11, " Benchmark distribution ");
  leg4->AddEntry(f4, " Gaussian distribution ");
  c5->cd();
  leg4->Draw(" SAME ");
  leg5->SetFillColor(0);
  leg5->AddEntry(hDiff1, " Difference_1 distribution ");
  leg5->AddEntry(f5, " Gaussian distribution ");
  c6->cd();
  leg5->Draw(" SAME ");
  leg6->SetFillColor(0);
  leg6->AddEntry(hDiff2, " Difference_2 distribution ");
  leg6->AddEntry(f6, " Gaussian distribution ");
  c7->cd();
  leg6->Draw(" SAME ");
  // Printing datas in SHELL

  // Azimuthal angle
  std::cout << "\nAzimuthal angle fit :" << '\n'
            << f1->GetParName(0) << std::left << std::setw(29) << ':' << f1->GetParameter(0) << " \u00b1 "
            << f1->GetParError(0) << std::left << std::setw(39)
            << "\n\u03c7 ^2/ NDF azimuthal angle fit :" << f1->GetChisquare() / f1->GetNDF() << std::left
            << std::setw(39) << "\n\u03c7 ^2 probability azimuthal angle fit :" << f1->GetProb() << '\n';

  // Polar angle
  std::cout << "\nPolar angle fit :" << '\n'
            << f2->GetParName(0) << std::left << std::setw(25) << ':' << f2->GetParameter(0) << " \u00b1 "
            << f2->GetParError(0) << std::left << std::setw(35)

            << "\n\u03c7 ^2/ NDF polar angle fit :" << f2->GetChisquare() / f2->GetNDF() << std::left << std::setw(35)
            << "\n\u03c7 ^2 probability polar angle fit :" << f2->GetProb() << '\n';


  std::cout << '\n'
            << f4->GetParName(1) << std::left << std::setw(30) << " =" << f4->GetParameter(1) << " \u00b1 "
            << f4->GetParError(1) << '\n'
            << f4->GetParName(2) << std::left << std::setw(29) << " =" << f4->GetParameter(2) << " \u00b1 "
            << f4->GetParError(2) << '\n'
            << f4->GetParName(0) << std::left << std::setw(28) << " =" << f4->GetParameter(0) << " \u00b1 "
            << f4->GetParError(0) << std::left << std::setw(38)
            << "\n\u03c7 ^2/ NDF 1st difference fit :" << f4->GetChisquare() / f4->GetNDF() << std::left
            << std::setw(38) << "\n\u03c7 ^2 probability 1st difference fit :" << f4->GetProb() << '\n';

  // K* 2nd difference
  std::cout << '\n'
            << f5->GetParName(1) << std::left << std::setw(30) << " =" << f5->GetParameter(1) << " \u00b1 "
            << f5->GetParError(1) << '\n'
            << f5->GetParName(2) << std::left << std::setw(29) << " =" << f5->GetParameter(2) << " \u00b1 "
            << f5->GetParError(2) << '\n'
            << f5->GetParName(0) << std::left << std::setw(28) << " =" << f5->GetParameter(0) << " \u00b1 "
            << f5->GetParError(0) << std::left << std::setw(38)
            << "\n\u03c7 ^2/ NDF 2st difference fit :" << f5->GetChisquare() / f5->GetNDF() << std::left
            << std::setw(38) << "\n\u03c7 ^2 probability 2nd difference fit :" << f5->GetProb() << "\n\n";

  // Writing on new TFile
  file2->cd();
  c1->Write();
  c2->Write();
  c3->Write();
  c4->Write();
  c5->Write();
  c6->Write();
  c7->Write();

  // Saving Canvas in .pdf , . png and . jpg formats
  c1->Print("particleDistribution.pdf ");
  c1->SaveAs("particleDistribution.pdf");
  c2->Print("impulse.pdf");
  c3->Print("energy.pdf");
  c4->Print("invariantMass.pdf");
  c5->Print("invariantMassDecay.pdf");
  c6->Print("decayParticleData1.pdf");
  c7->Print("decayParticleData1.pdf");
  c1->Print("particleDistribution.png");
  c2->Print("impulse.png");
  c3->Print("energy.png");
  c4->Print("invariantMass.png");
  c5->Print("invariantMassDecay.png");
  c6->Print("decayParticleData1.png");
  c7->Print("decayParticleData1.png");
  c1->Print("particleDistribution.jpg");
  c2->Print("impulse.jpg");
  c3->Print("energy.jpg");
  c4->Print("invariantMass.jpg");
  c5->Print("invariantMassDecay.jpg");
  c6->Print("decayParticleData1.jpg");
  c7->Print("decayParticleData1.jpg");
  
  // Verifica se il canvas è stato salvato correttamente
  file2->Close();
  file->Close();
  if (gSystem->AccessPathName("particleDistribution.pdf") == 0) {
    std::cout << "Il file particleDistribution.pdf è stato creato con successo." << std::endl;
  } else {
    std::cerr << "Errore durante il salvataggio di particleDistribution.pdf."
              << std::endl;  // Esce con codice di errore
  }
}

// Add main in order to compile from SHELL
int main2() {
  analysis();
  return EXIT_SUCCESS;
}
