#include "lab_m1/world_of_tanks/Main_wot.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Main_wot::Main_wot()
{
}


Main_wot::~Main_wot()
{
}


void Main_wot::Init()
{
    start_time = high_resolution_clock::now();
    duration_aux = duration_cast<seconds>(start_time - start_time);

    MyTank = Tank();
    EnemyTank = Tank(true);
    renderCameraTarget = false;
    
    d_3 = 0;

    glm::vec3 my_pos = MyTank.GetCorp_pos();
    glm::vec2 my_point = { my_pos[0], my_pos[2] };
    camera = new implemented::TemaCamera();
    glm::vec3 initialDirection = glm::vec3(-1.0f, 0.0f, 0.0f);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(MyTank.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec4 rotatedDirection = rotationMatrix * glm::vec4(initialDirection, 0.0f);
    glm::vec3 newDirection = glm::vec3(rotatedDirection);
    glm::vec2 cam_point = { 5.29f, 3.6f };

    //Init the camera
    camera->Set(glm::vec3(5.29f, 2.7f, 3.6f), newDirection, glm::vec3(0, 1, 0), glm::distance(my_point,cam_point));
    
    {
        Mesh* mesh = new Mesh("floor");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("tun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank_parts"), "final_tun.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("corp");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank_parts"), "final_corp.obj");
        meshes[mesh->GetMeshID()] = mesh;
    } 
    
    {
        Mesh* mesh = new Mesh("senile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank_parts"), "final_senile.obj");
        meshes[mesh->GetMeshID()] = mesh;
    } 
    
    {
        Mesh* mesh = new Mesh("turela");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank_parts"), "final_turela.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("projectile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank_parts"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("building");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank_parts"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("Shader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "world_of_tanks", "TankVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "world_of_tanks", "TankFragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    radians = RADIANS(60);
    width = 20.f;
    length = 20.f;
    znear = 0.01f;
    zfar = 200.0f;
    projectionMatrix = glm::perspective(radians, window->props.aspectRatio, znear, zfar);

    int nr_buildings = std::rand() % 6 + 10;
    for (int i = 0; i <= nr_buildings; i++)
        buildings.push_back(Cladire());
    finish_time_sec = 0;

    mouse_x = 0;
    mouse_y = 0;

    finish_game = 0;
}       


void Main_wot::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Main_wot::Update(float deltaTimeSeconds)
{
    if (finish_game == 2)
        return;

    if (finish_time_sec == 90)
        finish_game = 1;

    if (finish_game)
    {
        if (MyTank.life == 0)
            std::cout << "YOU LOST! :(" << std::endl;
        else
            std::cout <<"Total points = "<< total_points << std::endl;
        finish_game = 2;
        return;
    }

    current_time = high_resolution_clock::now();
    std::chrono::seconds duration = duration_cast<seconds>(current_time - start_time);
    if (duration.count() > duration_aux.count())
    {
        duration_aux = duration;
        Projectiles_life();
        Tank_shoot();
        EnemyTank_move();
        finish_time_sec++;
    }

    //MyTank rend
    {
        {
            glm::mat4 modelMatrix = MyTank.Tun_rend(1);
            RenderMesh(meshes["tun"], shaders["Shader"], modelMatrix, MyTank.GetTun_col(), MyTank.life);
        }

        {
            glm::mat4 modelMatrix = MyTank.Senile_rend();
            RenderMesh(meshes["senile"], shaders["Shader"], modelMatrix, MyTank.GetSenile_col(), MyTank.life);
        }

        {
            glm::mat4 modelMatrix = MyTank.Turela_rend(1);
            RenderMesh(meshes["turela"], shaders["Shader"], modelMatrix, MyTank.GetTurela_col(), MyTank.life);
        }

        {
            glm::mat4 modelMatrix = MyTank.Corp_rend();
            RenderMesh(meshes["corp"], shaders["Shader"], modelMatrix, MyTank.GetCorp_col(), MyTank.life);
        }
    }

    //EnemyTank rend
    {
        {
            glm::mat4 modelMatrix = EnemyTank.Tun_rend(0);
            RenderMesh(meshes["tun"], shaders["Shader"], modelMatrix, EnemyTank.GetTun_col(), EnemyTank.life);
        }

        {
            glm::mat4 modelMatrix = EnemyTank.Senile_rend();
            RenderMesh(meshes["senile"], shaders["Shader"], modelMatrix, EnemyTank.GetSenile_col(), EnemyTank.life);
        }

        {
            glm::mat4 modelMatrix = EnemyTank.Turela_rend(0);
            RenderMesh(meshes["turela"], shaders["Shader"], modelMatrix, EnemyTank.GetTurela_col(), EnemyTank.life);
        }

        {
            glm::mat4 modelMatrix = EnemyTank.Corp_rend();
            RenderMesh(meshes["corp"], shaders["Shader"], modelMatrix, EnemyTank.GetCorp_col(), EnemyTank.life);
        }
    }

    for (int i = 0; i < buildings.size(); i++)
    {
        glm::mat4 modelMatrix = buildings[i].Rend();
        RenderMesh(meshes["building"], shaders["Shader"], modelMatrix, buildings[i].GetCol(),3);
    }

    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].Move(deltaTimeSeconds);
        glm::mat4 modelMatrix = projectiles[i].Rend();
        if (Coliz_proj(i))
            projectiles.erase(projectiles.begin() + i);
        else
        {
            RenderMesh(meshes["projectile"], shaders["Shader"], modelMatrix, projectiles[i].GetCol(),3);
        }
       
    }

    {
        Coliz_tank_tank();
        Coliz_tank_build();
        Tank_in_radius();
    }

    //EnemyTank move
    if (EnemyTank.move_sec > 0)
    {
        EnemyTank.W_move(deltaTimeSeconds);
    }
    else
    {
        if (EnemyTank.a)
            EnemyTank.A_rotation(deltaTimeSeconds);
        else
            EnemyTank.D_rotation(deltaTimeSeconds);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= tema_transform3D::Scale(200, 200, 200);
        RenderMesh(meshes["floor"], shaders["Shader"], modelMatrix, glm::vec3(115.f/255.f, 118.f / 255.f, 83.f / 255.f), 3);
    }
}

void Main_wot::Tank_in_radius()
{
    glm::vec2 mytank_pos = { MyTank.GetCorp_pos()[0] + MyTank.x_move, MyTank.GetCorp_pos()[2] + MyTank.z_move };
    glm::vec2 enemytank_pos = { EnemyTank.GetCorp_pos()[0] + EnemyTank.x_move, EnemyTank.GetCorp_pos()[2] + EnemyTank.z_move };
    
    float dif = glm::distance(mytank_pos, enemytank_pos);

    if (dif < 15.f)
    {
        EnemyTank.Tun_rot(MyTank.GetCorp_pos()[0] + MyTank.x_move, MyTank.GetCorp_pos()[2] + MyTank.z_move);
        Proiectil new_pro = EnemyTank.Shoot_pro(3);
        if (new_pro.GetLife() != -1)
            projectiles.push_back(new_pro);
    }
}


void Main_wot::Coliz_tank_build()
{
    glm::vec3 corp_mytank_pos = MyTank.GetCorp_pos();
    corp_mytank_pos[0] += MyTank.x_move;
    corp_mytank_pos[2] += MyTank.z_move;
    
    glm::vec3 corp_enemytank_pos = EnemyTank.GetCorp_pos();
    corp_enemytank_pos[0] += EnemyTank.x_move;
    corp_enemytank_pos[2] += EnemyTank.z_move;

    float R_tank = 1.2f;
    for (int i = 0; i < buildings.size(); i++)
    {
        glm::vec3 build_sc = buildings[i].GetSc();
        glm::vec3 build_pos = buildings[i].GetPos();
        
        if (build_pos[2] - build_sc[2]/2 - R_tank < corp_mytank_pos[2] && corp_mytank_pos[2] < build_pos[2] + build_sc[2]/2 + R_tank
            && corp_mytank_pos[0] < build_pos[0] + build_sc[0]/2 + R_tank && corp_mytank_pos[0] > build_pos[0] - build_sc[0] / 2 - R_tank)
        {
            glm::vec3 tankToBuilding = glm::normalize(build_pos - corp_mytank_pos);
            float p = build_sc[0] / 2 + R_tank;
            tankToBuilding.x = -tankToBuilding.x * p;
            tankToBuilding.z = -tankToBuilding.z * p;
            MyTank.Center_move(0.1f, tankToBuilding);
            camera->Center_move(0.1f, tankToBuilding);
        }

        if (build_pos[2] - build_sc[2] / 2 - R_tank < corp_mytank_pos[2] && corp_mytank_pos[2] < build_pos[2] + build_sc[2] / 2 + R_tank
            && corp_mytank_pos[0] < build_pos[0] + build_sc[0] / 2 + R_tank && corp_mytank_pos[0] > build_pos[0] - build_sc[0] / 2 - R_tank)
        {
            float p = build_sc[0] / 2 + R_tank;
            glm::vec3 tankToBuilding = glm::normalize(build_pos - corp_enemytank_pos);
            tankToBuilding.x = -tankToBuilding.x * p;
            tankToBuilding.z = -tankToBuilding.z * p;
            EnemyTank.Center_move(0.1f, tankToBuilding);
        }
    }
}

void Main_wot::Coliz_tank_tank()
{
    glm::vec2 mytank = { MyTank.GetCorp_pos()[0] + MyTank.x_move, MyTank.GetCorp_pos()[2] + MyTank.z_move };
    glm::vec2 enemytank = { EnemyTank.GetCorp_pos()[0] + EnemyTank.x_move, EnemyTank.GetCorp_pos()[2] + EnemyTank.z_move };

    glm::vec3 corp_mytank_pos = MyTank.GetCorp_pos();
    corp_mytank_pos[0] += MyTank.x_move;
    corp_mytank_pos[2] += MyTank.z_move;

    glm::vec3 corp_enemytank_pos = EnemyTank.GetCorp_pos();
    corp_enemytank_pos[0] += EnemyTank.x_move;
    corp_enemytank_pos[2] += EnemyTank.z_move;

    float dif = glm::distance(mytank, enemytank);

    if (dif < 2.4f) //2 * RTank
    {
        float p = 2.4f - dif;
        auto dir = glm::normalize(corp_enemytank_pos - corp_mytank_pos) * p;
        MyTank.Center_move(-0.5f, dir);
        camera->Center_move(-0.5f, dir);
        EnemyTank.Center_move(0.5f, dir);
    }
}


void Main_wot::EnemyTank_move()
{
    if (EnemyTank.move_sec > 0)
    {
        EnemyTank.move_sec--;
        if (EnemyTank.move_sec == 0)
        {
            EnemyTank.move_sec = -1;
            int random = std::rand() % 2 + 1;
            EnemyTank.rot_sec = random;
            EnemyTank.a = std::rand() % 2;
        }
        return;
    }
    if (EnemyTank.rot_sec > 0)
    {
        EnemyTank.rot_sec--;
        if (EnemyTank.rot_sec == 0)
        {
            EnemyTank.rot_sec = -1;
            int random = std::rand() % 3 + 2;
            EnemyTank.move_sec = random;
        }
    }
        
    
}

void Main_wot::Tank_shoot()
{
    MyTank.Dcr_shoot();
    EnemyTank.Dcr_shoot();
}

void Main_wot::Projectiles_life()
{
    for (int i = 0; i < projectiles.size(); i++)
        if (projectiles[i].Life() == 0)
            projectiles.erase(projectiles.begin() + i);
}

bool Main_wot::Coliz_proj(int n)
{
    Proiectil projectil = projectiles[n];
    glm::vec3 pos_proj = projectil.GetRealPos();
    for (int i = 0; i < buildings.size(); i++)
    {
        glm::vec3 build_pos = buildings[i].GetPos();
        glm::vec3 build_sc = buildings[i].GetSc();
        
        if (build_pos[0] - build_sc[0]/2 < pos_proj[0] && pos_proj[0] < build_pos[0] + build_sc[0]/2 &&
            build_pos[2] - build_sc[2]/2 < pos_proj[2] && pos_proj[2] < build_pos[2] + build_sc[2]/2)
        {
            buildings.erase(buildings.begin() + i);
            return 1;
        }
    }

    glm::vec3 enemy_pos = EnemyTank.GetCorp_pos();
    glm::vec2 proj_point = { pos_proj[0], pos_proj[2]  };
    glm::vec2 enemy_point = { enemy_pos[0] + EnemyTank.x_move, enemy_pos[2] + EnemyTank.z_move };
    if (glm::distance(proj_point, enemy_point) < 1.3f + 0.35f)//RTank and RProj
    {
        EnemyTank.life--;
        if (EnemyTank.life == 0)
        {
            EnemyTank = Tank(true);
            total_points++;
        }
        return 1;
    }

    glm::vec3 my_pos = MyTank.GetCorp_pos();
    glm::vec2 my_point = { my_pos[0] + MyTank.x_move, my_pos[2] + MyTank.z_move };

    if (glm::distance(proj_point, my_point) < 1.3f + 0.35f)//RTank and RProj
    {
        MyTank.life--;
        if (MyTank.life == 0)
            finish_game = 1;
        return 1;
    }

    return 0;

}

void Main_wot::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Main_wot::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, int life)
{
    
    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));
    glUniform1i(glGetUniformLocation(shader->program, "life"), life);

    mesh->Render();
}




void Main_wot::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_W))
    {
        MyTank.W_move(deltaTime);
        float cameraSpeed = 2.0f;
        camera->XTranslateForward(deltaTime * cameraSpeed, MyTank);
    }

    if (window->KeyHold(GLFW_KEY_S))
    {

        MyTank.S_move(deltaTime);
        float cameraSpeed = -2.0f;
        camera->XTranslateForward(deltaTime * cameraSpeed, MyTank);
    }
    if (d_3 == 0)
    {
        if (window->KeyHold(GLFW_KEY_A))
        {
            MyTank.A_rotation(deltaTime);
            camera->RotateThirdPerson_OY(MyTank);
        }

        if (window->KeyHold(GLFW_KEY_D))
        {
            MyTank.D_rotation(deltaTime);
            camera->RotateThirdPerson_OY(MyTank);

        }
    }
}


void Main_wot::OnKeyPress(int key, int mods)
{
    
}


void Main_wot::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Main_wot::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    int left_or_right = 0;
    if (mouseX > mouse_x)
        left_or_right = 1;
    else
        left_or_right = 0;

    mouse_x = mouseX;

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;
        
        camera->XRotateThirdPerson_OY(-deltaX * sensivityOY, MyTank);

    }
    else
    {
        float sensivityOX = 0.0001f;
        float sensivityOY = 0.0001f; 
        if (left_or_right)
        {
            MyTank.Mouse_move(deltaX, sensivityOX, 1);
        }
        else {
            MyTank.Mouse_move(deltaX, sensivityOX, 0);
        }
    }
}


void Main_wot::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == 1)
    {
        Proiectil new_pro = MyTank.Shoot_pro(2);
        if (new_pro.GetLife() != -1)
        {
            projectiles.push_back(new_pro);
        }
    }
}


void Main_wot::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if (button == 2)
    {
        camera->RotateThirdPerson_OY(MyTank);
    }
}


void Main_wot::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Main_wot::OnWindowResize(int width, int height)
{
}
