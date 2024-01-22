#include "object2D_Tema.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D_Tema::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, -1), color),
        VertexFormat(corner + glm::vec3(length, length, -1), color),
        VertexFormat(corner + glm::vec3(0, length, -1), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D_Tema::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, -1), color),
        VertexFormat(corner + glm::vec3(length, height, -1), color),
        VertexFormat(corner + glm::vec3(0, height, -1), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D_Tema::CreateStar(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    glm::vec3 color1,
    glm::vec3 color2,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(2, 0, 2), color2),//B
        VertexFormat(corner + glm::vec3(0, -1.4f, 2), color2),//C
        VertexFormat(corner + glm::vec3(-2, 0, 2), color2),//A
        VertexFormat(corner + glm::vec3(0, 1.6f, 2), color1),//D
        VertexFormat(corner + glm::vec3(0.8f, 0, 2), color1),//F
        VertexFormat(corner + glm::vec3(-0.8f, 0, 2), color1),//E
        VertexFormat(corner + glm::vec3(-1, -0.5f, 2), color1),//H
        //C
        VertexFormat(corner + glm::vec3(-1, -2, 2), color1),//G
        VertexFormat(corner + glm::vec3(1, -0.5f, 2), color1),//J
        VertexFormat(corner + glm::vec3(1, -2, 2), color1),//I
        //C


    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3,4,5,6,1,7,8,9,1 };
    star->InitFromData(vertices, indices);
    return star;
}

Mesh* object2D_Tema::CreateRomb(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(-1, 0, 0), color),//B
        VertexFormat(corner + glm::vec3(1, 0, 0), color),//C
        VertexFormat(corner + glm::vec3(0, 2, 0), color),//A
        //B
        //C
        VertexFormat(corner + glm::vec3(0, -2, 0), color),//D
        VertexFormat(corner + glm::vec3(0.5f, -0.5f, 0), color),//F
        VertexFormat(corner + glm::vec3(0.5f, 0.5f, 0), color),//E
        VertexFormat(corner + glm::vec3(2, -0.5f, 0), color),//G
        VertexFormat(corner + glm::vec3(2, 0.5f, 0), color),//H





    };

    Mesh* romb = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 2,1,0,1, 3,4,5,6,5,7,6 };

    romb->InitFromData(vertices, indices);
    return romb;
}

Mesh* object2D_Tema::CreateHex(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    glm::vec3 colorout,
    glm::vec3 colorin)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, colorout),//M
        VertexFormat(corner + glm::vec3(-1, 2, 10), colorout),//A
        VertexFormat(corner + glm::vec3(1, 2, 10), colorout),//B
        VertexFormat(corner + glm::vec3(2, 0, 10), colorout),//C
        VertexFormat(corner + glm::vec3(1,-2, 10), colorout),//D
        VertexFormat(corner + glm::vec3(-1, -2, 10), colorout),//E
        VertexFormat(corner + glm::vec3(-2, 0, 10), colorout),//F
        VertexFormat(corner, colorin),//N
        VertexFormat(corner + glm::vec3(-0.5f, 1, 11), colorin),//G
        VertexFormat(corner + glm::vec3(0.5f, 1, 11), colorin),//H
        VertexFormat(corner + glm::vec3(1, 0, 11), colorin),//I
        VertexFormat(corner + glm::vec3(0.5f, -1, 11), colorin),//J
        VertexFormat(corner + glm::vec3(-0.5f, -1, 11), colorin),//K
        VertexFormat(corner + glm::vec3(-1, 0, 11), colorin),//L


    };

    Mesh* hex = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 0,2,3,0,3,4,0,4,5,0,5,6,0,6,1,7,8,9,7,9,10,7,10,11,7,11,12,7,12,13,7,13,8 };

    hex->InitFromData(vertices, indices);
    return hex;
}