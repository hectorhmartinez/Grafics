#include "Modelling/Objects/Plane.h"

Plane::Plane():Mesh(100)
{
    qDebug() << "Estic en el constructor del Plane\n";
    // Plane centrat al 0,0,0 amb dimensió 1 a totes les seves arestes
    xorig = -0.5; yorig = -0.50; zorig = -0.5;
    a = 1.0;
    p = 1.0;

    // Vertices of a unit Planee centered at origin, sides aligned with axes
    vertices[0] = point4( -0.5, -0.5,  0.5, 1.0 );
    vertices[1] = point4( -0.5,  0.5,  0.5, 1.0 );
    vertices[2] = point4(  0.5,  0.5,  0.5, 1.0 );
    vertices[3] = point4(  0.5, -0.5,  0.5, 1.0 );



}

// Constructora amb tots els parametres
/*Plane::Plane(int an, int al, int profu, const GLfloat x0, GLfloat y0, GLfloat z0)
{
    qDebug() << "Estic en el constructor parametritzat del Plane\n";
    a = an;
    p = profu;
    xorig = x0;
    yorig = y0;
    zorig = z0;
}*/

// Destructora
Plane::~Plane()
{
}

// quad generates two triangles for each face and assigns colors
//    to the vertices

void Plane::quad( int a)
{
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;

}


// Realitzacio de la geometria del Plane en el vertex array
void Plane::make()
{
    qDebug() << "Estic en el make del Plane\n";
    // generacio de la geometria dels triangles per a visualitzar-lo
    quad(0);

}

// Carrega del Plane a la GPU
void Plane::toGPU(QGLShaderProgram *program){

    qDebug() << "Passo les dades del Plane a la GPU\n";

    // Creació d'un vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Creacio i inicialitzacio d'un buffer object

    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors),
                  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );


    // set up vertex arrays

    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(points)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

// Pintat dels arrays definits del Plane: activació del pipeline de GL
void Plane::draw()
{
   glDrawArrays( GL_TRIANGLES, 0, NumVertices );
}

void Plane::aplicaTG(mat4 m)
{
    point4  transformed_points[NumVertices];

    for ( int i = 0; i < NumVertices; ++i ) {
        transformed_points[i] = m * points[i];
    }

    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    // Actualitzacio del vertex array per a preparar per pintar
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(transformed_points),
                     transformed_points );
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
