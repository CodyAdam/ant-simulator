#ifndef _ANTBASE_H_
#define _ANTBASE_H_

#include <Agent.h>
#include <Anthill.h>

/*
Nous allons maintenant créer notre première classe de fourmi. Cette classe nommée AntBase devra
hériter de la classe Agent. Toutes les fourmis ont différentes choses en commun.
-  Elles sont des agents.
-  Elles sont membres d'une fourmilière.
-  Elles ont une vitesse de déplacement dont la valeur par défaut est de 1 cm.s-1
-  Elles ont une direction de déplacement représentée par un vecteur en 2 dimensions dont la
norme 1.
-  Elles ont une durée de vie dans l'intervalle [1000 ; 2500] secondes.
-  Elles peuvent transporter une certaine quantité de nourriture.
-  Une fourmi peut avancer suivant sa direction de déplacement. Dans ce cas, la fourmi se
translate d'un vecteur d*v*Timer::dt() où d est le vecteur direction de déplacement, v la
vitesse de déplacement et Timer::dt() fournit le temps écoulé depuis le dernier appel à
update().
- Une fourmi peut tourner d'un certain angle (exprimé en radians). Cela correspond à appliquer
une rotation sur le vecteur fournissant la direction de déplacement.
-  Une fourmi peut faire demi-tour ; cela correspond à inverser la direction de déplacement.
-  Une fourmi peut s'orienter vers une cible dont la position est fournie.
-  Une fourmi peut déposer la nourriture qu'elle transporte.
-  Une fourmi peut récolter de la nourriture lorsqu'elle se trouve dessus et peut transporter un
maximum de 5 unités de nourriture.
-  Une fourmi peut percevoir avec un angle d'ouverture de pi/2 radians de la nourriture à une
distance maximale de 3 cm.
-  Lorsque la fourmi a atteint sa durée de vie, elle meurt.
-  Une fourmi s'affiche sous la forme d'un point blanc (R :255, V :255, B :255, A :255) tracé à sa
position ou d'un point vert (128,255,128,255) si elle transporte de la nourriture.
*/
class AntBase : public Agent
{
private:
  float m_speed;
  Vector2<float> m_direction;
  float m_lifeTime;
  float m_foodQuantity;
  Anthill *m_anthill;

  template <class T>
  std::vector<T *> getVisible()
  {
    std::vector<T *> all = getEnvironment()->getAllInstancesOf<T>();
    std::vector<T *> visibleFoods = {};
    std::copy_if(all.begin(), all.end(), std::back_inserter(visibleFoods), [this](T *food)
                 { return food->getPosition().distance(getPosition()) < CONE_RANGE &&
                          food->getPosition().angle(getPosition()) < CONE_ANGLE; });
    return visibleFoods;
  }
  void lookAt(const Vector2<float> &target);
  void move();
  void turn(float angle);
  void flipDirection();
  void dropFood(float quantity);
  float harvest();
  static float MAX_FOOD_QUANTITY;
  static float CONE_ANGLE;
  static float CONE_RANGE;

public:
  AntBase(Environment *env, Anthill *anthill, const float speed);
  ~AntBase();

  void update() override;
  void draw() const override;
};

#endif