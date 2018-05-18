#ifndef PIG_H_
#define PIG_H_
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include "Coin.h"
#include <iostream>
#include <ngl/Obj.h>
//----------------------------------------------------------------------------------------------------------------------
class Pig
{
  public:
    Pig(ngl::Vec3 _pos, const ngl::Mat4 &_view, const ngl::Mat4 &_project);
    //health of the user (pig):
    int health;
    //get the size of the user (pig):
    GLfloat getSize() {return m_sizePig;}
    //get the position of the pig:
    ngl::Vec3 getPos() {return m_pos;}
    //get the direction of the pig:
    ngl::Vec3 getDir() {return m_dir;}
    //get the speed of the pig:
    GLfloat getSpeed() {return m_speed;}
    //controls speed and direction of user(pig):
    void move();
    //draw pig:
    void drawPig();
    //limit pig motion to grid
    void boundary();
    // move left
    void left();
   // move right
    void right();
    //go forward
    void forward();
    //go backward
    void backward();
//----------------------------------------------------------------------------------------------------------------------
  private:
    //direction of pig:
    ngl::Vec3 m_dir;
    //position of pig:
    ngl::Vec3 m_pos;
    //size of pig:
    GLfloat m_sizePig;
    //spped of pig:
    float m_speed=0.25f;
    float m_steerAngle=0.0f;
    const ngl::Mat4 &m_view;
    const ngl::Mat4 &m_project;
    ngl::Obj *m_mesh;
    void loadMatrixToShader();
};
//----------------------------------------------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------------------------------------------
