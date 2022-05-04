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
protected:
  float m_speed;
  Vector2<float> m_direction;
  float m_lifeTime;
  float m_foodQuantity;
  Anthill *m_anthill;

  void lookAt(const Vector2<float> &target);
  virtual void move();
  void turn(float angle);
  void flipDirection();
  void dropFood(float quantity);
  float harvest();

  static float const MAX_FOOD_QUANTITY;
  static float const FOOD_ANGLE;
  static float const FOOD_EXTENT;
  static float const FOOD_MIN_EXTENT;
  static float const PHERO_ANGLE;
  static float const PHERO_EXTENT;
  static float const PHERO_MIN_EXTENT;

public:
  AntBase(Anthill *anthill, Vector2<float> initPos, const float speed = 1);
  ~AntBase();

  virtual void update() = 0;
  void draw() const override;
};

#endif