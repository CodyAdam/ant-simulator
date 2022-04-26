#ifndef _AGENT_H
#define _AGENT_H

#include <Environment.h>

class Agent : private Environment::LocalizedEntity
{
  private:
  /* data */
public:
  Agent(/* args */);
  ~Agent();
};

Agent::Agent(const Environment *env)
{
  
}

Agent::~Agent()
{
}

#endif


// Créez la classe Agent qui devra hériter de la classe Environment::LocalizedEntity. Cet
// agent disposera dun constructeur prenant en paramètre un pointeur sur une instance de la classe
// TP de C++ (module PROG 2)
// Environnement,  sa  position  initiale  ainsi  que  son  rayon  qui  par  défaut  prendra  la  valeur
// Environment::LocalizedEntity::defaultRadius().