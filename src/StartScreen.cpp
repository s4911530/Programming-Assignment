#include "StartScreen.h"
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>

StartScreen::StartScreen(ngl::Vec3 _pos, const ngl::Mat4 &_view, const ngl::Mat4 &_project) :
    m_view(_view), m_project(_project)
{
    m_mesh= new ngl::Obj("models/startscreen.obj", "textures/pigtexture.png");
   // m_mesh->createVAO();
    m_Pos= _pos;
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    shader->loadShader("TextureShader", "shaders/TextureVertex.glsl", "shaders/TextureFragment.glsl");
    shader-> use("TextureShader");
    shader->setUniform("MVP", ngl::Mat4());
    ngl::Texture tx("textures/pigtexture.png");
    m_texID= tx.setTextureGL();
    glBindTexture(GL_TEXTURE_2D, m_texID);
}
//----------------------------------------------------------------------------------------------------------------------
void StartScreen::loadMatrixToShader()
  {
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    shader-> use("TextureShader");
    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat3 normalMatrix;
    ngl::Transformation tx;
    tx.setScale(60,10,60);
    tx.setRotation(30,0,0);
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
//draw startup screen
void StartScreen::drawStartScreen()
  {
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    loadMatrixToShader();
     //m_mesh->draw();
    prim->draw("cube");
    ngl::VAOPrimitives::instance()->draw("cube");
  }
//----------------------------------------------------------------------------------------------------------------------
