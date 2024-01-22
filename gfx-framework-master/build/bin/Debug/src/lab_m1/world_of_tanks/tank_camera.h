#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"
#include <iostream>
#include "lab_m1/world_of_tanks/Tank.h"


namespace implemented
{
    class TemaCamera
    {
    public:
        TemaCamera()
        {
            position = glm::vec3(0, 2, 5);
            forward = glm::vec3(0, 0, -1);
            up = glm::vec3(0, 1, 0);
            right = glm::vec3(1, 0, 0);
            distanceToTarget = -1;
        }

        TemaCamera(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up, float dist)
        {
            Set(position, forward, up, dist);
        }

        ~TemaCamera()
        { }

        void Set(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up, float  dist)
        {
            this->position = position;
            this->forward = forward;
            this->up = up;
            right = glm::cross(forward, up);
            this->distanceToTarget = dist;
        }

        void Center_move(float x, glm::vec3 dir)
        {
            position[0] += dir.x * x;
            position[2] += dir.z * x;
        }

        void TranslateForward(float distance)
        {
            glm::vec3 dir = glm::normalize(forward);
             position[0] += dir[0] * distance;
             position[2] += dir[2] * distance;
        }

        void XTranslateForward(float distance, Tank MyTank)
        {
            glm::vec3 initialDirection = glm::vec3(-1.0f, 0.0f, 0.0f);
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(MyTank.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::vec4 rotatedDirection = rotationMatrix * glm::vec4(initialDirection, 0.0f);
            glm::vec3 newDirection = glm::vec3(rotatedDirection);
            position[0] += newDirection[0] * distance;
            position[2] += newDirection[2] * distance;
        }

        void Rotate_A(float angle)
        {
            forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1)));
            right = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1)));
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateFirstPerson_OX(float angle)
        {

            forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, right) * glm::vec4(forward, 1)));
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateFirstPerson_OY(float angle)
        {
            forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1)));
            right = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1)));
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateThirdPerson_OY(Tank MyTank)
        {
            TranslateForward(distanceToTarget);

            glm::vec3 initialDirection = glm::vec3(-1.0f, 0.0f, 0.0f);
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(MyTank.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::vec4 rotatedDirection = rotationMatrix * glm::vec4(initialDirection, 0.0f);
            glm::vec3 newDirection = glm::vec3(rotatedDirection);
            
            forward = newDirection;
            up = glm::vec3(0, 1, 0);
            right = glm::normalize(glm::cross(forward, up));
            TranslateForward(-distanceToTarget);
        }

        void XRotateThirdPerson_OY(float angle, Tank MyTank)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OY(angle);
            TranslateForward(-distanceToTarget);
        }


        glm::mat4 GetViewMatrix()
        {
            // Returns the view matrix
            return glm::lookAt(position, position + forward, up);
        }

        glm::vec3 GetTargetPosition()
        {
            return position + forward * distanceToTarget;
        }

    public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
    };
}   // namespace implemented
