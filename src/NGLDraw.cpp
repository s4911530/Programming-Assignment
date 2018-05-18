#include "NGLDraw.h"
#include <ngl/ShaderLib.h>
#include <ngl/NGLInit.h>
#include <ngl/Material.h>
#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>
const static float INCREMENT=0.01f;
const static float ZOOM=0.05f;
constexpr char * DiffuseShader="DiffuseShader";

// This function was originally written by Jon Macey
NGLDraw::NGLDraw()
{
  m_rotate=false;
  // mouse rotation values set to 0
  m_spinXFace=0;
  m_spinYFace=0;

  glClearColor(0.4f, 0.4f, 1.4f, 1.0f);			   // Blue Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
//----------------------------------------------------------------------------------------------------------------------
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  shader->createShaderProgram(DiffuseShader);
  constexpr char * vertex="vertex";
  shader->attachShader(vertex,ngl::ShaderType::VERTEX);
  constexpr char *fragment="fragment";
  shader->attachShader(fragment,ngl::ShaderType::FRAGMENT);
  shader->loadShaderSource(vertex,"shaders/DiffuseVertex.glsl");
  shader->loadShaderSource(fragment,"shaders/DiffuseFragment.glsl");
  shader->compileShader(vertex);
  shader->compileShader(fragment);
  shader->attachShaderToProgram(DiffuseShader,vertex);
  shader->attachShaderToProgram(DiffuseShader,fragment);
  shader->linkProgramObject(DiffuseShader);
  shader->use(DiffuseShader);

  shader->setUniform("light.position",0.0f,1.0f,0.0f);
  shader->setUniform("light.diffuse",1.0f,1.0f,1.0f,1.0f);
  //set camera position
  m_view= ngl::lookAt({0.0f,70.0f,50.0f}, {0.0f,1.0f,0.0f}, {0.0f,1.0f,0.0f});
//----------------------------------------------------------------------------------------------------------------------
  //draw grid
  ngl::VAOPrimitives::instance()->createLineGrid("grid",60,60,30);
  // initialise objects
  m_pig.reset(new Pig(ngl::Vec3(35,0,30),m_view,m_projection));
  m_coin.reset(new Coin(ngl::Vec3(0,0,0),m_view,m_projection));
//----------------------------------------------------------------------------------------------------------------------
  life1 = new Lives(ngl::Vec3(15.0,55.0,31.0),m_view,m_projection);
  life2 = new Lives(ngl::Vec3(13.0,55.0,31.0),m_view,m_projection);
  life3 = new Lives(ngl::Vec3(11.0,55.0,31.0),m_view,m_projection);
  life4 = new Lives(ngl::Vec3(9.0,55.0,31.0),m_view,m_projection);
  life5 = new Lives(ngl::Vec3(7.0,55.0,31.0),m_view,m_projection);
//----------------------------------------------------------------------------------------------------------------------
  bullet1 = new Bullet(ngl::Vec3(-30,0,-25),m_view,m_projection);
  bullet2 = new Bullet(ngl::Vec3(-30,0,-5),m_view,m_projection);
  bullet3 = new Bullet(ngl::Vec3(-30,0,15),m_view,m_projection);
  bullet4 = new Bullet(ngl::Vec3(30,0,-15),m_view,m_projection);
  bullet5 = new Bullet(ngl::Vec3(30,0,5),m_view,m_projection);
  bullet6 = new Bullet(ngl::Vec3(30,0,25),m_view,m_projection);
  bullet7 = new Bullet(ngl::Vec3(-20,0,-28),m_view,m_projection);
  bullet8 = new Bullet(ngl::Vec3(0,0,-28),m_view,m_projection);
  bullet9 = new Bullet(ngl::Vec3(20,0,-28),m_view,m_projection);
  ngl::VAOPrimitives *prim =  ngl::VAOPrimitives::instance();
  prim->createSphere("sphere",1.0f,40.0f);
  bullet4->rightBullets=true;
  bullet5->rightBullets=true;
  bullet6->rightBullets=true;
  bullet7->topBullets=true;
  bullet8->topBullets=true;
  bullet9->topBullets=true;
//----------------------------------------------------------------------------------------------------------------------
  m_gameover.reset(new Gameover(ngl::Vec3(-2.5,-10.0,0.0),m_view,m_projection));
  m_startScreen.reset(new StartScreen(ngl::Vec3(0,0,0),m_view,m_projection));
//----------------------------------------------------------------------------------------------------------------------
}
// end of function
//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::loadMatrixToShader()
{
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  shader-> use("DiffuseShader");
  shader->setUniform("Colour",0.4f,1.0f,0.4f,1.0f);
  ngl::Mat4 MVP;
  ngl::Mat4 MV;
  ngl::Mat3 normalMatrix;
  MV=m_view * transform.getMatrix();
  MVP=m_projection*MV;
  normalMatrix=MV;
  normalMatrix.inverse().transpose();
  //shader->setUniform("MVP",ngl::Mat4());
  shader->setUniform("MVP",MVP);
  shader->setUniform("MV",MV);
  shader->setUniform("normalMatrix", normalMatrix);
}
//----------------------------------------------------------------------------------------------------------------------
NGLDraw::~NGLDraw()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}

//resize window
void NGLDraw::resize(int _w, int _h)
{
  glViewport(0,0,_w,_h);
  m_projection =ngl::perspective(45.0f, float(_w)/_h, 0.01f, 200.0f);
}
//----------------------------------------------------------------------------------------------------------------------
//draw objects
void NGLDraw::draw()
{
    //if game is not running, draw startup screen
    if (isRunning == false)
    {
        m_startScreen->drawStartScreen();
        m_view= ngl::lookAt({0.0f,90.0f,10.0f}, {0.0f,1.0f,0.0f}, {0.0f,1.0f,0.0f});
        std::cout<<"run is "<<isRunning<<std::endl;
    }

    //if game is running, draw:
    else if (isRunning ==true)
    {
        ngl::ShaderLib *shader = ngl::ShaderLib::instance();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ngl::VAOPrimitives *prim =  ngl::VAOPrimitives::instance();
        shader->setUniform("diffuseColour",0.0f,0.0f,0.0f,1.0f);
        m_view= ngl::lookAt({0.0f,70.0f,50.0f}, {0.0f,1.0f,0.0f}, {0.0f,1.0f,0.0f});
        transform.reset();
        {
            transform.setPosition(0,0,0);
            loadMatrixToShader();
            prim->draw("grid");
        }
        m_coin->drawCoin();
        bullet1->drawBullet();
        bullet2->drawBullet();
        bullet3->drawBullet();
        bullet4->drawBullet();
        bullet5->drawBullet();
        bullet6->drawBullet();
        bullet7->drawBullet();
        bullet8->drawBullet();
        bullet9->drawBullet();
        m_pig->drawPig();
//----------------------------------------------------------------------------------------------------------------------
        //if loops to subtract lives when health is affected
        if (m_pig->health == 5)
        {
            life1->drawLives();
            life2->drawLives();
            life3->drawLives();
            life4->drawLives();
            life5->drawLives();
        }
        if (m_pig->health == 4)
        {
            life1->drawLives();
            life2->drawLives();
            life3->drawLives();
            life4->drawLives();
        }
        if (m_pig->health == 3)
        {
            life1->drawLives();
            life2->drawLives();
            life3->drawLives();
        }
        if (m_pig->health == 2)
        {
            life1->drawLives();
            life2->drawLives();
        }
        if (m_pig->health == 1)
        {
            life1->drawLives();
        }
        shader->setUniform("diffuseColour",1.0f,0.0f,0.0f,1.0f);
    }
    //condition for game over
   if (m_pig->health < 1)
   {
       std::cout << "GAME OVER"<<std::endl;
       m_gameover->drawGameover();
   }
}
//----------------------------------------------------------------------------------------------------------------------
// This function was originally written by Jon Macey
void NGLDraw::setLightPos(float _dx, float _dy, float _dz)
{
  m_lightPos.m_x+=_dx;
  m_lightPos.m_y+=_dy;
  m_lightPos.m_z+=_dz;
  ngl::ShaderLib::instance()->setUniform("light.pos", m_lightPos);
}
//end of function
//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::keyEvent(SDL_KeyboardEvent &_event)
{
  switch (_event.keysym.sym)
  {
    case SDLK_UP : m_pig->forward();break;
    case SDLK_DOWN : m_pig->backward(); break;
    case SDLK_LEFT : m_pig->left(); break;
    case SDLK_RIGHT : m_pig->right(); break;
    case SDLK_RETURN : isRunning = true; break;
  }
}
//----------------------------------------------------------------------------------------------------------------------
//do pig-coin collsion:
// This function was originally written by Jon Macey:
bool NGLDraw::pigCoinCollision(ngl::Vec3 m_pos, ngl::Vec3 m_coinPos, GLfloat m_sizePig, GLfloat m_sizeCoin)
{
  // the relative position of the pig and coin
  ngl::Vec3 relPos;
  //min and max distances of the pig and coin
  GLfloat dist;
  GLfloat minDist;
  GLfloat len;
  relPos = m_pos - m_coinPos;
  // and the distance
  len=relPos.length();
  dist=len*len;
  minDist = m_sizePig + m_sizeCoin;
  // if it is a hit
  if(dist <=(minDist * minDist))
  {
    return true;
  }
  else
  {
    return false;
  }
}
//end of function

//check pig-coin collsion:
void NGLDraw::checkPigCoinCollision()
{
  //first check the pig and coin against each other
  bool collide = pigCoinCollision(m_pig->getPos(),m_coin->getPos(), m_pig->getSize(), m_coin->getSize());
  if(collide==true)
  {
      m_coin->spawnCoin();
  }
}
//do bullet-pig collsion:
bool NGLDraw::bulletPigCollision(ngl::Vec3 m_bulletPos, ngl::Vec3 m_pos, GLfloat m_radius, GLfloat m_sizePig)
{
  // the relative position of the bullet and pig
  ngl::Vec3 relPos;
  //min and max distances of the bullet and pig
  GLfloat dist;
  GLfloat minDist;
  GLfloat len;
  relPos = m_bulletPos - m_pos;
  // and the distance
  len=relPos.length();
  dist=len*len;
  minDist = m_radius + m_sizePig;
  // if it is a hit
  if(dist <=(minDist * minDist))
  {
    return true;

  }
  else
  {
    return false;
  }
}
//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::checkBulletPigCollision()
{
  //check the bullet and pig against each other
  bool collide1 = bulletPigCollision(bullet1->getPos(),m_pig->getPos(),
                                       bullet1->getRadius(), m_pig->getSize());
  bool collide2 = bulletPigCollision(bullet2->getPos(),m_pig->getPos(),
                                       bullet2->getRadius(), m_pig->getSize());
  bool collide3 = bulletPigCollision(bullet3->getPos(),m_pig->getPos(),
                                       bullet3->getRadius(), m_pig->getSize());
  bool collide4 = bulletPigCollision(bullet4->getPos(),m_pig->getPos(),
                                       bullet4->getRadius(), m_pig->getSize());
  bool collide5 = bulletPigCollision(bullet5->getPos(),m_pig->getPos(),
                                       bullet5->getRadius(), m_pig->getSize());
  bool collide6 = bulletPigCollision(bullet6->getPos(),m_pig->getPos(),
                                       bullet6->getRadius(), m_pig->getSize());
  bool collide7 = bulletPigCollision(bullet7->getPos(),m_pig->getPos(),
                                       bullet7->getRadius(), m_pig->getSize());
  bool collide8 = bulletPigCollision(bullet8->getPos(),m_pig->getPos(),
                                       bullet8->getRadius(), m_pig->getSize());
  bool collide9 = bulletPigCollision(bullet9->getPos(),m_pig->getPos(),
                                       bullet9->getRadius(), m_pig->getSize());
  if(collide1==true)
  {
      if (counter1 == 1)
      {
          m_pig->health -=1;
      }
      m_pig->getPos() = ngl::Vec3 (0, 0, 30);
      counter1++;
      std::cout << "health: " <<m_pig->health<<std::endl;
  }
//----------------------------------------------------------------------------------------------------------------------
  else if (collide1==false)
  {
      counter1 = 1;
  }
//----------------------------------------------------------------------------------------------------------------------
  if(collide2==true)
  {
      if (counter2 == 1)
      {
          m_pig->health -=1;
      }
      m_pig->getPos() = ngl::Vec3 (0, 0, 30);
      counter2++;
      std::cout << "health: " <<m_pig->health<<std::endl;
  }
//----------------------------------------------------------------------------------------------------------------------
  else if (collide2==false)
  {
      counter2 = 1;
  }
  std::cout << "counter: " <<counter2<<std::endl;
//----------------------------------------------------------------------------------------------------------------------
  if(collide3==true)
  {
      if (counter3 == 1)
      {
          m_pig->health -=1;
      }
      m_pig->getPos() = ngl::Vec3 (0, 0, 30);
      counter3++;
      std::cout << "health: " <<m_pig->health<<std::endl;
  }
//----------------------------------------------------------------------------------------------------------------------
  else if (collide3==false)
  {
      counter3 = 1;
  }
  std::cout << "counter: " <<counter3<<std::endl;
//----------------------------------------------------------------------------------------------------------------------
  if(collide4==true)
  {
      if (counter4 == 1)
      {
          m_pig->health -=1;
      }
      m_pig->getPos() = ngl::Vec3 (0, 0, 30);
      counter4++;
      std::cout << "health: " <<m_pig->health<<std::endl;
  }
//----------------------------------------------------------------------------------------------------------------------
  else if (collide4 == false)
  {
      counter4 = 1;
  }
//----------------------------------------------------------------------------------------------------------------------
  if(collide5==true)
  {
      if (counter5 == 1)
      {
          m_pig->health -=1;
      }
      m_pig->getPos() = ngl::Vec3 (0, 0, 30);
      counter5++;
      std::cout << "health: " <<m_pig->health<<std::endl;
  }
//----------------------------------------------------------------------------------------------------------------------
  else if (collide5==false)
  {
      counter5 = 1;
  }
//----------------------------------------------------------------------------------------------------------------------
  if(collide6==true)
  {
      if (counter6 == 1)
      {
          m_pig->health -=1;
      }
      m_pig->getPos() = ngl::Vec3 (0, 0, 30);
      counter6++;
      std::cout << "health: " <<m_pig->health<<std::endl;
  }
//----------------------------------------------------------------------------------------------------------------------
  else if (collide6==false)
  {
      counter6 = 1;
  }
//----------------------------------------------------------------------------------------------------------------------
  if(collide7==true)
  {
      if (counter7 == 1)
      {
          m_pig->health -=1;
      }
      m_pig->getPos() = ngl::Vec3 (0, 0, 30);
      counter7++;
      std::cout << "health: " <<m_pig->health<<std::endl;
  }
//----------------------------------------------------------------------------------------------------------------------
  else if (collide7==false)
  {
      counter7 = 1;
  }
//----------------------------------------------------------------------------------------------------------------------
  if(collide8==true)
  {
      if (counter8 == 1)
      {
          m_pig->health -=1;
      }
      m_pig->getPos() = ngl::Vec3 (0, 0, 30);
      counter8++;
      std::cout << "health: " <<m_pig->health<<std::endl;
  }
//----------------------------------------------------------------------------------------------------------------------
  else if (collide8==false)
  {
      counter8 = 1;
  }
//----------------------------------------------------------------------------------------------------------------------
  if(collide9==true)
  {
      if (counter9 == 1)
      {
          m_pig->health -=1;
      }
      m_pig->getPos() = ngl::Vec3 (0, 0, 30);
      counter9++;
      std::cout << "health: " <<m_pig->health<<std::endl;
  }
//----------------------------------------------------------------------------------------------------------------------
  else if (collide9==false)
  {
      counter9 = 1;
  }
}
//The following functions were originally written by Jon Macey:
void NGLDraw::mouseMoveEvent (const SDL_MouseMotionEvent &_event)
{
  if(m_rotate && _event.state &SDL_BUTTON_LMASK)
  {
    int diffx=_event.x-m_origX;
    int diffy=_event.y-m_origY;
    m_spinXFace += (float) 0.5f * diffy;
    m_spinYFace += (float) 0.5f * diffx;
    m_origX = _event.x;
    m_origY = _event.y;
    draw();
  }
  // right mouse translate code
  else if(m_translate && _event.state &SDL_BUTTON_RMASK)
  {
    int diffX = (int)(_event.x - m_origXPos);
    int diffY = (int)(_event.y - m_origYPos);
    m_origXPos=_event.x;
    m_origYPos=_event.y;
    m_modelPos.m_x += INCREMENT * diffX;
    m_modelPos.m_y -= INCREMENT * diffY;
    draw();
  }
}
//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::mousePressEvent (const SDL_MouseButtonEvent &_event)
{
  // this method is called when the mouse button is pressed in this case we
  // store the value where the maouse was clicked (x,y) and set the Rotate flag to true
  if(_event.button == SDL_BUTTON_LEFT)
  {
    m_origX = _event.x;
    m_origY = _event.y;
    m_rotate =true;
  }
  // right mouse translate mode
  else if(_event.button == SDL_BUTTON_RIGHT)
  {
    m_origXPos = _event.x;
    m_origYPos = _event.y;
    m_translate=true;
  }
}
//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::mouseReleaseEvent (const SDL_MouseButtonEvent &_event)
{
  // this event is called when the mouse button is released
  // we then set Rotate to false
  if (_event.button == SDL_BUTTON_LEFT)
  {
    m_rotate=false;
  }
  // right mouse translate mode
  if (_event.button == SDL_BUTTON_RIGHT)
  {
    m_translate=false;
  }
}
//----------------------------------------------------------------------------------------------------------------------
void NGLDraw::wheelEvent(const SDL_MouseWheelEvent &_event)
{
//----------------------------------------------------------------------------------------------------------------------
  // check the diff of the wheel position (0 means no change)
  if(_event.y > 0)
  {
    m_modelPos.m_z+=ZOOM;
    this->draw();
  }
  else if(_event.y <0 )
  {
    m_modelPos.m_z-=ZOOM;
    draw();
  }

  // check the diff of the wheel position (0 means no change)
  if(_event.x > 0)
  {
    m_modelPos.m_x-=ZOOM;
    draw();
  }
  else if(_event.x <0 )
  {
    m_modelPos.m_x+=ZOOM;
    draw();
  }
}
//end of functions
//----------------------------------------------------------------------------------------------------------------------
//update every frame:
void NGLDraw::update()
{
  draw();
  m_pig->move();
  m_pig->boundary();
  checkPigCoinCollision();
  checkBulletPigCollision();
 }
//----------------------------------------------------------------------------------------------------------------------
