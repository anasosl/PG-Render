#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "vec3.h"

using namespace std;

vector<vector<vec3>> getTexture() {
    // Abre o arquivo PPM
    ifstream file("image.ppm");

    if (!file) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return {};
    }

    // Lê o cabeçalho PPM
    string header;
    getline(file, header);

    // Lê as dimensões da imagem
    int largura, altura, max_valor_cor;
    file >> largura >> altura >> max_valor_cor;

    // Lê os pixels da imagem
    vector<vec3> pp (500);
    vector<vector<vec3>> pixels(500, pp);

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            double r, g, b;
            file >> r >> g >> b;
            pixels[i][j] = vec3(r,g,b);
        }
    }

    return pixels;
}