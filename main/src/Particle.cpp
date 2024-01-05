// Particle.hpp

#include "../include/Particle.hpp"

#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "../include/ParticleType.hpp"
#include "../include/ResonanceType.hpp"

// Definition of constants
int const Particle::fMaxNumParticleType;
int Particle::fNParticleType = 0;
ParticleType *Particle::fParticleType[fMaxNumParticleType];

// Function to find the index of a particle type based on its name
int Particle::FindParticle(const char *Name) {
  // Loop through the particle types array to find the index
  for (int i = 0; i < fMaxNumParticleType; ++i) {
    if (fParticleType[i]->get_ParticleName() == Name) {
      return i;
    }
  }

  // If no correspondence is found, print a message and return -1
  std::cout << "No correspondence found for particle type: " << Name
            << std::endl;
  return -1;
}

// Default constructor
Particle::Particle(){};

// Parameterized constructor with particle name, momentum components (defaulted
// to 0)
Particle::Particle(const char *parName, double Px, double Py, double Pz)
    : f_Name(parName), fPx(Px = 0), fPy(Py = 0), fPz(Pz = 0) {
  // Initialize the particle index by finding the particle type
  fIndex = FindParticle(parName);
};

// Getter for the particle index
int Particle::get_fIndex() { return fIndex; }

// Getters for momentum components
double Particle::get_Xmomentum() const { return fPx; }
double Particle::get_Ymomentum() const { return fPy; }
double Particle::get_Zmomentum() const { return fPz; }

// Getter for particle mass using the particle type
double Particle::get_Mass() const {
  return fParticleType[fIndex]->get_ParticleMass();
}

// Getter for particle charge using the particle type
double Particle::get_Charge() const {
  return fParticleType[fIndex]->get_ParticleCharge();
}

// Check if a particle has a specific mass and type
bool Particle::get_specificMass(double mass, const char *name) const {
  if (fParticleType[FindParticle(name)]->get_ParticleMass() == mass) {
    return true;
  } else {
    return false;
  }
}

// Calculate and return the particle energy using the particle type
double Particle::ParticleEnergy() const {
  double const m = fParticleType[fIndex]->get_ParticleMass();
  double P = fPx * fPx + fPy * fPy + fPz * fPz;
  return sqrt(m * m + P);
}

// Calculate and return the invariant mass of two particles
double Particle::InvMass(Particle &p) {
  const double E1 = ParticleEnergy();
  const double E2 = p.ParticleEnergy();
  const double PX = fPx + p.get_Xmomentum();
  const double PY = fPy + p.get_Ymomentum();
  const double PZ = fPz + p.get_Zmomentum();

  return sqrt((E1 + E2) * (E1 + E2) - (PX + PY + PZ) * (PX + PY + PZ));
}

// Set the momentum components of the particle
void Particle::set_P(double px, double py, double pz) {
  fPx = px;
  fPy = py;
  fPz = pz;
}

// Print the status of all particle types
void Particle::ArrayStatus() {
  for (int i = 0; i < fNParticleType; ++i) {
    ParticleType p = *fParticleType[i];
    p.print();
    std::cout << std::endl;
  }
}

void Particle::ParticleStatus() {
  // Display particle information including code, name, and momentum
  std::cout << "Particle code: " << get_fIndex() << std::endl << std::endl;
  std::cout << "Name: " << f_Name << std::endl;
  std::cout << "Momentum: "
            << "(" << get_Xmomentum() << ", " << get_Ymomentum() << " ,"
            << get_Zmomentum() << ")" << std::endl;
}

void Particle::AddParticleType(const char *name, const double Mass,
                               const int Charge, const double Width) {
  // Add a new particle type to the array if it's not already full
  if (FindParticle(name) == -1 && fNParticleType < fMaxNumParticleType) {
    for (int i = fNParticleType; i < fMaxNumParticleType; ++i) {
      fParticleType[i] = new ResonanceType(name, Mass, Charge, Width);
      ++fNParticleType;
    }
  } else {
    // Display a message if the array is already full
    std::cout << "The array is already full, sorry bro" << std::endl;
  }
}

void Particle::set_fIndex(int index) {
  // Set the particle index if it's different from the current value
  if (get_fIndex() != index) {
    fIndex = index;
  }
}

void Particle::set_fIndex(const char *pname) {
  // Set the particle index based on the particle name if it's found
  if (FindParticle(pname) == -1) {
    fIndex = FindParticle(pname);
  }
}

void Particle::set_ParticleTypeFromMap(const std::string &particleType) {
  // Set the particle index based on a predefined map of particle types
  if (particleType == "Pion+") {
    set_fIndex("Pion+");
  } else if (particleType == "Pion-") {
    set_fIndex("Pion-");
  } else if (particleType == "Kaon+") {
    set_fIndex("Kaon+");
  } else if (particleType == "Kaon-") {
    set_fIndex("Kaon-");
  } else if (particleType == "Proton+") {
    set_fIndex("Proton+");
  } else if (particleType == "Proton-") {
    set_fIndex("Proton-");
  } else if (particleType == "Kaon*") {
    set_fIndex("Kaon*");
  }
}

int Particle::Decay2body(Particle &dau1, Particle &dau2) const {
  // Check if the mass is zero before performing decay
  if (get_Mass() == 0.0) {
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }

  double massMot = get_Mass();
  double massDau1 = dau1.get_Mass();
  double massDau2 = dau2.get_Mass();

  if (fIndex > -1) {  // Add width effect
    // Gaussian random numbers for introducing width effect
    float x1, x2, w, y1;

    double invnum = 1. / RAND_MAX;
    do {
      x1 = 2.0 * rand() * invnum - 1.0;
      x2 = 2.0 * rand() * invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while (w >= 1.0);

    w = sqrt((-2.0 * log(w)) / w);
    y1 = x1 * w;

    // Modify the mass with width effect
    massMot += fParticleType[fIndex]->get_ParticleWidth() * y1;
  }

  if (massMot < massDau1 + massDau2) {
    // Check if the total mass after decay is less than the sum of daughter
    // masses
    printf(
        "Decayment cannot be performed because mass is too low in this "
        "channel\n");
    return 2;
  }

  // Calculate the magnitude of the momentum of the daughters in the
  // center-of-mass frame
  double pout =
      sqrt(
          (massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
          (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
      massMot * 0.5;

  // Generate random angles for the direction of the daughters
  double norm = 2 * M_PI / RAND_MAX;
  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;

  // Set the momentum of the daughters based on the random angles and calculated
  // magnitude
  dau1.set_P(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi),
             pout * cos(theta));
  dau2.set_P(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi),
             -pout * cos(theta));

  // Calculate the energy of the parent particle
  double energy = sqrt(fPx * fPx + fPy * fPy + fPz * fPz + massMot * massMot);

  // Calculate boost parameters based on the parent particle's momentum
  double bx = fPx / energy;
  double by = fPy / energy;
  double bz = fPz / energy;

  // Boost the daughters to the parent particle's rest frame
  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  // Return 0 to indicate successful decay
  return 0;
}

void Particle::Boost(double bx, double by, double bz) {
  // Boost the particle's momentum in the specified direction
  double energy = ParticleEnergy();

  // Boost this Lorentz vector
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * fPx + by * fPy + bz * fPz;
  double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

  // Update the particle's momentum after the boost
  fPx += gamma2 * bp * bx + gamma * bx * energy;
  fPy += gamma2 * bp * by + gamma * by * energy;
  fPz += gamma2 * bp * bz + gamma * bz * energy;
}
