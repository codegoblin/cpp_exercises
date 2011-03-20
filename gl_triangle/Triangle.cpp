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

GLfloat blockSize = 0.3f;

GLBatch triangleBatch;
GLBatch triangleBatch2;
GLBatch triangleBatch3;
GLShaderManager shaderManager;

GLfloat vVerts[] =  { 
  -blockSize, 0.0f, 0.0f,
  blockSize, 0.0f, 0.0f,
  0.0f, ( blockSize * 2 ), 0.0f
};

GLfloat vVerts2[] =  { 
  -( blockSize * 2 ), -( blockSize * 2 ), 0.0f,
  0.0f, -( blockSize * 2 ), 0.0f,
  -blockSize, 0.0f, 0.0f
};

GLfloat vVerts3[] =  { 
  0.0f, -( blockSize * 2 ), 0.0f,
  ( blockSize * 2 ), -( blockSize * 2 ), 0.0f,
  blockSize, 0.0f, 0.0f
};

void ChangeSize( int w, int h )
{
  glViewport(0, 0, w, h);
}

// Respond to arrow keys by moving the camera frame of reference
void BounceTri(void)
{  
  GLfloat blockX = vVerts2[0];   // Upper left X
  GLfloat blockY = vVerts[7];  // Upper left Y
  
	static GLfloat xDir = 0.5f;
	static GLfloat yDir = 0.4f;
  
	GLfloat stepSize = 0.002f;
  
  blockY += stepSize * yDir;
	blockX += stepSize * xDir;
  
  // Collision detection
	if(blockX < -1.0f) { blockX = -1.0f; xDir *= -1.0f; }
	if(blockX > (1.0f - blockSize * 4)) { blockX = 1.0f - blockSize * 4; xDir *= -1.0f; }
	if(blockY < -1.0f + blockSize * 4)  { blockY = -1.0f + blockSize * 4; yDir *= -1.0f; }
	if(blockY > 1.0f) { blockY = 1.0f; yDir *= -1.0f; }
  
  // Recalculate vertex positions
  
  //Triangle 1
  vVerts[0] = blockX + blockSize;
  vVerts[1] = blockY - ( blockSize * 2 );
	
  vVerts[3] = blockX + ( blockSize * 3 );
  vVerts[4] = blockY - ( blockSize * 2 );
	
  vVerts[6] = blockX + ( blockSize * 2 );
  vVerts[7] = blockY;
  
  //Triangle 2
  vVerts2[0] = blockX;
  vVerts2[1] = blockY - ( blockSize * 4 );
	
  vVerts2[3] = blockX + ( blockSize * 2 );
  vVerts2[4] = blockY - ( blockSize * 4 );
	
  vVerts2[6] = blockX + blockSize;
  vVerts2[7] = blockY - ( blockSize * 2 );
  
  //Triangle 3
  vVerts3[0] = blockX + ( blockSize * 2 );
  vVerts3[1] = blockY - ( blockSize * 4 );
	
  vVerts3[3] = blockX + ( blockSize * 4 );
  vVerts3[4] = blockY - ( blockSize * 4 );
	
  vVerts3[6] = blockX + ( blockSize * 3 );
  vVerts3[7] = blockY - ( blockSize * 2 );
  
  triangleBatch.CopyVertexData3f( vVerts );
  triangleBatch2.CopyVertexData3f( vVerts2 );
  triangleBatch3.CopyVertexData3f( vVerts3 );  
}

void SetupRC( )
{
  //Black Background
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

  shaderManager.InitializeStockShaders( );

  // Load up a triangle
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
  
  BounceTri( );
	glutPostRedisplay( ); // Redraw
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