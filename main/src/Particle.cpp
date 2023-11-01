#include "Particle.hpp"

#include <array>
#include <cmath>
#include <iostream>

#include "ParticleType.hpp"
#include "ResonanceType.hpp"

int const Particle::fMaxNumParticleType;
int Particle::fNParticleType = 0;
ParticleType *Particle::fParticleType[fMaxNumParticleType];

int Particle::FindParticle(const char *Name) {
  for (int i = 0; i < fMaxNumParticleType; ++i) {
    if (fParticleType[i]->get_ParticleName() == Name) {
      return i;
    }
  }
  std::cout << "No correspondence, sorry";
  return -1;
}

Particle::Particle(const char *parName, int Index, double Px, double Py,
                   double Pz)
    : f_Name(parName),
      fIndex(Index = FindParticle(parName)),
      fPx(Px = 0),
      fPy(Py = 0),
      fPz(Pz = 0){};

int Particle::get_fIndex() { return fIndex; }

double const Particle::get_Xmomentum() { return fPx; }
double const Particle::get_Ymomentum() { return fPy; }
double const Particle::get_Zmomentum() { return fPz; }

double const Particle::get_Mass() { return particletype.get_ParticleMass(); }

double const Particle::ParticleEnergy() {
  double const m = particletype.get_ParticleMass();
  double P = fPx * fPx + fPy * fPy + fPz * fPz;
  return sqrt(m * m + P);
}

double Particle::InvMass(Particle &p) {
  const double E1 = ParticleEnergy();
  const double E2 = p.ParticleEnergy();
  const double PX = fPx + p.get_Xmomentum();
  const double PY = fPy + p.get_Ymomentum();
  const double PZ = fPz + p.get_Zmomentum();

  return sqrt((E1 + E2) * (E1 + E2) - (PX + PY + PZ) * (PX + PY + PZ));
}

void Particle::set_P(double px, double py, double pz) {
  fPx = px;
  fPy = py;
  fPz = pz;
}

void Particle::ArrayStatus()  // può essere statico? non lo so
{
  for (int i = 0; i < fNParticleType; ++i) {
    ParticleType p = *fParticleType[i];
    p.print();
    std::cout << std::endl;
  }
}

void Particle::ParticleStatus() {
  std::cout << "Particle code: " << get_fIndex() << std::endl << std::endl;
  std::cout << "Name: " << f_Name << std::endl;
  std::cout << "Momentum: "
            << "(" << get_Xmomentum() << ", " << get_Ymomentum() << " ,"
            << get_Zmomentum() << ")" << std::endl;
}

void Particle::AddParticleType(const char *name, const double Mass,
                               const int Charge, const double Width) {
  if (FindParticle(name) == -1 && fNParticleType < fMaxNumParticleType) {
    for (int i = fNParticleType; i < fMaxNumParticleType; ++i) {
      fParticleType[i] = new ResonanceType(name, Mass, Charge, Width);
      ++fNParticleType;
    }
  }

  else {
    std::cout << "The array is already full, sorry bro" << std::endl;
  }
}

void Particle::set_fIndex(int index) {
  if (get_fIndex() == index) {
    std::cout << "The particle is already here." << std::endl;
  } else {
    fIndex = index;
  }
}

void Particle::set_fIndex(const char *pname) {
  if (FindParticle(pname) != -1) {
    std::cout << "The particle is already here." << std::endl;
  } else {
    fIndex = FindParticle(pname);
  }
}

void Particle::DeallocateMemory() {
  for (int i = 0; i < fNParticleType; ++i) {
    delete fParticleType[i];
  }
}
/*Un metodo (un “Setter”) che permetta di settare esplicitamente l’attributo
fIndex corrispondente al codice della particella, controllando se il tipo
corrispondente è già contemplato nell’array di puntatori a ParticleType. Fornire
due versioni in overload, uno con argomento un intero, e uno con argomento il
nome nella particella. Usare anche in questo caso il metodo privato
FindParticle.*/