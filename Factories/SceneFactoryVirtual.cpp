#include "SceneFactoryVirtual.h"


SceneFactoryVirtual::SceneFactoryVirtual():SceneFactory()
{
}

shared_ptr<Scene> SceneFactoryVirtual::createScene(Serializable::SaveFormat saveFormat,
                                                   QString filename) {

    scene= make_shared<Scene>();
    load(saveFormat, filename);
    print(0);

    return scene;
}

shared_ptr<Scene> SceneFactoryVirtual::createScene() {
    scene= make_shared<Scene>();
    //  Test amb una esfera. Provar sense fitxers
    //  Fase 1: Aquest codi es pot modificar per a provar
    //  la visualització de diferents primitives bàsiques
    //this->OneSphere(scene);
    return scene;
}
bool SceneFactoryVirtual::load(SceneFactory::SaveFormat saveFormat, QString nameFile)
{

    QFile loadFile(nameFile);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open the virtual scene file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonParseError error;
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData, &error));


    if (loadDoc.isNull()) {
        qWarning("Parse error in json virtual scene file.");
        return false;
    }
    QJsonObject object = loadDoc.object();

    read(object);

    QTextStream(stdout) << "Loaded virtual scene using "
                        << (saveFormat != Json ? "CBOR" : "JSON") << "...\n";
    return true;
}

void SceneFactoryVirtual::read(const QJsonObject &json)
{

    if (json.contains("objects") && json["objects"].isArray()) {
            QJsonArray objectsArray = json["objects"].toArray();

            for (int objectIndex = 0; objectIndex < objectsArray.size(); objectIndex++) {
                QJsonObject objectObject = objectsArray[objectIndex].toObject();

                if (objectObject.contains("type") && objectObject["type"].isString()&& objectObject["type"] == "MESH") {
                    if(objectObject.contains("objFileName") && objectObject["objFileName"].isString()){
                        QString objStr = objectObject["objFileName"].toString();


                        auto obj = make_shared<Mesh>(1000000, objStr);
                        scene->addObject(obj);
                    }


            }
            }
     }

}
void SceneFactoryVirtual:: write(QJsonObject &json) const
{

}

void SceneFactoryVirtual::print(int indentation) const
{

 }


