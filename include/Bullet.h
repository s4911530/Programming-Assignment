#ifndef BULLET_H_
#define BULLET_H_
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Transformation.h>

class Bullet
{
public:
//----------------------------------------------------------------------------------------------------------------------
   Bullet(ngl::Vec3 _pos, const ngl::Mat4 &_view, const ngl::Mat4 &_project);
   ~Bullet()=default;
   //relative direction of bullets:
   ngl::Vec3 m_bulletDir;
   //x direction of bullets:
   float m_bulletDirX;
   //z direction of bullets:
   float m_bulletDirZ;
   //position of bullets:
   ngl::Vec3 m_bulletPos;
   //bullets on right side of grid:
   bool rightBullets = false;
   //bullets on top side of grid:
   bool topBullets = false;
//----------------------------------------------------------------------------------------------------------------------
   // The following functions were originally written by Jon Macey:
   //function to reverse x direction of bullets:
   inline void reverseX(){ m_bulletDirX*=-1;}
   //function to reverse z direction of bullets:
   inline void reverseZ(){ m_bulletDirZ*=-1;}
   //function to get position of bullets:
   inline ngl::Vec3 getPos(){return m_bulletPos;}
   // end of functions
//----------------------------------------------------------------------------------------------------------------------
   //function to get radius of bullets:
   GLfloat getRadius(){return m_radius;}
   //draw bullet:
   void drawBullet();
   // load matrix to shader:
   void loadMatrixToShaderBullet();
//----------------------------------------------------------------------------------------------------------------------
private:
   //radius of bullets:
   GLfloat m_radius;
   const ngl::Mat4 &m_view;
   const ngl::Mat4 &m_project;
};
#endif
