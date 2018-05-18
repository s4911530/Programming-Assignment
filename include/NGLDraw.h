#ifndef NGLDRAW_H_
#define NGLDRAW_H_

#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <SDL.h>
#include "Pig.h"
#include "Coin.h"
#include "Bullet.h"
#include "Lives.h"
#include "Gameover.h"
#include "StartScreen.h"
#include <memory>
#include <ngl/Transformation.h>
//----------------------------------------------------------------------------------------------------------------------
class NGLDraw
{
  public :
//----------------------------------------------------------------------------------------------------------------------
    //to check if game is running:
    bool isRunning=false;
    //----------------------------------------------------------------------------------------------------------------------
    GLuint m_texID;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor this will have a valid OpenGL context so we can create gl stuff
    //----------------------------------------------------------------------------------------------------------------------
    NGLDraw();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor used to remove any NGL stuff created
    //----------------------------------------------------------------------------------------------------------------------
    ~NGLDraw();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief resize our screen and set the camera aspect ratio
    /// @param[in] _w the new width
    /// @param[in] _h the new height
    //----------------------------------------------------------------------------------------------------------------------
    void resize(int _w, int _h);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief draw the scene
    //----------------------------------------------------------------------------------------------------------------------
    void draw();
//----------------------------------------------------------------------------------------------------------------------
    void update();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called every time a mouse is moved
    /// @param _event the SDL mouse event structure containing all mouse info
    //----------------------------------------------------------------------------------------------------------------------
    void mouseMoveEvent (const SDL_MouseMotionEvent &_event);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called every time a mouse button is presses
    /// @param _event the SDL mouse event structure containing all mouse info
    //----------------------------------------------------------------------------------------------------------------------
    void mousePressEvent (const SDL_MouseButtonEvent &_event);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is released
    /// @param _event the SDL mouse event structure containing all mouse info
    //----------------------------------------------------------------------------------------------------------------------
    void mouseReleaseEvent (const SDL_MouseButtonEvent &_event);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse wheel is moved
    /// @param _event the SDL mouse event structure containing all mouse info
    //----------------------------------------------------------------------------------------------------------------------
    void wheelEvent(const SDL_MouseWheelEvent &_event);
//----------------------------------------------------------------------------------------------------------------------
    void setLightPos(float _dx, float _dy, float _dz);
//----------------------------------------------------------------------------------------------------------------------
    void keyEvent(SDL_KeyboardEvent &_event);
//----------------------------------------------------------------------------------------------------------------------
  private :

    ngl::Transformation transform;
    ngl::Vec3 m_lightPos{0.0f, 1.0f, 0.0f};
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief used to store the x rotation mouse value
    //----------------------------------------------------------------------------------------------------------------------
    int m_spinXFace;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief used to store the y rotation mouse value
    //----------------------------------------------------------------------------------------------------------------------
    int m_spinYFace;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to indicate if the mouse button is pressed when dragging
    //----------------------------------------------------------------------------------------------------------------------
    bool m_rotate;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to indicate if the Right mouse button is pressed when dragging
    //----------------------------------------------------------------------------------------------------------------------
    bool m_translate;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the previous x mouse value
    //----------------------------------------------------------------------------------------------------------------------
    int m_origX;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the previous y mouse value
    //----------------------------------------------------------------------------------------------------------------------
    int m_origY;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the previous x mouse value for Position changes
    //----------------------------------------------------------------------------------------------------------------------
    int m_origXPos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the previous y mouse value for Position changes
    //----------------------------------------------------------------------------------------------------------------------
    int m_origYPos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief used to store the global mouse transforms
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Mat4 m_mouseGlobalTX;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the model position for mouse movement
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 m_modelPos;
    //variables for individual counters:
    int counter1= 1;
    int counter2= 1;
    int counter3= 1;
    int counter4= 1;
    int counter5= 1;
    int counter6= 1;
    int counter7= 1;
    int counter8= 1;
    int counter9= 1;

    /// @brief check the collisions
    //----------------------------------------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------------------------------------
    ngl::Mat4 m_view;
    ngl::Mat4 m_projection;
    // unique pointer for pig (user):
    std::unique_ptr<Pig> m_pig;
    // unique pointer for coin:
    std::unique_ptr<Coin> m_coin;
    // instances for bullets (spheres):
    Bullet *bullet1, *bullet2, *bullet3, *bullet4, *bullet5, *bullet6, *bullet7, *bullet8, *bullet9;
    // instances for lives:
    Lives *life1, *life2, *life3, *life4, *life5;
    // unique pointer for game over mesh:
    std::unique_ptr<Gameover> m_gameover;
    // unique pointer for startup screen
    std::unique_ptr<StartScreen> m_startScreen;
//----------------------------------------------------------------------------------------------------------------------
    void loadMatrixToShader();
    void loadMatrixToShaderLives();
    void loadMatrixToShaderCoin();
    void loadMatrixToShaderBullet();
    //do pig-coin collision:
    bool pigCoinCollision( ngl::Vec3 m_pos, ngl::Vec3 m_coinPos, GLfloat m_sizePig, GLfloat m_sizeCoin);
    //do bullet-pig collision:
    bool bulletPigCollision(ngl::Vec3 m_bulletPos, ngl::Vec3 m_pos, GLfloat m_radius, GLfloat m_sizePig);
    //check pig-coin collision:
    void checkPigCoinCollision();
    //check bullet-pig collision:
    void checkBulletPigCollision();
};
//----------------------------------------------------------------------------------------------------------------------
#endif
