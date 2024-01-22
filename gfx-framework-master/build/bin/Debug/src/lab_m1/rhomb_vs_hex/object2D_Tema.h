#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D_Tema
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length,float height, glm::vec3 color, bool fill = false);
    Mesh* CreateStar(const std::string& name, glm::vec3 leftBottomCorner, glm::vec3 color1, glm::vec3 color2, bool fill = false);
    Mesh* CreateRomb(const std::string& name, glm::vec3 leftBottomCorner, glm::vec3 color);
    Mesh* CreateHex(const std::string& name, glm::vec3 leftBottomCorner, glm::vec3 colorout, glm::vec3 colorin);
}
