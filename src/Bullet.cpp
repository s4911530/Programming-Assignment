#include "Bullet.h"
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
#include <ngl/Random.h>
#include <ctime>
//----------------------------------------------------------------------------------------------------------------------
Bullet::Bullet(ngl::Vec3 _pos, const ngl::Mat4 &_view, const ngl::Mat4 &_project) :
    m_view(_view), m_project(_project)
{
  m_bulletDir=ngl::Vec3(0.2,0.0,0.2);
  m_bulletDirX = 0.2;
  m_bulletDirZ = 0.2;
  m_bulletPos=_pos;
  //set the radius of the bullets
  m_radius= 1.0f;
}
//----------------------------------------------------------------------------------------------------------------------
void Bullet::loadMatrixToShaderBullet()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  shader-> use("DiffuseShader");
  shader->setUniform("diffuseColour",0.0f,0.0,1.0f,0.0f);
  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Transformation tx;
  tx.setScale(m_radius,m_radius,m_radius);
  tx.setPosition(m_bulletPos);
  MV=m_view * tx.getMatrix();
  MVP=m_project*MV;
  normalMatrix=MV;
  normalMatrix.inverse();
//----------------------------------------------------------------------------------------------------------------------
  shader->setUniform("MVP",MVP);
  shader->setUniform("MV", MV);
  shader->setUniform("normalMatrix",normalMatrix);
}
//----------------------------------------------------------------------------------------------------------------------
double clampB(double d, double min, double max)
{
  const double t = d < min ? min : d;
  return t > max ? max : t;
}
//----------------------------------------------------------------------------------------------------------------------
//draw bullets
void Bullet::drawBullet()
{
   ngl::ShaderLib *shader=ngl::ShaderLib::instance();
   ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
//----------------------------------------------------------------------------------------------------------------------
//to limit motion to grid:
   if (rightBullets==true)
   {
       m_bulletPos.m_x-=m_bulletDirX;
       m_bulletPos.m_x=clampB(m_bulletPos.m_x,-30,30);
   }
   else if(topBullets==true)
   {
       m_bulletPos.m_z-=m_bulletDirZ;
       m_bulletPos.m_z=clampB(m_bulletPos.m_z,-30,30);
   }
   else
   {
     m_bulletPos.m_x+=m_bulletDirX;
     m_bulletPos.m_x=clampB(m_bulletPos.m_x,-30,30);
   }
//to reverse direction:
   if (m_bulletPos.m_x ==30)
   {
       reverseX();
   }
    if (m_bulletPos.m_x == -30)
    {
        reverseX();
    }

   if (m_bulletPos.m_z ==30)
   {
       reverseZ();
  }
    if (m_bulletPos.m_z == -30)
    {
        reverseZ();
    }

   loadMatrixToShaderBullet();
   prim->draw("sphere");
   ngl::VAOPrimitives::instance()->draw("sphere");
}
//----------------------------------------------------------------------------------------------------------------------
