#ifndef GAMEOVER_H_
#define GAMEOVER_H_
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Transformation.h>
#include <ngl/Obj.h>
//----------------------------------------------------------------------------------------------------------------------
class Gameover
{
public:
   Gameover(ngl::Vec3 _pos, const ngl::Mat4 &_view, const ngl::Mat4 &_project);
   ~Gameover()=default;
   //position of mesh:
   ngl::Vec3 m_Pos;
   //draw mesh on screen:
   void drawGameover();
//----------------------------------------------------------------------------------------------------------------------
private:
   const ngl::Mat4 &m_view;
   const ngl::Mat4 &m_project;
   ngl::Obj *m_mesh;
   void loadMatrixToShader();
};
#endif
//----------------------------------------------------------------------------------------------------------------------
