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

#include <windows.h>  // Para PlaySound y otras funciones de Windows
#include <iostream>
#include <mmsystem.h>  // Para PlaySound



void establecerVolumenAl20Porciento() {
    DWORD volumen = MAKELONG(0x3333, 0x3333); // 20% en ambos canales (izq y der)
    waveOutSetVolume(0, volumen);
}


// Variables globales para el manejo de música
bool isMusicPlaying = false;
std::string currentMusicPath = "";


#include <tchar.h>

void reproducirMusicaDeFondo(const char* filePath, bool loop) {
    DWORD flags = SND_FILENAME | SND_ASYNC;
    if (loop) {
        flags |= SND_LOOP;
    }

    std::wstring wFilePath = std::wstring(filePath, filePath + strlen(filePath));
    if (PlaySoundW(wFilePath.c_str(), NULL, flags)) {
        isMusicPlaying = true;
        currentMusicPath = filePath;
        std::cout << "Reproduciendo música: " << filePath << std::endl;
    }
    else {
        std::cerr << "Error al reproducir música: " << filePath << std::endl;
        std::cerr << "Código de error: " << GetLastError() << std::endl;
    }
}


// Función para detener la música
void pararMusica() {
    PlaySound(NULL, NULL, 0);
    isMusicPlaying = false;
    std::cout << "Musica detenida" << std::endl;
}

// Función para cambiar la música
void cambiarMusica(const char* filePath, bool loop = true) {
    pararMusica();
    reproducirMusicaDeFondo(filePath, loop);
}


#pragma once