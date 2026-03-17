# Proyecto TankOpenGL: Proyecto de Computación Gráfica

Proyecto desarrollado para la asignatura de Computación Gráfica del grado de Ingeniería Informática en la Universidad de Santiago de Compostela (USC). El equipo de desarrollo está compuesto por Iago Feijóo Rey y Jorge González Corbelle.

## Descripción del Proyecto

Aplicación desarrollada en **C++ con OpenGL** que implementa un minijuego de tanques en 3D. El proyecto ha sido desarrollado íntegramente con **Visual Studio 2022** como entorno de desarrollo.

El juego consiste en avanzar por el mapa e intentar destruir todas las torretas en el menor tiempo posible, gestionando munición, energía de boost y distintas cámaras de visualización.

## Contenido del Repositorio

* `Debug/textures/`: Texturas usadas en el proyecto.
* `Debug/audios/`: Pistas de audio usadas en el proyecto.
* `esfera.h`: Geometría auxiliar.
* `shaders.h`: Gestión de shaders OpenGL.
* `presets.h`: Configuraciones y constantes del proyecto.
* `main.cpp`: Punto de entrada y lógica principal del juego.
* `README.md`: Este archivo.

## Controles

**Ajustes**
| Tecla | Acción |
|-------|--------|
| `ESC` | Salir del programa |
| `N` | Apagar el sonido del motor |
| `M` | Encender el sonido del motor |
| `E` | Activar visualización de ejes |
| `B` | Apagar la luz del sol |

**Movimiento**
| Tecla | Acción |
|-------|--------|
| `W` | Avanzar hacia delante (recarga boost) |
| `S` | Retroceder (recarga boost) |
| `A` | Avanzar hacia delante-izquierda |
| `D` | Avanzar hacia delante-derecha |
| `SHIFT` | Boost — solo hacia delante, consume energía |
| `ESPACIO` | Disparar (cooldown 5s, máx. 5 balas) |
| `R` | Recargar al máximo de balas |
| `2` | Alternar vista aérea / normal |
| `Q` | Alternar primera / tercera persona |
| `9` | Reiniciar nivel |

## Requisitos del Sistema

* Windows con Visual Studio 2022
* OpenGL 3.3 o superior
* GLFW, GLEW y GLUT/FreeGLUT (incluidos en el repositorio)
* Tarjeta gráfica con soporte para shaders GLSL

## Contacto

Para cualquier duda o sugerencia, puedes ponerte en contacto con el equipo de desarrollo:

**Iago Feijóo Rey**: iagofeijoorey@gmail.com
* [LinkedIn](https://www.linkedin.com/in/iagofeijoorey/)

**Jorge González Corbelle**: jorgegonzalezcorbelle@gmail.com
* [LinkedIn](https://www.linkedin.com/in/jorgegonzalezcorbelle/)

## Languages and Tools used

<p align="left">
<a href="https://isocpp.org/" target="_blank" rel="noreferrer">
<img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" alt="cplusplus" width="40" height="40"/></a>
<a href="https://www.opengl.org/" target="_blank" rel="noreferrer">
<img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/opengl/opengl-original.svg" alt="opengl" width="40" height="40"/></a>
<a href="https://www.glfw.org/" target="_blank" rel="noreferrer">
<img src="https://www.glfw.org/img/favicon/favicon-196x196.png" alt="glfw" width="40" height="40"/></a>
<a href="https://visualstudio.microsoft.com/" target="_blank" rel="noreferrer">
<img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/visualstudio/visualstudio-plain.svg" alt="visualstudio" width="40" height="40"/></a>
</p>
