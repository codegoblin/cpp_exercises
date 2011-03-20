//
//  Triangle.cpp
//  Triangle
//
//  Created by Cody Johnston on 3/19/11.
//  No Copyright. Just use it dawg.
//

#include <GLTools.h> // OpenGL Toolkit
#include <GLShaderManager.h> // Shader Manager Wut

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLBatch triangleBatch;
GLBatch triangleBatch2;
GLBatch triangleBatch3;
GLShaderManager shaderManager;

void ChangeSize( int w, int h )
{
  glViewport(0, 0, w, h);
}

void SetupRC( )
{
  //Black Background
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

  shaderManager.InitializeStockShaders( );

  // Load up a triangle
  GLfloat vVerts[] =  { 
    -0.5f, 0.0f, 0.0f,
    0.5f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f
  };
  
  GLfloat vVerts2[] =  { 
    -1.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    -0.5f, 0.0f, 0.0f
  };
  
  GLfloat vVerts3[] =  { 
    0.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.5f, 0.0f, 0.0f
  };

  triangleBatch.Begin( GL_TRIANGLES, 3 );
  triangleBatch.CopyVertexData3f( vVerts );
  triangleBatch.End( );
  
  triangleBatch2.Begin( GL_TRIANGLES, 3 );
  triangleBatch2.CopyVertexData3f( vVerts2 );
  triangleBatch2.End( );
  
  triangleBatch3.Begin( GL_TRIANGLES, 3 );
  triangleBatch3.CopyVertexData3f( vVerts3 );
  triangleBatch3.End( );
}

void RenderScene( void )
{
  // Clear the window with current clearing color
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
  GLfloat vYellow[] = { 5.0f, 5.0f, 0.0f, 1.0f };
  shaderManager.UseStockShader( GLT_SHADER_IDENTITY, vYellow );
  triangleBatch.Draw( );
  triangleBatch2.Draw( );
  triangleBatch3.Draw( );
  
  // Buffer swap and display back buffer
  glutSwapBuffers( );
}

int main( int argc, char* argv[] )
{
  gltSetWorkingDirectory( argv[0] );
  
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL );
  glutInitWindowSize( 800, 600 );
  glutCreateWindow( "Triangle" );
  glutReshapeFunc( ChangeSize );
  glutDisplayFunc( RenderScene );
  
  GLenum err = glewInit( );
  
  if ( GLEW_OK != err )
  {
    fprintf( stderr, "GLEW Error: %s\n", glewGetErrorString( err ) );
    return 1;
  }
  
  SetupRC( );
  
  glutMainLoop( );
  return( 0 );
}