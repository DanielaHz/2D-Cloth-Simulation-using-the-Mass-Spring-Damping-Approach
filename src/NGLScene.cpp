#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <iostream>
#include <ngl/ShaderLib.h>
#include <ngl/Util.h>

NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("Cloth Simulation");
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
  m_project = ngl::perspective(45.0f, float(_w) / float(_h), 0.01f, 2000.0f);
}


void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::initialize();
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			   // black Background or white?
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  // Cloth is temporarily initialized here until the simulation class is implemented, for now it serves to see if the drawCloth logic works
  m_cloth = std::make_unique<Cloth>(); 

  m_view = ngl::lookAt({620.0f, 360.0f, 1000.0f}, {620.0f, 360.0f, 0.0f}, {0, 1.0f, 0});
  ngl::ShaderLib::loadShader("Mass-SpringShader", "shaders/Mass-SpringVertex.glsl", "shaders/Mass-SpringFragment.glsl");
  m_cloth->initCloth(100,100,30.0f); // 3x3 grid for now
}



void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);

  ngl::ShaderLib::use("Mass-SpringShader");
  ngl::ShaderLib::setUniform("MVP", m_project*m_view);

  // Temporarily created to visualize the drawcloth function
  m_cloth->drawCloth();
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());

  break;
  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}
