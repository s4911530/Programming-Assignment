#include "Gameover.h"
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
//----------------------------------------------------------------------------------------------------------------------
Gameover::Gameover(ngl::Vec3 _pos, const ngl::Mat4 &_view, const ngl::Mat4 &_project) :
    m_view(_view), m_project(_project)
{
    m_mesh= new ngl::Obj("models/gameover.obj");
    m_mesh->createVAO();
    m_Pos= _pos;
}
//----------------------------------------------------------------------------------------------------------------------
void Gameover::loadMatrixToShader()
  {
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    shader-> use("DiffuseShader");
    shader->setUniform("diffuseColour",0.3f,0.6,0.5,1.0f);
    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat3 normalMatrix;
    ngl::Transformation tx;
    tx.setScale(4,4,4);
    tx.setRotation(0,0,0);
    tx.setPosition(m_Pos);
    MV=m_view*tx.getMatrix();
    MVP=m_project*MV;
    normalMatrix=MV;
    normalMatrix.inverse();

    shader->setUniform("MVP",MVP);
    shader->setUniform("MV", MV);
    shader->setUniform("normalMatrix",normalMatrix);
  }
//----------------------------------------------------------------------------------------------------------------------
//draw game over
void Gameover::drawGameover()
  {
      loadMatrixToShader();
       m_mesh->draw();
  }
//----------------------------------------------------------------------------------------------------------------------
