#include <QObject>
#include <vector>
#include <memory>


#include <stdio.h>


#include <library/Common.h>
using namespace Common;

#include <QGLShaderProgram>
#include <QOpenGLTexture>

#include <QFile>
#include <QRegularExpression>
#include <QDebug>
#include <QString>
#include <QStringList>

#include <Modelling/TG/TG.h>
#include <Modelling/Animation.h>
#include <Modelling/Objects/Cara.h>
#include "Modelling/Objects/Mesh.h"

const int NumVertices = 3; //(1 faces)(2 triangles/face)(3 vertices/triangle)

typedef vec4  color4;
typedef vec4  point4;

class Plane:public Mesh
{
  public:
      Plane();
      Plane(int an, int al, int profu, GLfloat x0, GLfloat y0, GLfloat z0);
      ~Plane();
      void make();
      void toGPU(QGLShaderProgram *program);
      void draw();
      void aplicaTG(mat4 m);

  private:

      void quad( int a);

      int a; // amplada
      int h; // alcada
      int p; // profunditat
      GLdouble xorig, yorig, zorig;

      point4 vertices[4]; // 8 vertexs del Plane
      color4 vertex_colors[8]; // 8 colors RGBA associats a cada vertex

      int Index;
      point4 points[NumVertices]; // 36 punts: Plane triangulat
      color4 colors[NumVertices]; // colors en aquests punts

      GLuint buffer;
};

