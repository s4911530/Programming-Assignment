#ifndef COIN_H_
#define COIN_H_
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Obj.h>
//----------------------------------------------------------------------------------------------------------------------
class Coin
{
public:
  //get the size of the coin:
  GLfloat getSize() {return m_sizeCoin;}
  //get the position of the coin:
  ngl::Vec3 getPos() {return m_coinPos;}
  Coin(ngl::Vec3 _pos, const ngl::Mat4 &_view, const ngl::Mat4 &_project);
  //draw the coin:
  void drawCoin();
  //spawn the coin to random points on grid:
  void spawnCoin();
//----------------------------------------------------------------------------------------------------------------------
private:
//----------------------------------------------------------------------------------------------------------------------
  const ngl::Mat4 &m_view;
  const ngl::Mat4 &m_project;
  //size of coin:
  GLfloat m_sizeCoin;
  //position of coin:
  ngl::Vec3 m_coinPos;
  //variable for random coin positions
  float m_random;
  ngl::Obj *m_mesh;
  void loadMatrixToShaderCoin();
};
//----------------------------------------------------------------------------------------------------------------------
#endif
