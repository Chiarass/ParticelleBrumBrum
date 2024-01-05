#ifndef ROOT_TEMPLATE_PROJECT_LINKDEF_H
#define ROOT_TEMPLATE_PROJECT_LINKDEF_H

#ifdef __CLING__
#pragma link C++ nestedclasses; //link nested classes
#pragma link C++ nestedtypedefs; //link nested typedefs
#pragma link C++ class ParticleType; link ParticleType
#pragma link C++ class ResonanceType; link ResonanceType
#pragma link C++ class Particle; link Particle
#endif

#endif //ROOT_TEMPLATE_PROJECT_LINKDEF_H