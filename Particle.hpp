#ifndef PARTICLE
#define PARTICLE
#include <array>
#include <iostream>

#include "ParticleType.hpp"
#include "ResonanceType.hpp"

class Particle {
 private:
  ParticleType particletype;
  ResonanceType resonancetype;
  const char* f_Name = particletype.get_ParticleName();
  static const int fMaxNumParticleType = 10;
  static ParticleType* fParticleType[fMaxNumParticleType];
  static int fNParticleType;
  int fIndex;
  double fPx;
  double fPy;
  double fPz;
  static int FindParticle(const char* Name) {
    for (int i; i < fMaxNumParticleType; ++i) {
      if (fParticleType[i]->get_ParticleName() == Name) {
        return i;
      } else {
        std::cout << "No correspondence, sorry";
        return -1;
      }
    }
  };

 public:
  Particle(const char* parName, int Index, double Px, double Py, double Pz)
      : f_Name(parName),
        fIndex(Index = FindParticle(parName)),
        fPx(Px = 0),
        fPy(Py = 0),
        fPz(Pz = 0){};
  int get_fIndex() { return fIndex; };
  static void AddParticleType(const char* name, const double Mass,
                              const int Charge, const double Width) {
    fNParticleType = 0;
    if (Width > 0) {
      ResonanceType* fResonanceType[fMaxNumParticleType];
      ParticleType* pPTR;
      for (int i = 0; i < fMaxNumParticleType; ++i) {
        fResonanceType[i] = static_cast<ResonanceType*>(fParticleType[i]);
        for (int i = 0; i < fMaxNumParticleType; ++i) {
          if (FindParticle(name) == -1) {
            if (fNParticleType < fMaxNumParticleType) {
              fResonanceType[i] = new ResonanceType(name, Mass, Charge, Width);
              ++fNParticleType;
            } else {
              std::cout << "The array is already full, sorry bro" << std::endl;
              break;
            }
          } else {
            std::cout << "This particle is already there, sorry bro"
                      << std::endl;
            break;
          }
        }
      }
    } else {
      for (int i = 0; i < fMaxNumParticleType; ++i) {
        if (FindParticle(name) == -1) {
          if (fNParticleType < fMaxNumParticleType) {
            fParticleType[i] = new ParticleType(name, Mass, Charge);
            ++fNParticleType;
          } else {
            std::cout << "The array is already full, sorry bro" << std::endl;
            break;
          }
        } else {
          std::cout << "This particle is already there, sorry bro" << std::endl;
          break;
        }
      }
    };
  };
};
#endif