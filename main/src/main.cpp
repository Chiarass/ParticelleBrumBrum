#include <Map.hpp>
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
  // Object ownership setup
#ifdef PROGRAM_USE_LOCAL_OWNERSHIP
  TDirectory::AddDirectory(kFALSE);
#endif
  // Create root application
  APP_TYPE app(APP_NAME, &argc, argv);
  // Initialize particle information
  particle_Info particle_Info;

  // Define particle types and their properties
  Particle::AddParticleType("Pion+", 0.13957, 1, 0.);
  Particle::AddParticleType("Pion-", 0.13957, -1, 0.);
  Particle::AddParticleType("Kaon+", 0.49367, 1, 0.);
  Particle::AddParticleType("Kaon-", 0.49367, -1, 0.);
  Particle::AddParticleType("Proton+", 0.93827, +1, 0.);
  Particle::AddParticleType("Proton-", 0.93827, -1, 0.);
  Particle::AddParticleType("Kaon*", 0.89166, 0, 0.050);

  // Set random seed
  gRandom->SetSeed(56);

  // Define parameters for event generation
  int Events = 100000;
  int N = 120;
  int M = 100;
  Particle *EventParticles[N];
  double phi;
  double theta;
  double p;

  // Define probabilities for each particle type
  double probabilityPionPlus = 0.4;
  double probabilityPionMinus = 0.4;
  double probabilityKaonPlus = 0.05;
  double probabilityKaonMinus = 0.05;
  double probabilityProtonPlus = 0.045;
  double probabilityProtonMinus = 0.045;
  double probabilityKStar = 0.01;

  // Define histograms for analysis
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
  std::vector<double> Imass;

  // Loop over events
  for (int i = 0; i < Events; i++) {
    // Loop over particles in each event
    for (int j = 0; j < 100; ++j) {
      // Generate random values for particle properties
      double randomValue = gRandom->Rndm();
      phi = gRandom->Uniform(1 / (2 * M_PI));
      theta = gRandom->Uniform(1 / M_PI);
      p = gRandom->Exp(1.);

      // Fill histograms with generated values
      HistoPolarAngle->Fill(theta);
      HistoAzimuthalAngle->Fill(phi);
      HistoP->Fill(p);
    }
  }
  // Define a lambda function to convert polar coordinates to Cartesian
  // coordinates
  auto ConversionPoltoCart = [&EventParticles, &HistoPTransversal](
                                 double p, double theta, double phi, int j) {
    auto P = EventParticles[j];
    double Px = p * std::sin(theta) * std::cos(phi);
    double Py = p * std::sin(theta) * std::sin(phi);
    double Pz = p * std::cos(theta);

    // Fill histogram for the transversal component of linear momentum
    HistoPTransversal->Fill(std::sqrt(Px * Px + Py * Py));

    // Set the Cartesian momentum components for the particle
    P->set_P(Px, Py, Pz);
  };

  // Loop over particles in each event
  for (int j = 0; j < 100; ++j) {
    // Generate a random value to determine the particle type
    double randomValue = gRandom->Rndm();

    // Assign a particle type based on the random value
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
      // Handle the case where the particle type is "Kaon*"
      EventParticles[j]->set_fIndex("Kaon*");
      HistoParticles->Fill(EventParticles[j]->get_fIndex());
      HistoEnergy->Fill(EventParticles[j]->ParticleEnergy());

      // Randomly choose the decay channel for "Kaon*"
      double x = gRandom->Uniform(1);
      if (x < 0.5) {
        // Decay channel: Kaon* -> Kaon+ + Pion-
        Particle Kplus = Particle("Kaon+", 0.49367, 1, 0);
        Particle *KPLUS = &Kplus;
        Particle Piminus = Particle("Pion-", 0.13957, -1, 0);
        Particle *PIMINUS = &Piminus;
        EventParticles[j]->Particle::Decay2body(Kplus, Piminus);
        EventParticles[M] = KPLUS;
        EventParticles[M + 1] = PIMINUS;
        HistoInvMass_dec->Fill(
            EventParticles[M]->InvMass(*EventParticles[M + 1]));
        M = M + 2;
      } else {
        // Decay channel: Kaon* -> Kaon- + Pion+
        Particle Kminus = Particle("Kaon-", 0.49367, -1, 0);
        Particle *KMINUS = &Kminus;
        Particle Piplus = Particle("Pion+", 0.13957, +1, 0);
        Particle *PIPLUS = &Piplus;
        EventParticles[j]->Particle::Decay2body(Kminus, Piplus);
        EventParticles[M] = KMINUS;
        EventParticles[M + 1] = PIPLUS;
        HistoInvMass_dec->Fill(
            EventParticles[M]->InvMass(*EventParticles[M + 1]));
        M = M + 2;
      }
    }
  }

  // Initialize a variable to store invariant mass
  double IMASS = 0.0;

  // Loop over particles in each event to calculate invariant masses
  for (int k = 0; k < M; ++k) {
    double charge1 = EventParticles[k]->get_Charge();
    double mass1 = EventParticles[k]->get_Mass();

    IMASS = 0.0;
    if (charge1 != 0) {
      // Nested loop to compare each particle with others for invariant mass
      // calculation
      for (int h = k + 1; h < M; ++h) {
        double charge2 = EventParticles[h]->get_Charge();
        double mass2 = EventParticles[h]->get_Mass();

        if (charge2 != 0) {
          // Calculate invariant mass between two particles
          IMASS = EventParticles[k]->InvMass(*EventParticles[h]);

          // Check for specific particle combinations and fill corresponding
          // histograms
          if ((EventParticles[h]->get_specificMass(mass2, "Kaon+") == true &&
               (EventParticles[k]->get_specificMass(mass1, "Pion+") == true)) ||
              (EventParticles[h]->get_specificMass(mass1, "Kaon+") == true &&
               (EventParticles[k]->get_specificMass(mass2, "Pion+") == true))) {
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
  }

  // Alternative solution proposal with reduced nested loops and more elegant
  // approach
  for (int i = 0; i < Events; i++) {
    for (int j = 0; j < 100; ++j) {
      // Generate a random value to determine the particle type
      double randomValue = gRandom->Rndm();

      // Get particleType from the map
      std::string particleType = particle_Info.GetParticleType(randomValue);

      // Create a new Particle object and set its type
      Particle *newParticle = new Particle();
      newParticle->set_ParticleTypeFromMap(particleType);

      // Set the particle type for the existing EventParticle
      EventParticles[j]->set_ParticleTypeFromMap(particleType);

      // Fill histograms or perform any other necessary actions

      // Delete the dynamically allocated Particle object
      delete newParticle;
    }
  }

  // Additional processing or analysis can be done here

  // Run the application
  app.Run();

  // Return 0 to indicate successful execution
  return 0;
}