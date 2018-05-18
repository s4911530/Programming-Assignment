#ifndef STARTSCREEN_H_
#define STARTSCREEN_H_
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Transformation.h>
#include <ngl/Obj.h>
//----------------------------------------------------------------------------------------------------------------------
class StartScreen
{
public:
   StartScreen(ngl::Vec3 _pos, const ngl::Mat4 &_view, const ngl::Mat4 &_project);
   ~StartScreen()=default;
   //position of startup screen:
   ngl::Vec3 m_Pos;
   GLuint m_texID;
   //draw startup screen
   void drawStartScreen();
//----------------------------------------------------------------------------------------------------------------------
private:
   const ngl::Mat4 &m_view;
   const ngl::Mat4 &m_project;
   ngl::Obj *m_mesh;
   void loadMatrixToShader();
};
#endif
//----------------------------------------------------------------------------------------------------------------------
