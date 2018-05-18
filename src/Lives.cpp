#include "Lives.h"
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
//----------------------------------------------------------------------------------------------------------------------
Lives::Lives(ngl::Vec3 _pos, const ngl::Mat4 &_view, const ngl::Mat4 &_project) :
    m_view(_view), m_project(_project)
{
    m_lifePos= _pos;
    m_mesh= new ngl::Obj("models/heart.obj");
    m_mesh->createVAO();
}
//----------------------------------------------------------------------------------------------------------------------
void Lives::loadMatrixToShaderLives()
  {
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    shader-> use("DiffuseShader");
    shader->setUniform("diffuseColour",1.0f,0.2,0.5,1.0f);
    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat3 normalMatrix;
    ngl::Transformation tx;
    tx.setScale(1.0,1.0,1.0);
    tx.setRotation(0,0,0);
    tx.setPosition(m_lifePos);
    MV=m_view*tx.getMatrix();
    MVP=m_project*MV;
    normalMatrix=MV;
    normalMatrix.inverse();

    shader->setUniform("MVP",MVP);
    shader->setUniform("MV", MV);
    shader->setUniform("normalMatrix",normalMatrix);
  }
//----------------------------------------------------------------------------------------------------------------------
//draw Lives
void Lives::drawLives()
  {
      loadMatrixToShaderLives();
      m_mesh->draw();
  }
//----------------------------------------------------------------------------------------------------------------------
