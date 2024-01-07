#include <algorithm>
#include <array>
#include <cmath>
#include <exception>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <vector>

#include <boost/stacktrace.hpp>

#include "../include/Headers.hpp"
#include "../include/Particle.hpp"
#include "../include/ParticleType.hpp"
#include "../include/ResonanceType.hpp"
#include "TApplication.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TH1F.h"
#include "TMath.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TRint.h"
#include "TStyle.h"
#include "TBenchmark.h"

// Cosmetics
void setStyle() {
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1122);
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void simulation() {
  // Cosmetics
  setStyle();

  // Set random seed
  gRandom->SetSeed();

  // Creating TFile
  std::unique_ptr<TFile> file(new TFile("simulations.root", "RECREATE"));

  // Define particle types and their properties
  Particle::AddParticleType("Pion+", 0.13957, 1, 0.);
  Particle::AddParticleType("Pion-", 0.13957, -1, 0.);
  Particle::AddParticleType("Kaon+", 0.49367, 1, 0.);
  Particle::AddParticleType("Kaon-", 0.49367, -1, 0.);
  Particle::AddParticleType("Proton+", 0.93827, +1, 0.);
  Particle::AddParticleType("Proton-", 0.93827, -1, 0.);
  Particle::AddParticleType("Kaon*", 0.89166, 0, 0.050);

  // Define histograms for data analysis
  TH1F *HistoParticles = new TH1F("HistoParticles", "Particle type distribution", 7, 0, 7);
  TH1F *HistoPolarAngle = new TH1F("HistoPolarAngles", "Polar angle distribution", 1e3, 0, TMath::Pi());
  TH1F *HistoAzimuthalAngle = new TH1F("HistoAzimuthalAngles", "Azimuthal angle distribution", 1e3, 0, 2 * TMath::Pi());
  TH1F *HistoP = new TH1F("HistoP", "Linear momentum distribution", 500, 0, 10);
  TH1F *HistoPTransversal = new TH1F("HistoPTransversal", "Transversal component of the linear momentum", 500, 0, 10);
  TH1F *HistoEnergy = new TH1F("HistoEnergy", "Energy distribution", 500, 0, 10);
  TH1F *HistoInvMass_conc = new TH1F("HistoInvMass_conc", "Invariant Mass of concordant charge particles", 80, 0, 3);
  TH1F *HistoInvMass_disc = new TH1F("HistoInvMass_disc", "Invariant Mass of discordant charge particles", 80, 0, 3);
  TH1F *HistoInvMass_PionKaon_conc =
      new TH1F("HistoInvMass_PionKaon_conc", "Invariant Mass of concordant Pions and Kaons particles", 150, 0, 3);
  TH1F *HistoInvMass_PionKaon_disc =
      new TH1F("HistoInvMass_PionKaon_disc", "Invariant Mass of discordant Pions and Kaons particles", 150, 0, 3);
  TH1F *HistoInvMass_dec = new TH1F("HistoInvMass_dec", "Invariant Mass of Kaon* decay charge particles", 200, 0, 3);

  // Applying Sumw2() method on invariant mass histo
  HistoInvMass_conc->Sumw2();
  HistoInvMass_disc->Sumw2();
  HistoInvMass_PionKaon_conc->Sumw2();
  HistoInvMass_PionKaon_disc->Sumw2();
  HistoInvMass_dec->Sumw2();

  // Creating and initialiting variables
  constexpr int Events(1e5);
  constexpr int Particles(1e2);
  constexpr int N{120};
  int M = 100;
  std::array<std::shared_ptr<Particle>, N> EventParticles{};
  double phi;
  double theta;
  double p;
  double xRAND;
  double yRAND;

  // Lambda function for converting polar to Cartesian coordinates
  auto ConversionPoltoCart = [&HistoPTransversal, &EventParticles](double p, double theta, double phi, int j) {
    EventParticles[j]->set_P(p * std::sin(theta) * std::cos(phi), p * std::sin(theta) * std::sin(phi),
                             p * std::cos(theta));
    HistoPTransversal->Fill(EventParticles[j]->get_Xmomentum() * EventParticles[j]->get_Xmomentum() +
                            EventParticles[j]->get_Ymomentum() * EventParticles[j]->get_Ymomentum());
  };

  // Loop over events
  for (int i = 0; i < Events; i++) {
    // Reset M at the beginning of each event
    M = 100;
    std::generate_n(EventParticles.begin(), M, []() { return std::make_shared<Particle>(); });

    // Loop over particles in each event
    for (int j = 0; j < Particles; ++j) {
      phi = gRandom->Uniform(1 / (2 * TMath::Pi()));
      theta = gRandom->Uniform(1 / TMath::Pi());
      p = gRandom->Exp(1.);
      xRAND = gRandom->Rndm();

      // Fill histograms with generated data
      HistoPolarAngle->Fill(theta);
      HistoAzimuthalAngle->Fill(phi);
      HistoP->Fill(p);

      ConversionPoltoCart(p, theta, phi, j);

      // Particle generation based on probabilities
      if (xRAND < 0.4) {
        EventParticles[j]->set_fIndex("Pion+");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());
      } else if (xRAND < 0.8) {
        EventParticles[j]->set_fIndex("Pion-");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());
      } else if (xRAND < 0.85) {
        EventParticles[j]->set_fIndex("Kaon+");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());
      } else if (xRAND < 0.9) {
        EventParticles[j]->set_fIndex("Kaon-");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());
      } else if (xRAND < 0.945) {
        EventParticles[j]->set_fIndex("Proton+");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());
      } else if (xRAND < 0.99) {
        EventParticles[j]->set_fIndex("Proton-");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());
      } else {
        EventParticles[j]->set_fIndex("Kaon*");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());

        // Decay of K* particle
        yRAND = gRandom->Uniform(1);
        if (yRAND < 0.5) {
          EventParticles[M] = std::make_shared<Particle>("Kaon+", 0.49367, 1, 0);
          EventParticles[M + 1] = std::make_shared<Particle>("Pion-", 0.13957, -1, 0);
        } else {
          EventParticles[M] = std::make_shared<Particle>("Kaon-", 0.49367, -1, 0);
          EventParticles[M + 1] = std::make_shared<Particle>("Pion+", 0.13957, +1, 0);
        }
        EventParticles[j]->Particle::Decay2body(*EventParticles[M], *EventParticles[M + 1]);
        HistoInvMass_dec->Fill(EventParticles[M]->InvMass(*EventParticles[M + 1]));
        M += 2;
      }
    }

    // Initialize a variable to store invariant mass
    double IMASS = 0.0;

    // Loop over particles in each event to calculate invariant masses
    for (int k = 0; k < M; ++k) {
      // Checking EventParticles to avoid segmentation fault
      if (EventParticles[k] == nullptr) {
        std::cout << "ERROR: nullptr found\n";
        continue;  // TODO gestire l'errore
      }
      double charge1 = EventParticles[k]->get_Charge();
      double mass1 = EventParticles[k]->get_Mass();

      IMASS = 0.0;
      if (charge1 == 0) {
        continue;  // era una K*
      }
      // Nested loop to compare each particle with others for invariant mass
      // calculation
      for (int h = k + 1; h < M; ++h) {
        double charge2 = EventParticles[h]->get_Charge();
        double mass2 = EventParticles[h]->get_Mass();
        if (charge2 == 0) {
          continue;  // era una K*
        }
        // Calculate invariant mass between two particles
        if (EventParticles[h] == nullptr) {
          std::cout << "ERROR: nullptr found\n";
          continue;  // TODO gestire l'errore
        }
        IMASS = EventParticles[k]->InvMass(*EventParticles[h]);

        // Check for specific particle combinations and fill corresponding
        // histograms
        if ((EventParticles[h]->get_specificMass(mass2, "Kaon+") &&
             EventParticles[k]->get_specificMass(mass1, "Pion+")) ||
            (EventParticles[h]->get_specificMass(mass1, "Kaon+") &&
             EventParticles[k]->get_specificMass(mass2, "Pion+"))) {
          if (charge1 * charge2 < 0) {
            HistoInvMass_PionKaon_disc->Fill(IMASS);
          } else {
            HistoInvMass_PionKaon_conc->Fill(IMASS);
          }
        }

        if (charge1 * charge2 < 0) {
          HistoInvMass_disc->Fill(IMASS);
        } else {
          HistoInvMass_conc->Fill(IMASS);
        }
      }
    }
  }
  // Writing histo on TFile
  file->cd();
  file->Write();
  file->Close();
}

void exitLog() {
  std::cout << "exit by exit\n";
  std::cout << boost::stacktrace::stacktrace();
}

// Add main in order to compile from SHELL
int main() {
  auto benchmark = TBenchmark();
  benchmark.Start("Total");
  std::atexit(exitLog);

  setStyle();

  try {
    simulation();
  } catch (const std::exception &e) {
    std::cout << e.what() << '\n';
  } catch (...) {
    std::cout << "Error occurred\n";
  }

  benchmark.Show("Total");

  return EXIT_SUCCESS;
}
