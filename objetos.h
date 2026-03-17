#pragma once
#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




/*------------------------ CREAR OBJETOS ------------------------*/
unsigned int VAOEjes;
unsigned int VAOCubo;
unsigned int VAOPlano;
unsigned int VAOCilindro;
unsigned int VAOSkybox;


void crearPlano() {
    unsigned int VBO, EBO;

    // Vértices de un plano simple con normales y coordenadas de textura
    float vertices[] = {
        // Posiciones          // Normales             // Coordenadas de textura
        -10.0f, 0.0f, -10.0f,  0.0f, 1.0f, 0.0f,      0.0f, 0.0f,
         10.0f, 0.0f, -10.0f,  0.0f, 1.0f, 0.0f,      30, 0.0f,
         10.0f, 0.0f,  10.0f,  0.0f, 1.0f, 0.0f,      30, 30,
        -10.0f, 0.0f,  10.0f,  0.0f, 1.0f, 0.0f,      0.0f, 30
    };

    unsigned int indices[] = {
        0, 2, 1,
        0, 3, 2
    };

    glGenVertexArrays(1, &VAOPlano);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAOPlano);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Posición - atributo 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normales - atributo 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Coordenadas de textura - atributo 2
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void crearEjes() {
    unsigned int VBO, EBO;
    float vertices[] = {
        //Vertices           //Colores
        0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f, // origen
        5.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f, // x
        0.0f, 5.0f, 0.0f,    0.0f, 1.0f, 0.0f, // y
        0.0f, 0.0f, 5.0f,    0.0f, 0.0f, 1.0f  // z
    };
    unsigned int indices[] = {
        0, 1,    // x
        0, 2,    // y
        0, 3     // z
    };

    glGenVertexArrays(1, &VAOEjes);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAOEjes);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void crearCilindro() {
    unsigned int VBO, EBO;

    const unsigned int segments = 32;
    const float radius = 1.0f;
    const float height = 1.5f;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // Formato de vértice: x, y, z, nx, ny, nz, s, t
    // Donde (s, t) son las coordenadas de textura

    // Centro de la base inferior
    vertices.push_back(0.0f);      // x
    vertices.push_back(0.0f);      // y
    vertices.push_back(0.0f);      // z
    vertices.push_back(0.0f);      // nx
    vertices.push_back(-1.0f);     // ny
    vertices.push_back(0.0f);      // nz
    vertices.push_back(0.5f);      // s (coordenada de textura)
    vertices.push_back(0.5f);      // t (coordenada de textura)

    // Centro de la tapa superior
    vertices.push_back(0.0f);      // x
    vertices.push_back(height);    // y
    vertices.push_back(0.0f);      // z
    vertices.push_back(0.0f);      // nx
    vertices.push_back(1.0f);      // ny
    vertices.push_back(0.0f);      // nz
    vertices.push_back(0.5f);      // s
    vertices.push_back(0.5f);      // t

    // Vértices para la circunferencia (tanto para tapas como para paredes)
    for (unsigned int i = 0; i <= segments; ++i) {
        float angle = 2.0f * glm::pi<float>() * i / segments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        // Coordenadas de textura para este ángulo
        float s = static_cast<float>(i) / segments;

        // Para las tapas: coordenadas de textura basadas en posición
        float s_cap = (x / (2 * radius)) + 0.5f;
        float t_cap = (z / (2 * radius)) + 0.5f;

        // Normalizar las coordenadas para obtener la normal correcta para las paredes
        float nx = cos(angle);  // Normal normalizada en X
        float nz = sin(angle);  // Normal normalizada en Z

        // Vértice para la base (y=0)
        vertices.push_back(x);             // x
        vertices.push_back(0.0f);          // y
        vertices.push_back(z);             // z
        vertices.push_back(0.0f);          // nx
        vertices.push_back(-1.0f);         // ny
        vertices.push_back(0.0f);          // nz
        vertices.push_back(s_cap);         // s (mapeado circular)
        vertices.push_back(t_cap);         // t (mapeado circular)

        // Vértice para la tapa superior (y=height)
        vertices.push_back(x);             // x
        vertices.push_back(height);        // y
        vertices.push_back(z);             // z
        vertices.push_back(0.0f);          // nx
        vertices.push_back(1.0f);          // ny
        vertices.push_back(0.0f);          // nz
        vertices.push_back(s_cap);         // s (mapeado circular)
        vertices.push_back(1.0f - t_cap);  // t (mapeado circular invertido para mejor orientación)

        // Vértice para la pared con normal hacia afuera (inferior)
        vertices.push_back(x);             // x
        vertices.push_back(0.0f);          // y
        vertices.push_back(z);             // z
        vertices.push_back(nx);            // nx (normal normalizada)
        vertices.push_back(0.0f);          // ny
        vertices.push_back(nz);            // nz
        vertices.push_back(s);             // s (mapeado cilíndrico)
        vertices.push_back(0.0f);          // t (base de la pared)

        // Vértice para la pared con normal hacia afuera (superior)
        vertices.push_back(x);             // x
        vertices.push_back(height);        // y
        vertices.push_back(z);             // z
        vertices.push_back(nx);            // nx (misma normal que el vértice inferior)
        vertices.push_back(0.0f);          // ny
        vertices.push_back(nz);            // nz
        vertices.push_back(s);             // s (mapeado cilíndrico)
        vertices.push_back(1.0f);          // t (tope de la pared)
    }

    // Índices para la base inferior
    for (unsigned int i = 0; i < segments; ++i) {
        indices.push_back(0);  // Centro de la base
        indices.push_back(2 + 4 * i);  // Vértice actual
        indices.push_back(2 + 4 * ((i + 1) % segments));  // Siguiente vértice
    }

    // Índices para la tapa superior
    for (unsigned int i = 0; i < segments; ++i) {
        indices.push_back(1);  // Centro de la tapa superior
        indices.push_back(3 + 4 * ((i + 1) % segments));  // Siguiente vértice
        indices.push_back(3 + 4 * i);  // Vértice actual
    }

    // Índices para las paredes laterales
    for (unsigned int i = 0; i < segments; ++i) {
        unsigned int base = 4 + 4 * i;  // Base del vértice actual
        unsigned int next_base = 4 + 4 * ((i + 1) % segments);  // Base del siguiente vértice

        // Primer triángulo
        indices.push_back(base - 2);  // Inferior actual
        indices.push_back(base - 1);  // Superior actual
        indices.push_back(next_base - 2);  // Inferior siguiente

        // Segundo triángulo
        indices.push_back(next_base - 2);  // Inferior siguiente
        indices.push_back(base - 1);  // Superior actual
        indices.push_back(next_base - 1);  // Superior siguiente
    }

    // Calcular número de vértices e índices para debug
    std::cout << "Cilindro: " << vertices.size() / 8 << " vértices, " << indices.size() << " índices" << std::endl;

    // Configurar VAO, VBO y EBO
    glGenVertexArrays(1, &VAOCilindro);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAOCilindro);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Definir el stride como 8 floats (posición + normal + textura)
    int stride = 8 * sizeof(float);

    // Posición (x, y, z) - attribute 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    // Normal (nx, ny, nz) - attribute 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Coordenadas de textura (s, t) - attribute 2
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void crearCubo() {
    unsigned int VBO, EBO;
    // Vértices del cubo con normales correctas y coordenadas de textura
    float vertices[] = {
        // Posiciones              // Normales (apuntando hacia afuera)           // Coordenadas de textura
        // Cara frontal (Z negativo)
        -0.5f, -0.5f, -0.5f,      0.0f,  0.0f, -1.0f,       0.0f, 0.0f,  // Vértice 0
         0.5f, -0.5f, -0.5f,      0.0f,  0.0f, -1.0f,       1.0f, 0.0f,  // Vértice 1
         0.5f,  0.5f, -0.5f,      0.0f,  0.0f, -1.0f,       1.0f, 1.0f,  // Vértice 2
        -0.5f,  0.5f, -0.5f,      0.0f,  0.0f, -1.0f,       0.0f, 1.0f,  // Vértice 3
        // Cara trasera (Z positivo)
        -0.5f, -0.5f,  0.5f,      0.0f,  0.0f,  1.0f,       0.0f, 0.0f,  // Vértice 4
         0.5f, -0.5f,  0.5f,      0.0f,  0.0f,  1.0f,       1.0f, 0.0f,  // Vértice 5
         0.5f,  0.5f,  0.5f,      0.0f,  0.0f,  1.0f,       1.0f, 1.0f,  // Vértice 6
        -0.5f,  0.5f,  0.5f,      0.0f,  0.0f,  1.0f,       0.0f, 1.0f,  // Vértice 7
        // Cara izquierda (X negativo)
        -0.5f, -0.5f, -0.5f,     -1.0f,  0.0f,  0.0f,       0.0f, 0.0f,  // Vértice 8
        -0.5f, -0.5f,  0.5f,     -1.0f,  0.0f,  0.0f,       1.0f, 0.0f,  // Vértice 9
        -0.5f,  0.5f,  0.5f,     -1.0f,  0.0f,  0.0f,       1.0f, 1.0f,  // Vértice 10
        -0.5f,  0.5f, -0.5f,     -1.0f,  0.0f,  0.0f,       0.0f, 1.0f,  // Vértice 11
        // Cara derecha (X positivo)
         0.5f, -0.5f, -0.5f,      1.0f,  0.0f,  0.0f,       0.0f, 0.0f,  // Vértice 12
         0.5f, -0.5f,  0.5f,      1.0f,  0.0f,  0.0f,       1.0f, 0.0f,  // Vértice 13
         0.5f,  0.5f,  0.5f,      1.0f,  0.0f,  0.0f,       1.0f, 1.0f,  // Vértice 14
         0.5f,  0.5f, -0.5f,      1.0f,  0.0f,  0.0f,       0.0f, 1.0f,  // Vértice 15
         // Cara inferior (Y negativo)
         -0.5f, -0.5f, -0.5f,      0.0f, -1.0f,  0.0f,      0.0f, 0.0f,  // Vértice 16
          0.5f, -0.5f, -0.5f,      0.0f, -1.0f,  0.0f,      1.0f, 0.0f,  // Vértice 17
          0.5f, -0.5f,  0.5f,      0.0f, -1.0f,  0.0f,      1.0f, 1.0f,  // Vértice 18
         -0.5f, -0.5f,  0.5f,      0.0f, -1.0f,  0.0f,      0.0f, 1.0f,  // Vértice 19
         // Cara superior (Y positivo)
         -0.5f,  0.5f, -0.5f,      0.0f,  1.0f,  0.0f,      0.0f, 0.0f,  // Vértice 20
          0.5f,  0.5f, -0.5f,      0.0f,  1.0f,  0.0f,      1.0f, 0.0f,  // Vértice 21
          0.5f,  0.5f,  0.5f,      0.0f,  1.0f,  0.0f,      1.0f, 1.0f,  // Vértice 22
         -0.5f,  0.5f,  0.5f,      0.0f,  1.0f,  0.0f,      0.0f, 1.0f,  // Vértice 23
    };

    unsigned int indices[] = {
        // Cara frontal (Z negativo)
        0, 1, 2,  0, 2, 3,
        // Cara trasera (Z positivo)
        4, 6, 5,  4, 7, 6,
        // Cara izquierda (X negativo)
        8, 9, 10,  8, 10, 11,
        // Cara derecha (X positivo)
        12, 13, 14,  12, 14, 15,
        // Cara superior (Y positivo)
        20, 21, 22,  20, 22, 23,
        // Cara inferior (Y negativo)
        16, 18, 17,  16, 19, 18
    };

    // Generar VAO, VBO y EBO
    glGenVertexArrays(1, &VAOCubo);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAOCubo);

    // Vértices e índices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Atributo 0: Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atributo 1: Normales
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Atributo 2: Coordenadas de textura
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



void crearSkybox() {

    float skyboxVertices[] =
    {
        //   Coordinates
        -1.0f, -1.0f,  1.0f,//        7--------6
         1.0f, -1.0f,  1.0f,//       /|       /|
         1.0f, -1.0f, -1.0f,//      4--------5 |
        -1.0f, -1.0f, -1.0f,//      | |      | |
        -1.0f,  1.0f,  1.0f,//      | 3------|-2
         1.0f,  1.0f,  1.0f,//      |/       |/
         1.0f,  1.0f, -1.0f,//      0--------1
        -1.0f,  1.0f, -1.0f
    };

    unsigned int skyboxIndices[] =
    {
        // Right
        1, 2, 6,
        6, 5, 1,
        // Left
        0, 4, 7,
        7, 3, 0,
        // Top
        4, 5, 6,
        6, 7, 4,
        // Bottom
        0, 3, 2,
        2, 1, 0,
        // Back
        0, 1, 5,
        5, 4, 0,
        // Front
        3, 7, 6,
        6, 2, 3
    };

    unsigned int skyboxVBO, skyboxEBO;
    glGenVertexArrays(1, &VAOSkybox);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);
    glBindVertexArray(VAOSkybox);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    // All the faces of the cubemap (make sure they are in this exact order)
    std::string facesCubemap[6] =
    {
        "textures/right.jpg",
        "textures/left.jpg",
        "textures/top.jpg",
        "textures/bottom.jpg",
        "textures/front.jpg",
        "textures/back.jpg"
    };

    unsigned int texturaID = cargarTextura("Debug/textures/front.jpg");
    verificarEstadoTextura(texturaID, "Debug/textures/front.jpg");
    texturaID = cargarTextura("Debug/textures/left.jpg");
    verificarEstadoTextura(texturaID, "Debug/textures/left.jpg");



    // Creates the cubemap texture object

    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // These are very important to prevent seams
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // This might help with seams on some systems
    //glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    // Cycles through all the textures and attaches them to the cubemap object
    for (unsigned int i = 0; i < 6; i++)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D
            (
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
            stbi_image_free(data);
        }
    }

}





#pragma once