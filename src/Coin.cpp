#include "Coin.h"
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
#include <ngl/Random.h>
#include <ctime>
//----------------------------------------------------------------------------------------------------------------------
Coin::Coin(ngl::Vec3 _pos, const ngl::Mat4 &_view, const ngl::Mat4 &_project) :
    m_view(_view), m_project(_project)
{
  m_coinPos=_pos;
  m_sizeCoin= 0.3f;
  m_mesh= new ngl::Obj("models/coin.obj");
  m_mesh->createVAO();
  std::cout << "coin destructor" << std::endl << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
void Coin::loadMatrixToShaderCoin()
{
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  shader-> use("DiffuseShader");
  shader->setUniform("diffuseColour",1.0f,0.9,0.0,1.0f);
  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Transformation tx;
  tx.setScale(m_sizeCoin*2,m_sizeCoin*2,m_sizeCoin*2);
  tx.setPosition(m_coinPos);
  MV=m_view*tx.getMatrix();
  MVP=m_project*MV;
  normalMatrix=MV;
  normalMatrix.inverse();

  shader->setUniform("MVP",MVP);
  shader->setUniform("MV", MV);
  shader->setUniform("normalMatrix",normalMatrix);
}
//----------------------------------------------------------------------------------------------------------------------
//spawm coin randomly
void Coin::spawnCoin()
{
  srand(time(NULL));
  m_coinPos.m_x = std::rand() % 50 +(-25) +0;
  m_coinPos.m_z = std::rand() % 50 +(-25) +0;
}
//----------------------------------------------------------------------------------------------------------------------
//draw coin
void Coin::drawCoin()
{
    loadMatrixToShaderCoin();
    m_mesh->draw();
}
//----------------------------------------------------------------------------------------------------------------------
