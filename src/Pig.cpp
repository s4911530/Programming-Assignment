#include "Pig.h"
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
#include <ngl/Random.h>
#include <ctime>
#include "Coin.h"

const static float UPDATESPEED=0.01;
Pig::Pig(ngl::Vec3 _pos, const ngl::Mat4 &_view, const ngl::Mat4 &_project) :
    m_view(_view), m_project(_project)
{
  m_pos=_pos;
  m_sizePig= 1.5f;
  m_mesh= new ngl::Obj("models/pig.obj");
  m_mesh->createVAO();
  health= 5;
}
//----------------------------------------------------------------------------------------------------------------------
void Pig::move()
{
  //std::cout<<"position is"<<m_pos<<std::endl;
  ngl::Mat3 rot;
  rot.rotateY(m_steerAngle);
  ngl::Vec3 dir(0.0f,0.0f,-1.0f);
  m_dir=dir*rot;
  m_dir*=m_speed;
  m_pos+=m_dir;
}
//----------------------------------------------------------------------------------------------------------------------
void Pig::loadMatrixToShader()
{
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  shader-> use("DiffuseShader");
  shader->setUniform("diffuseColour",1.0f,0.7,0.8f,0.0f);
  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Transformation tx;
  tx.setPosition(m_pos);
  tx.setScale(m_sizePig*2,m_sizePig*2,m_sizePig*2);
  tx.setRotation(0.0f,m_steerAngle,0.0f);
  MV=m_view*tx.getMatrix();
  MVP=m_project*MV;
  normalMatrix=MV;
  normalMatrix.inverse().transpose();

  shader->setUniform("MVP",MVP);
  shader->setUniform("MV", MV);
  shader->setUniform("normalMatrix",normalMatrix);
}
//----------------------------------------------------------------------------------------------------------------------
//draw pig
void Pig::drawPig()
{
  loadMatrixToShader();
  m_mesh->draw();
}
//----------------------------------------------------------------------------------------------------------------------
//go left
void Pig::left()
{
  m_steerAngle = 90.0f;
}
//----------------------------------------------------------------------------------------------------------------------
//go right
void Pig::right()
{
  m_steerAngle= 270.0f;
}
//----------------------------------------------------------------------------------------------------------------------
double clamp(double d, double min, double max)
{
  const double t = d < min ? min : d;
  return t > max ? max : t;
}
//----------------------------------------------------------------------------------------------------------------------
//go forward
void Pig::forward()
{
    m_steerAngle =0.0f;
}
//----------------------------------------------------------------------------------------------------------------------
//go backward
void Pig::backward()
{
m_steerAngle = 180.0f;
}
//----------------------------------------------------------------------------------------------------------------------
//limit motion to grid
void Pig::boundary()
{
// x boundaries:
    if (m_pos.m_x== 30.0f)
    {
        m_pos.m_x= -30.0f;
    }

    if (m_pos.m_x== -30.0f)
    {
        m_pos.m_x= 30.0f;
    }
//z boundaries:
    if (m_pos.m_z == 30.0f)
    {
        m_pos.m_z = -30.0f;
    }

    if (m_pos.m_z== -30.0f)
    {
        m_pos.m_z= 30.0f;
    }
}
//----------------------------------------------------------------------------------------------------------------------
