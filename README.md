# RenderGPU
Segona pràctica de GiVD 2021-22

**Abstract**

En aquesta pràctica hem après a utilitzar mètodes projectius a la GPU(ZBuffer) implementant diferents funcionalitats que fèiem a la pràctica anterior.
Hem aconseguit llegir una escena, passar diferents atributs, siguin materials o  llums, a la GPU per després fer ús en els diferents shaders que tenim. Aquí és on han sorgit la majoria de problemes que hem tingut durant la pràctica. No obstant això, hem dedicat moltes hores i creiem que hem fet una bona pràctica per al nombre de gent que som.


- Fase 1
    - Adaptació a la lectura de fitxers de dades
        - [X] Objectes
            - Hector
        - [X] Escenes virtuals
            - Hector
        - [ ] Escenes de dades Reals 
    - Material
        - [x] Material
            - Marc
    - Light
        - [x] Puntual
            - Andrei  
        - [x] Direccional
            - Andrei    
        - [x] Spotlight
            - Andrei    
        - [x] Ambient Global
            - Andrei i Hector   
    - Shading
        - [X] Depth
            - Hector
        - [X] Phong
            - Hector
        - [X] Gouraud
            - Hector
        - [X] Toon-shading
            - Hector
    - Textures
        - [x] Textura com material en un objecte
            - Marc
        - [ ] Textura al pla base
        

- Fase 2 
    - [ ] Èmfasi de siluetes
    - [ ] Mapping indirecte de textures
    - [ ] Animacions amb dades temporals
    - [ ] Normal mapping
    - [ ] Entorn amb textures
    - [ ] Reflexions
    - [x] Transparències via objectes.
        - Marc
    - [ ] Transparències via environmental mapping.


**Memòria i Screenshots**

- **FASE 1**

    - **Pas 1: Construcció de l’escena virtual**


        Hem conseguit llegir el .json anomentat objects1:
        ![Imgur](https://i.imgur.com/8yavId1.jpg)

        Nomès ens ha sortit virtual data tal i com comentem a anotacions.

    - **Pas 2: Modificació de la classe Material i pas a la GPU dels valors de materials**


        Hem afegit material als objectes. Per a veure aquestes comprovacions hem mirat de llegir de la GPU els valors enviats corresponents a les components.
        Ka = (1,0,0) | Kd = (0, 1, 0) | Ks = (0, 0, 1) | Kt = (1, 1, 0)
        ---|---|---|---
        ![Imgur](https://i.imgur.com/jKgMDDy.png) | ![Imgur](https://i.imgur.com/4pcMivw.png) | ![Imgur](https://i.imgur.com/5qF6DJr.png) | ![Imgur](https://i.imgur.com/SS1N4hI.png)

        Per a shininess = 20 hem dividit shinniness / 20 de tal manera que el vector quedi (0, 1, 1):

        color = vec4(0, material.shininess/20, material.shininess/20, 1.0f);

        <img src="https://i.imgur.com/2V5Hq4V.png" alt="shininess" width="400"/>



    - **Pas 3: Modificació de la classe llum i pas a la GPU**


        Per a comprovar que l'enviament a la GPU i la llegida correcta dels atributs de Light, hem enviat 3 llums a la GPU i hem fet unes comprovacions a l'igual que amb el pas 2, accedint a Id de les diferents llums:

       Les llums han estat definides seguint els seguent constructor:

       auto light = make_shared<PointLight>(vec3 Ia, vec3 Id, vec3 Is, vec4 position, vec3 coeficients);
       Llums | vec3 Ia | vec3 Id | vec3 Is | vec4 Position | vec3 Coeficients
       ---|---|---|---|---|---
       Llum 1 | (0.3f, 0.3f, 0.3f) | (1.0f, 1.0f, 1.0f) | (0.5f, 0.5f, 0.5f) | (0.7f, 0.7f, 0.7f, 1.0f) | (0.0f, 1.0f, 1.0f)
       Llum 2 | (0.3f, 0.3f, 0.3f) | (0.6f, 0.6f, 0.6f) | (0.5f, 0.5f, 0.5f) | (0.2f, 0.2f, 0.2f, 1.0f) | (0.0f, 1.0f ,1.0f)
       Llum 3 | (0.4f, 0.3f, 0.6f) | (0.67f, 0.3f, 0.3f) | (0.2f, 0.2f, 0.2f) | (0.5f, 0.5f, 0.5f, 1.0f) | (0.0f, 1.0f ,1.0f)



        Llum 1 * | Llum 2 ** | Llum 3 *** 
        ---|---|---
        ![Imgur](https://i.imgur.com/H1GV7Nl.png) | ![Imgur](https://i.imgur.com/bfi7KF3.png) | ![Imgur](https://i.imgur.com/20OnoQg.png)


        (*) color = vec4(lights[0].Id[0], lights[0].Id[1], lights[0].Id[2], 1.0f);

        (**) color = vec4(lights[1].Id[0], lights[1].Id[1], lights[1].Id[2], 1.0f);

        (***) color = vec4(lights[2].Id[0], lights[2].Id[1], lights[2].Id[2], 1.0f);



    - **Pas 4: Implementació dels diferents tipus de shading (depth, Gouraud, Phong i toon-shading)**

        En aquest pas hem implementat els diferents tipus de shadings seguint el que teniem a la pràctica 1 i a teoria. A continuació podem veure com surten:
    
        Per a les dades fetes servir en Gourad i Phong, han estat les que ens donaven al pdf del campus anomenat "Escena test + fotos". 
    
    Som conscients que no el toon no acaba de ser el resultat esperat i creiem que és per culpa de les llums, però despres de moltes hores, no hem sapigut solucionar-ho.
    
    
        Depth Shading | Gouraud | Phong Shading | Toon Shading
        ---|---|---|---
        ![Imgur](https://i.imgur.com/m31jMCh.png) | ![Imgur](https://i.imgur.com/f13dh0U.png) | ![Imgur](https://i.imgur.com/1pUuQUY.png) | ![Imgur](https://i.imgur.com/kkkBOJY.png)

    - **Pas 5:  Inclusió de les textures en les teves visualitzacions**

        Per aquest pas hem modificat la clase Mesh per a que suporti textures. en la imatge que es mostra a continuació podem veure com s'aplica la textura 2k.jpg a f16.obj

        <img src="https://i.imgur.com/nCn1PhS.png" alt="drawing" width="400"/>

        Al no haver fet la part de Real Data al pas 1, no hem pogut fer la part de dades geolocalitzades al pla en aquest pas.
    
    
 - **FASE 2:**
    
    - [OPCIONAL] Transparències via objectes.
    
    <img src="https://i.imgur.com/T57lrX7.png" alt="drawing" width="400"/>

    
    **Additional Information**

*(NOTA: Hores de dedicació i problemes que heu tingut fent la pràctica)*

El pas 1 ha portat moltes hores de dedicació (al voltant de 20h) però al final hem decidit no fer la part de realdata, ja que no ens hem ensortit. Simplement, està fet el mètode newDataEscene a la classe build però no hi ha re mes pel fet que com no funcionava hem decidit treure-ho.

En el pas 4, vam estar moltes hores (aproximadament 35) pensant que no ens funcionaven els diferents shaders a causa de errors de programació. Finalment, fent proves, vam concloure en què era un problema de les llums, ja que no tots els atributs arribaven correctament. Degut a això, vam decidir harcodejar les dades. Sabem que encara així no surt del tot correcte però millora molt la versió anterior.
