#include "Modelling/Objects/Mesh.h"


/**
 * @brief Mesh::Mesh
 * @param npoints
 * @param parent
 */
Mesh::Mesh(int npoints, QObject *parent) : QObject(parent){
    qDebug() << "Constructor 1 mesh.....";
    numPoints = npoints;
    points = new point4[numPoints];
    normals = new point4[numPoints];
    colors = new point4[numPoints];
    textures = new vec2[numPoints];
    canHaveTexture = true;
    hasTexture = false;
 }

/**
 * @brief Mesh::Mesh
 * @param npoints
 * @param n
 */
Mesh::Mesh(int npoints, QString n) : numPoints(npoints){
    qDebug() << "Constructor 2 mesh.....";

    points = new point4[numPoints];
    normals = new point4[numPoints];
    colors = new point4[numPoints];
    textures = new vec2[numPoints];
    canHaveTexture = false;
    hasTexture = false;
    vec3 ambient(0.1f, 0.02f, 0.02f);
    vec3 diffuse(1.0f, 0.2f, 0.2f);
    vec3 specular(1.0f, 1.0f, 1.0f);
    vec3 transparency(0.7f, 0.0f, 0.0f);
    float shininess = 20.0;
    material = make_shared<Material>(ambient, diffuse, specular, transparency, shininess);
    parseObjFile(n);
    make();
}


/**
 * @brief Mesh::~Mesh
 */
Mesh::~Mesh(){
    delete points;
    delete normals;
    delete colors;
    delete textures;
}

/**
 * @brief Mesh::toGPU
 * @param pr
 */
void Mesh::toGPU(shared_ptr<QGLShaderProgram> pr) {
    // TO  DO: A modificar a la fase 1 de la practica 2

    qDebug() << "Obj to GPU.....";

    program = pr;
    // Creació d'un vertex array object

    glGenVertexArrays( 1, &vao );

    // Creacio i inicialitzacio d'un vertex buffer object (VBO)
    glGenBuffers( 1, &buffer );

    // Aqui s'ha de fer el pas de dades a la GPU per si hi ha més d'un objecte
    // Activació a GL del Vertex Buffer Object

    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal passar les normals a la GPU

    glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*Index + sizeof(point4)*Index + sizeof(vec2)*Index, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*Index, points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(point4)*Index, normals);
    glBufferSubData( GL_ARRAY_BUFFER, 2*sizeof(point4)*Index, sizeof(vec2)*Index, textures);

    // set up vertex arrays
    glBindVertexArray( vao );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(point4)*Index));
    glEnableVertexAttribArray(1);

    if (canHaveTexture){
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,  (void*)(2*sizeof(point4)*Index));
        glEnableVertexAttribArray(2);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);

    }

}


/**
 * Pintat en la GPU.
 * @brief Mesh::draw
 */
void Mesh::draw(){
    qDebug() << "Draw MESH.....";

    // Aqui s'ha de fer el pas de dades a la GPU per si hi ha més d'un objecte
    // Activació a GL del Vertex Buffer Object.
    material->toGPU(program);
    if(hasTexture){
        this->toGPUTexture(program);
    }
    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal activar també les normals  a la GPU
    glBindVertexArray( vao );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    if (canHaveTexture)
        glEnableVertexAttribArray(2);


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, Index );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    if (canHaveTexture)
        glDisableVertexAttribArray(2);

}

/**
 * @brief Mesh::make
 */
void Mesh::make(){
    qDebug() << "Make MESH.....";

    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal calcular la normal a cada vertex a la CPU

    static vec3  base_colors[] = {
        vec3( 1.0, 0.0, 0.0 ),
        vec3( 0.0, 1.0, 0.0 ),
        vec3( 0.0, 0.0, 1.0 ),
        vec3( 1.0, 1.0, 0.0 )
    };

    Index = 0;
    if(canHaveTexture){
        qDebug()<<"Texture";
    }else{
        qDebug()<<"NoTexture";
    }
    for(unsigned int i=0; i<cares.size(); i++){
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){
            points[Index] = vertexs[cares[i].idxVertices[j]];
            normals[Index] = normalsVertexs[cares[i].idxNormals[j]];
            if (canHaveTexture){
                textures[Index] = textVertexs[cares[i].idxTextures[j]];
            }
            Index++;
        }
    }
}



/**
 * @brief Mesh::setTexture
 * @param t
 */
void Mesh::setTexture(shared_ptr<QOpenGLTexture> t){
   texture = t;
   hasTexture = true;
   initTexture();
}

/**
 * @brief Mesh::initTexture
 */
void Mesh::initTexture()
 {
    // TO DO: A implementar a la fase 1 de la practica 2
    // Cal inicialitzar la textura de l'objecte: veure l'exemple del CubGPUTextura
    qDebug() << "Initializing textures...";
    glActiveTexture(GL_TEXTURE0);
    texture->setWrapMode(QOpenGLTexture::Repeat);
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    texture->bind(0);

    qDebug()<<"Textura carregada";
 }

/**
 * @brief Mesh::toGPUTexture
 * @param pr
 */
void Mesh::toGPUTexture(shared_ptr<QGLShaderProgram> pr){
    program = pr;
    // S'activa la textura i es passa a la GPU
    if (hasTexture){
        texture->bind(0);
        program->setUniformValue("texMap", 0);
    }
    GLuint glHasTexture = program->uniformLocation("hasTexture");
    glUniform1i(glHasTexture, int(this->hasTexture));

}

/**
 * @brief Mesh::drawTexture
 */
void Mesh::drawTexture(){

}

/**
 * @brief Mesh::parseObjFile
 * @param fileName
 */
void Mesh::parseObjFile(const QString &fileName)
{
    QFile file(fileName);
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            QVector<QVector3D> v, vn;
            QVector<QVector2D> vt;

            while(!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0) {
                    // if it’s a comment
                    if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0)
                    {
                        //qDebug() << line.remove(0, 1).trimmed();
                    }
                    // if it’s a vertex position (v)
                    else if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        vertexs.push_back(point4(lineParts.at(1).toFloat(),
                                           lineParts.at(2).toFloat(),
                                           lineParts.at(3).toFloat(), 1.0f));
                    }

                    // if it’s a normal (vn)
                    else if(lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
                    {
                        normalsVertexs.push_back (point4(lineParts.at(1).toFloat(),
                                            lineParts.at(2).toFloat(),
                                            lineParts.at(3).toFloat(), 0.0f));
                    }

                    // if it’s a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {
                        textVertexs.push_back(vec2(lineParts.at(1).toFloat(),
                                            lineParts.at(2).toFloat()));
                        canHaveTexture = true;
                    }

                    // if it’s face data (f)
                    // there’s an assumption here that faces are all triangles
                    else if(lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
                    {
                        Cara *cara = new Cara();

                        // get points from v array
                        cara->idxVertices.push_back(lineParts.at(1).split("/").at(0).toInt() - 1);
                        cara->idxVertices.push_back(lineParts.at(2).split("/").at(0).toInt() - 1);
                        cara->idxVertices.push_back(lineParts.at(3).split("/").at(0).toInt() - 1);

                        if(textVertexs.size() > 0) // check if really there are any UV coords
                        {
                            cara->idxTextures.push_back( lineParts.at(1).split("/").at(1).toInt() - 1);
                            cara->idxTextures.push_back( lineParts.at(2).split("/").at(1).toInt() - 1);
                            cara->idxTextures.push_back( lineParts.at(3).split("/").at(1).toInt() - 1);
                        }

                        // get normals from vn array
                        cara->idxNormals.push_back( lineParts.at(1).split("/").at(2).toInt() - 1);
                        cara->idxNormals.push_back( lineParts.at(2).split("/").at(2).toInt() - 1);
                        cara->idxNormals.push_back( lineParts.at(3).split("/").at(2).toInt() - 1);


                        // cara->calculaNormal();
                        cares.push_back(*cara);
                    }

                }
            }

            file.close();
        }
    }
}

Capsa3D Mesh::calculCapsa3D()
{
    vec3    pmin, pmax;
    int     i;
    Capsa3D capsa;

    pmin.x = points[0].x;
    pmin.y = points[0].y;
    pmin.z = points[0].z;
    pmax = pmin;
    for(i=1; i<Index; i++) {
        if(points[i].x <pmin[0])
            pmin[0] = points[i].x;
        if(points[i].y <pmin[1])
            pmin[1] = points[i].y;
        if(points[i].z <pmin[2])
            pmin[2] = points[i].z;

        if(points[i].x >pmax[0])
            pmax[0] = points[i].x;
        if(points[i].y >pmax[1])
            pmax[1] = points[i].y;
        if(points[i].z >pmax[2])
            pmax[2] = points[i].z;
    }
    capsa.pmin = pmin;
    capsa.a = pmax[0]-pmin[0];
    capsa.h = pmax[1]-pmin[1];
    capsa.p = pmax[2]-pmin[2];
    return capsa;
}

void Mesh::aplicaTG(shared_ptr<TG> tg){

}

