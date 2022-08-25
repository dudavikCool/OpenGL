#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <bits/stdc++.h>


struct vertexCoords {
    float x; float y; float z;
    
    vertexCoords(float x, float y, float z) : x(x), y(y), z(z) {};
    vertexCoords(initializer_list<float> li) : x(*(li.begin())), y(*(li.begin() + 1)), z(*(li.begin() + 2)) {};
};


class Mesh {
    public:
    
    vector<float> vertices;
    vector<unsigned short> indices;
    public:

    int verticesBufferSize;
    int indicesBufferSize;
    Mesh(initializer_list<float> verticesInit, initializer_list<unsigned short> indicesInit) : 
                    vertices(verticesInit), indices(indicesInit) {
        verticesBufferSize = vertices.size() * sizeof(float);
        indicesBufferSize = indices.size() * sizeof(int);
    }
    float* getVertices() {
        return &this->vertices[0];
    }
    unsigned short* getIndices() {
        return &this->indices[0];
    }

};


class CubeObject : public Mesh{
    public:

    CubeObject(vertexCoords v1, vertexCoords v2) : 
        Mesh({
            v1.x, v1.y, v1.z,
            v1.x, v2.y, v1.z,
            v1.x, v2.y, v2.z, 
            v1.x, v1.y, v2.z,

            v2.x, v2.y, v2.z, 
            v2.x, v1.y, v2.z,
            v2.x, v1.y, v1.z, 
            v2.x, v2.y, v1.z
        },
        {
            0, 1, 2, // Левая грань
            2, 3, 0, 

            3, 2, 4, // Задняя
            4, 5, 3,

            6, 7, 4, // Правая
            4, 5, 6,

            0, 1, 7, // Передняя
            7, 6, 0,

            1, 2, 4, // Верхняя
            4, 7, 1,

            0, 3, 5, // Нижняя
            5, 6, 0 
        }) {}

};
#endif