#pragma once



/*------------------------ Clase basica para las colisiones ------------------------*/
struct AABB {
    glm::vec3 position; // centro
    glm::vec3 halfSize; // la mitad del tamaño (ancho/2, largo/2)
};




/*------------------------ FUNCIONES ------------------------*/
void dibujarRetroceso();

void dibujarAABB(const AABB& aabb, glm::mat4 view, glm::vec3 color);

glm::vec3 obtenerPuntoCirculo(float centroX, float centroZ, float rotacion, float angulo, float radio);

glm::vec3 obtenerPuntoEsfera(const glm::vec3& centro, float rotacionHorizontal, float anguloHorizontal, float anguloVertical, float radio);

bool checkCollision(const AABB& a, const AABB& b);

bool revisarColisiones(const AABB& tanqueAABB);

void dispararTanque();

void actualizarRecarga();

void actualizarProyectiles(glm::mat4 view);

void moverTanque(bool adelante, float rotacion, float velocidad);

void actualizarRetroceso(float deltaTime);

#pragma once
