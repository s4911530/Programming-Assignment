#ifndef LIVES_H_
#define LIVES_H_
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Transformation.h>
#include <ngl/Obj.h>
//----------------------------------------------------------------------------------------------------------------------
class Lives
{
public:
   Lives(ngl::Vec3 _pos, const ngl::Mat4 &_view, const ngl::Mat4 &_project);
   ~Lives()=default;
   //position of hearts:
   ngl::Vec3 m_lifePos;
   //draw hearts on screen:
   void drawLives();
//----------------------------------------------------------------------------------------------------------------------
private:
   const ngl::Mat4 &m_view;
   const ngl::Mat4 &m_project;
   ngl::Obj *m_mesh;
   void loadMatrixToShaderLives();
};
#endif
//----------------------------------------------------------------------------------------------------------------------
