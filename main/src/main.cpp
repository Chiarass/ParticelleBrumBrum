#include <array>
#include <cmath>
#include <iostream>
#include <vector>

#include "Headers.hpp"
#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "TApplication.h"
#include "TDirectory.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TRint.h"

int main(int argc, char **argv) {
// object ownership setup
#ifdef PROGRAM_USE_LOCAL_OWNERSHIP
  TDirectory::AddDirectory(kFALSE);
#endif
  // create root application
  APP_TYPE app(APP_NAME, &argc, argv);

  Particle::AddParticleType("Pion+", 0.13957, 1, 0.);
  Particle::AddParticleType("Pion-", 0.13957, -1, 0.);
  Particle::AddParticleType("Kaon+", 0.49367, 1, 0.);
  Particle::AddParticleType("Kaon-", 0.49367, -1, 0.);
  Particle::AddParticleType("Proton+", 0.93827, +1, 0.);
  Particle::AddParticleType("Proton-", 0.93827, -1, 0.);
  Particle::AddParticleType("Kaon*", 0.89166, 0, 0.050);
  // Particle::DeallocateMemory();

  gRandom->SetSeed(56);
  int Events = 100000;
  int N = 120;
  int M = 100;
  Particle *EventParticles[N];
  double phi;
  double theta;
  double p;

  double probabilityPionPlus = 0.4;
  double probabilityPionMinus = 0.4;
  double probabilityKaonPlus = 0.05;
  double probabilityKaonMinus = 0.05;
  double probabilityProtonPlus = 0.045;
  double probabilityProtonMinus = 0.045;
  double probabilityKStar = 0.01;

  TH1F *HistoParticles =
      new TH1F("HistoParticles", "Particle type distribution", 7, -0.5, 6.5);

  TH1F *HistoPolarAngle =
      new TH1F("HistoPolarAngles", "Polar angle distribution", 180, 0, M_PI);

  TH1F *HistoAzimuthalAngle = new TH1F(
      "HistoAzimuthalAngles", "Azimuthal angle distribution", 360, 0, 2 * M_PI);

  TH1F *HistoP =
      new TH1F("HistoP", "Linear momentum distribution", 100000, 0, 100);

  TH1F *HistoPTransversal =
      new TH1F("HistoPTransversal",
               "Transversal component of the linear momentum ", 1000, 0, 10);

  TH1F *HistoEnergy =
      new TH1F("HistoEnergy", "Energy distribution", 1000, 0, 100);

  TH1F *HistoInvMass_conc =
      new TH1F("HistoInvMass_conc",
               "Invariant Mass of concordant charge particles", 100000, 0, 10);

  TH1F *HistoInvMass_disc =
      new TH1F("HistoInvMass_disc",
               "Invariant Mass of discordant charge particles", 100000, 0, 10);

  TH1F *HistoInvMass_PionKaon_conc = new TH1F(
      "HistoInvMass_PionKaon_conc",
      "Invariant Mass of concordant Pions and Kaons particles", 100000, 0, 10);

  TH1F *HistoInvMass_PionKaon_disc = new TH1F(
      "HistoInvMass_PionKaon_disc",
      "Invariant Mass of discordant Pions and Kaons particles", 100000, 0, 10);

  TH1F *HistoInvMass_dec =
      new TH1F("HistoInvMass_dec",
               "Invariant Mass of Kaon* decay charge particles", 100000, 0, 10);

  for (int i = 0; i < Events; i++) {
    double charge = 0.0;
    double mass = 0.0;
    for (int j = 0; j < 100; ++j) {
      double randomValue = gRandom->Rndm();

      phi = gRandom->Uniform(1 / (2 * M_PI));
      theta = gRandom->Uniform(1 / M_PI);
      p = gRandom->Exp(1.);

      HistoPolarAngle->Fill(theta);
      HistoAzimuthalAngle->Fill(phi);
      HistoP->Fill(p);

      // ConversionPoltoCart(p, theta, phi, EventParticles[j]);
      auto ConversionPoltoCart = [&EventParticles](double p, double theta,
                                                   double phi, int j) {
        auto P = EventParticles[j];
        double Px = p * std::sin(theta) * std::cos(phi);
        double Py = p * std::sin(theta) * std::sin(phi);
        double Pz = p * std::cos(theta);

        HistoPTransversal->Fill(std::sqrt(Px * Px + Py * Py));

        P->set_P(Px, Py, Pz);
      };

      if (randomValue < probabilityPionPlus) {
        EventParticles[j]->set_fIndex("Pion+");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());

      } else if (randomValue < probabilityPionPlus + probabilityPionMinus) {
        EventParticles[j]->set_fIndex("Pion-");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());

      } else if (randomValue < probabilityPionPlus + probabilityPionMinus +
                                   probabilityKaonPlus) {
        EventParticles[j]->set_fIndex("Kaon+");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());

      } else if (randomValue < probabilityPionPlus + probabilityPionMinus +
                                   probabilityKaonPlus + probabilityKaonMinus) {
        EventParticles[j]->set_fIndex("Kaon-");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());

      } else if (randomValue < probabilityPionPlus + probabilityPionMinus +
                                   probabilityKaonPlus + probabilityKaonMinus +
                                   probabilityProtonPlus) {
        EventParticles[j]->set_fIndex("Proton+");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());

      } else if (randomValue < probabilityPionPlus + probabilityPionMinus +
                                   probabilityKaonPlus + probabilityKaonMinus +
                                   probabilityProtonPlus +
                                   probabilityProtonMinus) {
        EventParticles[j]->set_fIndex("Proton-");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());

      } else {
        EventParticles[j]->set_fIndex("Kaon*");
        HistoParticles->Fill(EventParticles[j]->get_fIndex());
        HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());

        double x = gRandom->Uniform(1);
        if (x < 0.5) {
          Particle Kplus = Particle("Kaon+", 0.49367, 1, 0);
          Particle Piminus = Particle("Pion-", 0.13957, -1, 0);
          EventParticles[j]->Particle::Decay2body(Kplus, Piminus);
          EventParticles[M] = Kplus;
          EventParticles[M + 1] = Piminus;

          HistoInvMass_dec->Fill(
              EventParticles[M]->InvMass(EventParticles[M + 1]));
          M = M + 2;
        } else {
          Particle Kminus = Particle("Kaon-", 0.49367, -1, 0);
          Particle Piplus = Particle("Pion+", 0.13957, +1, 0);
          EventParticles[j]->Particle::Decay2body(Kminus, Piplus);
          EventParticles[M] = Kminus;
          EventParticles[M + 1] = Piplus;

          HistoInvMass_dec->Fill(
              EventParticles[M]->InvMass(EventParticles[M + 1]));
          M = M + 2;
        }
      }
    }

    std::vector<Particle *> chargePlus;
    std::vector<Particle *> chargeMinus;
    for (int k = 0; k < 100; ++k) {
      
      if ((EventParticles[k]->get_fIndex()) % 2 == 0 && EventParticles[k]->get_fIndex() != 6 )
        chargePlus.push_back(EventParticles[k]);

      else 
      if (EventParticles[k]->get_fIndex() != 6) chargeMinus.push_back(EventParticles[k]);
    }

    
  }

  // do stuff

  // run application
  app.Run();

  return 0;
}
