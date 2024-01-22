#include "lab_m1/rhomb_vs_hex/Main_game.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/rhomb_vs_hex/transform2D.h"
#include "lab_m1/rhomb_vs_hex/object2D_Tema.h"

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    start_time = high_resolution_clock::now();

    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);


    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;
    float squareLifeSide = 50;
    float squarecadrSide = 100;

    line1 = 100;
    line2 = 250;
    line3 = 400;

    totalStarsX = 800;
    totalStarsY = 600;

    float rectangleL = 75;
    float rectangleH = 400;

    totalLife = 3;

    pickedRomb.SetScale(20);

    //Stars you have
    totalPoints = 7;
    totalStars.resize(10);
    for (int i = 0; i <= 9; i++)
        totalStars[i] = Star::Star(totalStarsX + i * 35, totalStarsY, 10, 1);

    for (int i = 7; i <= 9; i++)
        totalStars[i].SetToRand(0);

    //Stars that appear
    pointStars.resize(3);
    for (int i = 0; i < 3; i++)
        pointStars[i] = Star::Star(0, 0, 15, 0);

    //Lifes
    totalLifes.resize(3);
    totalLifes[0] = 800;
    totalLifes[1] = 875;
    totalLifes[2] = 950;

    //Rombs on map
    rombs.resize(9);
    rombs[0] = Romb::Romb(150, 100, 0, 0, 20);
    rombs[1] = Romb::Romb(300, 100, 0, 0, 20);
    rombs[2] = Romb::Romb(450, 100, 0, 0, 20);
    rombs[3] = Romb::Romb(150, 250, 0, 0, 20);
    rombs[4] = Romb::Romb(300, 250, 0, 0, 20);
    rombs[5] = Romb::Romb(450, 250, 0, 0, 20);
    rombs[6] = Romb::Romb(150, 400, 0, 0, 20);
    rombs[7] = Romb::Romb(300, 400, 0, 0, 20);
    rombs[8] = Romb::Romb(450, 400, 0, 0, 20);


    duration_aux = duration_cast<seconds>(start_time - start_time);

    picked = 0;
    pointsUp = 0;

    // Initialize angularStep
    Mesh* romb1 = object2D_Tema::CreateRomb("romb1", corner, glm::vec3(1, 0,0));//red
    AddMeshToList(romb1);

    Mesh* romb2 = object2D_Tema::CreateRomb("romb2", corner, glm::vec3(13.f / 255.f, 195.f / 255.f, 219.f / 255.f));//blue
    AddMeshToList(romb2);

    Mesh* romb3 = object2D_Tema::CreateRomb("romb3", corner, glm::vec3(9.f / 255.f, 222.f / 255.f,112.f / 255.f));//green
    AddMeshToList(romb3);

    Mesh* romb4 = object2D_Tema::CreateRomb("romb4", corner, glm::vec3(222.f / 255.f, 115.f / 255.f, 9.f / 255.f));//orange
    AddMeshToList(romb4);

    Mesh* starPoints = object2D_Tema::CreateStar("starPoints", corner, glm::vec3(1, 105.f/255.f, 180.f/255.f), glm::vec3(170.f / 255.f, 213.f / 255.f, 82.f / 255.f), true);
    AddMeshToList(starPoints);

    Mesh* star1 = object2D_Tema::CreateStar("star1", corner, glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), true);
    AddMeshToList(star1);

    Mesh* star2 = object2D_Tema::CreateStar("star2", corner, glm::vec3(13.f / 255.f, 195.f / 255.f, 219.f / 255.f), glm::vec3(13.f / 255.f, 195.f / 255.f, 219.f / 255.f), true);
    AddMeshToList(star2);

    Mesh* star3 = object2D_Tema::CreateStar("star3", corner, glm::vec3(9.f / 255.f, 222.f / 255.f, 112.f / 255.f), glm::vec3(9.f / 255.f, 222.f / 255.f, 112.f / 255.f), true);
    AddMeshToList(star3);

    Mesh* star4 = object2D_Tema::CreateStar("star4", corner, glm::vec3(222.f / 255.f, 115.f / 255.f, 9.f / 255.f), glm::vec3(222.f / 255.f, 115.f / 255.f, 9.f / 255.f), true);
    AddMeshToList(star4);

    Mesh* rectangle1 = object2D_Tema::CreateRectangle("rectangle1", corner, rectangleL, rectangleH, glm::vec3(1, 0, 0), true);
    AddMeshToList(rectangle1);

    Mesh* square1 = object2D_Tema::CreateSquare("square1", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(square1);

    Mesh* squareLife = object2D_Tema::CreateSquare("squareLife", corner, squareLifeSide, glm::vec3(1, 0.3f, 0), true);
    AddMeshToList(squareLife);

    Mesh* squarecadr1 = object2D_Tema::CreateSquare("squarecadr1", corner, squarecadrSide, glm::vec3(0, 0, 1), false);
    AddMeshToList(squarecadr1);

    Mesh* enemy1 = object2D_Tema::CreateHex("enemy1", corner, glm::vec3(1,0,0), glm::vec3(122.f / 255.f, 119.f / 255.f, 114.f / 255.f));
    AddMeshToList(enemy1);
    
    Mesh* enemy2 = object2D_Tema::CreateHex("enemy2", corner, glm::vec3(13.f / 255.f, 195.f / 255.f, 219.f / 255.f), glm::vec3(122.f / 255.f, 119.f / 255.f, 114.f / 255.f));
    AddMeshToList(enemy2);

    Mesh* enemy3 = object2D_Tema::CreateHex("enemy3", corner, glm::vec3(9.f / 255.f, 222.f / 255.f, 112.f / 255.f), glm::vec3(122.f / 255.f, 119.f / 255.f, 114.f / 255.f));
    AddMeshToList(enemy3);

    Mesh* enemy4 = object2D_Tema::CreateHex("enemy4", corner, glm::vec3(222.f / 255.f, 115.f / 255.f, 9.f / 255.f), glm::vec3(122.f / 255.f, 119.f / 255.f, 114.f / 255.f));
    AddMeshToList(enemy4);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    if (totalLife == 0)
        return;
    current_time = high_resolution_clock::now();
    std::chrono::seconds duration = duration_cast<seconds>(current_time - start_time);
    if (duration.count() > duration_aux.count())
    {
        duration_aux = duration;
        EnemyAppear();
        Shoot();
        for (int i = 0; i < 9; i++)
        {
            int shoot = rombs[i].GetShoot();
            if (shoot)
                rombs[i].SetShoot(shoot - 1);
        }
        
    }

    if (duration.count() % 10 == 0 && !pointsUp)
        RandomStars();

    if (pointsUp)
        for (int i = 0; i < pointStars.size(); i++)
            if (pointStars[i].GetToRand())
                StarRand(pointStars[i].GetX(), pointStars[i].GetY(), pointStars[i].GetScale(), pointStars[i].GetScale(), 0, "starPoints");

    for (int i = 0; i <= totalPoints; i++)
            StarRand(totalStars[i].GetX(), totalStars[i].GetY(), totalStars[i].GetScale(), totalStars[i].GetScale(), 0, "starPoints");

    for (int i = 0; i < starLine1.size(); i++)
    {
        StarRand(starLine1[i].GetX(), starLine1[i].GetY(), starLine1[i].GetScale(), starLine1[i].GetScale(), starLine1[i].GetRotate(), starLine1[i].GetStar());
        starLine1[i].Rotate(deltaTimeSeconds);
        starLine1[i].Move(deltaTimeSeconds);

    }
    for (int i = 0; i < starLine2.size(); i++)
    {
        StarRand(starLine2[i].GetX(), starLine2[i].GetY(), starLine2[i].GetScale(), starLine2[i].GetScale(), starLine2[i].GetRotate(), starLine2[i].GetStar());
        starLine2[i].Rotate(deltaTimeSeconds);
        starLine2[i].Move(deltaTimeSeconds);
    }
    for (int i = 0; i < starLine3.size(); i++)
    {
        StarRand(starLine3[i].GetX(), starLine3[i].GetY(), starLine3[i].GetScale(), starLine3[i].GetScale(), starLine3[i].GetRotate(), starLine3[i].GetStar());
        starLine3[i].Rotate(deltaTimeSeconds);
        starLine3[i].Move(deltaTimeSeconds);
    }

    //Zones
    SquareRand(100, 50, "square1");
    SquareRand(250, 50, "square1");
    SquareRand(400, 50, "square1");
    SquareRand(100, 200, "square1");
    SquareRand(250, 200, "square1");
    SquareRand(400, 200, "square1");
    SquareRand(100, 350, "square1");
    SquareRand(250, 350, "square1");
    SquareRand(400, 350, "square1");
    
    //Finish line
    SquareRand(10, 50, "rectangle1");

    //Lifes
    for (int i = 0; i < totalLife; i++)
        SquareRand(totalLifes[i], 625, "squareLife");


    //Tips of rombs
    RombRand(200, 650, 20, 20, "romb1");
    RombRand(350, 650, 20, 20, "romb2");
    RombRand(500, 650, 20, 20, "romb3");
    RombRand(650, 650, 20, 20, "romb4");

    //Squares for rombs
    SquareRand(150, 600, "squarecadr1"); 
    SquareRand(300, 600, "squarecadr1");
    SquareRand(450, 600, "squarecadr1");
    SquareRand(600, 600, "squarecadr1");

    //Cost of rombs
    StarRand(170, 570, 10, 10, 0, "starPoints");
    StarRand(320, 570, 10, 10, 0, "starPoints");
    StarRand(355, 570, 10, 10, 0, "starPoints");
    StarRand(470, 570, 10, 10, 0, "starPoints");
    StarRand(505, 570, 10, 10, 0, "starPoints");
    StarRand(615, 570, 10, 10, 0, "starPoints");
    StarRand(650, 570, 10, 10, 0, "starPoints");
    StarRand(685, 570, 10, 10, 0, "starPoints");

    //If a romb is picked
    if (picked)
        RombTypeRand(pickedRomb);

    //Rand the rombs in cuadranes
    CadrRomb();


    //Enemies on line 1
    for (int i = 0; i < enemyLine1.size(); i++)
    {
        if (enemyLine1[i].GetDie() == 0)
            EnemyHit(starLine1, rombs, 0, enemyLine1[i]);
        EnemyRand(enemyLine1[i].GetX(), enemyLine1[i].GetY(), enemyLine1[i].GetScale(), enemyLine1[i].GetScale(), enemyLine1[i].GetType());
        if (enemyLine1[i].GetDie())
            enemyLine1[i].SetScale(enemyLine1[i].GetScale() - 0.5f);
        else enemyLine1[i].SetX(enemyLine1[i].GetX() - 40 * deltaTimeSeconds);
        if (enemyLine1[i].GetScale() == 0)
        {
            enemyLine1.erase(enemyLine1.begin()+i);
            i--;
        }
    }


    //Enemies on line 2
    for (int i = 0; i < enemyLine2.size(); i++)
    {
        if (enemyLine2[i].GetDie() == 0)
            EnemyHit(starLine2, rombs, 1, enemyLine2[i]);
        EnemyRand(enemyLine2[i].GetX(), enemyLine2[i].GetY(), enemyLine2[i].GetScale(), enemyLine2[i].GetScale(), enemyLine2[i].GetType());
        if (enemyLine2[i].GetDie())
            enemyLine2[i].SetScale(enemyLine2[i].GetScale() - 0.5f);
        else enemyLine2[i].SetX(enemyLine2[i].GetX() - 40 * deltaTimeSeconds);
        if (enemyLine2[i].GetScale() == 0)
        {
            enemyLine2.erase(enemyLine2.begin() + i);
            i--;
        }
    }

    //Enemies on line 3
    for (int i = 0; i < enemyLine3.size(); i++)
    {
        if (enemyLine3[i].GetDie() == 0)
            EnemyHit(starLine3, rombs, 2, enemyLine3[i]);
        EnemyRand(enemyLine3[i].GetX(), enemyLine3[i].GetY(), enemyLine3[i].GetScale(), enemyLine3[i].GetScale(), enemyLine3[i].GetType());
        if (enemyLine3[i].GetDie())
            enemyLine3[i].SetScale(enemyLine3[i].GetScale() - 0.5f);
        else enemyLine3[i].SetX(enemyLine3[i].GetX() - 40 * deltaTimeSeconds);
        if (enemyLine3[i].GetScale() == 0)
        {
            enemyLine3.erase(enemyLine3.begin() + i);
            i--;
        }
    }
}

//Check if enemy hits something
void Tema1::EnemyHit(std::vector<Star> &starsLine, std::vector <Romb> &rombsLine, int line ,Enemy &enemy )
{
    glm::vec2 enemyPoint = { enemy.GetX(),enemy.GetY() };
    //Check stars
    for (int i = 0; i < starsLine.size(); i++)
    {
        if (starsLine[i].GetType() == enemy.GetType())
        {
            glm::vec2 starPoint = { starsLine[i].GetX(),starsLine[i].GetY()};
            if (glm::distance(enemyPoint,starPoint) < 2*starsLine[i].GetScale() + 2*enemy.GetScale())
            {
                starsLine.erase(starsLine.begin() + i);
                enemy.SetLife(enemy.GetLife() - 1);
            }
        }
        if (enemy.GetLife() == 0)
        {
            enemy.SetDieOne();
            return;
        }
    }

    //Check rombs
    for (int i = line * 3; i < line * 3 + 3; i++)
    {
        if (rombsLine[i].GetDie() == 0 && rombsLine[i].GetPosition())
        {
            glm::vec2 rombPoint = { rombsLine[i].GetX(),rombsLine[i].GetY() };
            if (glm::distance(enemyPoint, rombPoint) < 2 * rombsLine[i].GetScale() + 2 * enemy.GetScale())
            {
                rombsLine[i].SetDie(1);

            }
        }
    }

    //Check finish line
    glm::vec2 rectanglePoint = { 46,enemy.GetY() };
    if (glm::distance(enemyPoint, rectanglePoint) < 37 + 2 * enemy.GetScale())
    {
        enemy.SetDieOne();
        totalLife--;
    }
}


void Tema1::Shoot()
{
    //Enemy on first line
    if (enemyLine1.size())
    {
        for (int i = 0; i < 3; i++)
        {
            if (rombs[i].GetPosition())
                for (int j = 0; j < enemyLine1.size(); j++)
                {
                    int shoot = rombs[i].GetShoot();
                    if (rombs[i].GetType() == enemyLine1[j].GetType() && shoot == 0)
                    {
                        ShootStar(i, starLine1);
                        break;
                    }
                }
        }
    }

    //Enemy on second line
    if (enemyLine2.size())
    {
        for (int i = 3; i < 6; i++)
        {
            if (rombs[i].GetPosition())
            {
                for (int j = 0; j < enemyLine2.size(); j++)
                {
                    int shoot = rombs[i].GetShoot();
                    //std::cout << i << "   " << rombs[i].GetType() << "==" << enemyLine2[j].GetType() << " shoot = " << shoot << std::endl;
                    if (rombs[i].GetType() == enemyLine2[j].GetType() && shoot == 0)
                    {
                        ShootStar(i, starLine2);
                       // std::cout << starLine2[starLine2.size() - 1].GetType() << " " << starLine2[starLine2.size() - 1].GetStar() << std::endl;
                        break;
                    }
                }
            }
        }
    }
    //Enemy on third line
    if (enemyLine3.size())
    {
        for (int i = 6; i < 9; i++)
        {
            if (rombs[i].GetPosition())
                for (int j = 0; j < enemyLine3.size(); j++)
                {
                    int shoot = rombs[i].GetShoot();
                    //std::cout << i << "   " << rombs[i].GetType() << "==" << enemyLine3[j].GetType() << " shoot = " << shoot << std::endl;
                    if (rombs[i].GetType() == enemyLine3[j].GetType() && shoot == 0)
                    {
                        ShootStar(i, starLine3);
                        //std::cout << starLine3[starLine3.size() - 1].GetType() << " "<< starLine3[starLine3.size() - 1].GetStar() << std::endl;
                        break;
                    }
                }
        }
    }
}

//
void Tema1::ShootStar(int i,std::vector<Star> &line)
{
    Star star;
    switch (rombs[i].GetType())
    {
    case 1:
    {
        star = Star::Star(rombs[i].GetX() + 40 + 30, rombs[i].GetY(), 15, 360, "star1", 1);
        break;
    }
    case 2:
    {
        star = Star::Star(rombs[i].GetX() + 40 + 30, rombs[i].GetY(), 15, 360, "star2", 2);
        break;
    }
    case 3:
    {
        star = Star::Star(rombs[i].GetX() + 40 + 30, rombs[i].GetY(), 15, 360, "star3", 3);
        break;
    }
    case 4:
    {
        star = Star::Star(rombs[i].GetX() + 40 + 30, rombs[i].GetY(), 15, 360, "star4", 4);
        break;
    }
    default:
        break;
    }
    rombs[i].SetShoot(4);
    line.push_back(star);

}


void Tema1::EnemyAppear()
{
    glm::ivec2 resolution = window->GetResolution();
    int chance = std::rand() % 101;
    if (chance % 7 == 0)
    {
        int line = std::rand()%3;
        switch (line)
        {
        case 0:
        {
            int type = std::rand() % 4;
            Enemy newEnemy = Enemy::Enemy(1280, line1, 15, 1, type+1);
            enemyLine1.push_back(newEnemy);
            break;
        }
        case 1:
        {
            int type = std::rand() % 4;
            Enemy newEnemy = Enemy::Enemy(1280, line2, 15, 1, type+1);
            enemyLine2.push_back(newEnemy);
            break;
        }
        case 2:
        {
            int type = std::rand() % 4;
            Enemy newEnemy = Enemy::Enemy(1280, line3, 15, 1, type+1);
            enemyLine3.push_back(newEnemy);
            break;
        }
        default:
            break;
        }
    }

}

void Tema1::RandomStars()
{
    glm::ivec2 resolution = window->GetResolution();
    pointsUp = 3;
    for (int i = 0; i < 3; i++)
    {
        int randomx = std::rand();
        int randomy = std::rand();
        pointStars[i].SetX(randomx % resolution.x);
        pointStars[i].SetY(randomx % resolution.y);
        pointStars[i].SetToRand(1);
    }
}

void Tema1::CadrRomb()
{
    for (int i = 0; i < 9; i++)
        if (rombs[i].GetPosition())
        {
            float scale = rombs[i].GetScale();
            if (rombs[i].GetDie())
                rombs[i].SetScale(scale - 0.5f);
            if (rombs[i].GetScale() == 0)
                rombs[i].SetPosition(0);
            else   
                RombTypeRand(rombs[i]);
        }
}

void Tema1::RombTypeRand(Romb &romb)
{
        switch (romb.GetType())
        {
        case 1:
        {
            RombRand(romb.GetX(), romb.GetY(), romb.GetScale(), romb.GetScale(), "romb1");
            break;
        }
        case 2:
        {
            RombRand(romb.GetX(), romb.GetY(), romb.GetScale(), romb.GetScale(), "romb2");
            break;
        }
        case 3:
        {
            RombRand(romb.GetX(), romb.GetY(), romb.GetScale(), romb.GetScale(), "romb3");
            break;
        }
        case 4:
        {
            RombRand(romb.GetX(), romb.GetY(), romb.GetScale(), romb.GetScale(), "romb4");
            break;
        }
        default:
            break;
        }
}

void Tema1::SquareRand(float x,float y,std::string sq)
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x, y);

    RenderMesh2D(meshes[sq], shaders["VertexColor"], modelMatrix);
}

void Tema1::StarRand(float x, float y,float scx, float scy, float rotate, std::string star)
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x, y);
    modelMatrix *= transform2D::Scale(scx, scy);
    if (rotate != 0)
        modelMatrix *= transform2D::Rotate(rotate);
    RenderMesh2D(meshes[star], shaders["VertexColor"], modelMatrix);
}

void Tema1::RombRand(float x, float y, float scx, float scy, std::string romb)
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x, y);
    modelMatrix *= transform2D::Scale(scx, scy);

    RenderMesh2D(meshes[romb], shaders["VertexColor"], modelMatrix);
}

void Tema1::EnemyRand(float x, float y, float scx, float scy, int type)
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x, y);
    modelMatrix *= transform2D::Scale(scx, scy);


    switch (type)
    {
    case 1:
    {
        RenderMesh2D(meshes["enemy1"], shaders["VertexColor"], modelMatrix);
        break;
    }
    case 2:
    {
        RenderMesh2D(meshes["enemy2"], shaders["VertexColor"], modelMatrix);
        break;
    }
    case 3:
    {
        RenderMesh2D(meshes["enemy3"], shaders["VertexColor"], modelMatrix);
        break;
    }
    case 4:
    {
        RenderMesh2D(meshes["enemy4"], shaders["VertexColor"], modelMatrix);
        break;
    }
    default:
        break;
    }

}

void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    glm::ivec2 resolution = window->GetResolution();
    //Drag the romb after the mouse
    if (picked)
    {
        pickedRomb.SetX(mouseX);
        pickedRomb.SetY(resolution.y - mouseY);
    }
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    glm::ivec2 resolution = window->GetResolution();
    // Add mouse button press event
    if (button == 2)
    {
        //Kill a romb
        //1 1
        if (rombs[0].GetPosition() != 0 && 100 < mouseX && mouseX < 200 && 50 < resolution.y - mouseY && resolution.y - mouseY < 150)
        {
            rombs[0].SetDie(1);
        }
        //1 2
        if (250 < mouseX && mouseX < 350 && 50 < resolution.y - mouseY && resolution.y - mouseY < 150 && rombs[1].GetPosition() != 0)
        {
            rombs[1].SetDie(1);

        }
        //1 3
        if (400 < mouseX && mouseX < 500 && 50 < resolution.y - mouseY && resolution.y - mouseY < 150 && rombs[2].GetPosition() != 0)
        {
            rombs[2].SetDie(1);

        }
        //2 1
        if (100 < mouseX && mouseX < 200 && 200 < resolution.y - mouseY && resolution.y - mouseY < 300 && rombs[3].GetPosition() != 0)
        {
            rombs[3].SetDie(1);

        }
        //2 2
        if (250 < mouseX && mouseX < 350 && 200 < resolution.y - mouseY && resolution.y - mouseY < 300 && rombs[4].GetPosition() != 0)
        {
            rombs[4].SetDie(1);

        }
        //2 3
        if (400 < mouseX && mouseX < 500 && 200 < resolution.y - mouseY && resolution.y - mouseY < 300 && rombs[5].GetPosition() != 0)
        {
            rombs[5].SetDie(1);

        }
        //3 1
        if (100 < mouseX && mouseX < 200 && 350 < resolution.y - mouseY && resolution.y - mouseY < 450 && rombs[6].GetPosition() != 0)
        {
            rombs[6].SetDie(1);

        }
        //3 2
        if (250 < mouseX && mouseX < 350 && 350 < resolution.y - mouseY && resolution.y - mouseY < 450 && rombs[7].GetPosition() != 0)
        {
            rombs[7].SetDie(1);

        }
        //3 3
        if (400 < mouseX && mouseX < 500 && 350 < resolution.y - mouseY && resolution.y - mouseY < 450 && rombs[8].GetPosition() != 0)
        {
            rombs[8].SetDie(1);

        }
    }
    if (button == 1)
    {
        if (!picked)
        {
            //Check if you try to pick a romb
            if (resolution.y - 600 >= mouseY && mouseY >= resolution.y - 600 - 100)
            {
                if (150 < mouseX && mouseX < 250)
                {
                    picked = 1;
                    pickedRomb.SetType(1);
                    pickedRomb.SetX(mouseX);
                    pickedRomb.SetY(resolution.y - mouseY);
                }
                if (300 < mouseX && mouseX < 400)
                {
                    picked = 1;
                    pickedRomb.SetType(2);
                    pickedRomb.SetX(mouseX);
                    pickedRomb.SetY(resolution.y - mouseY);
                }
                if (450 < mouseX && mouseX < 550)
                {
                    picked = 1;
                    pickedRomb.SetType(3);
                    pickedRomb.SetX(mouseX);
                    pickedRomb.SetY(resolution.y - mouseY);
                }
                if (600 < mouseX && mouseX < 700)
                {
                    picked = 1;
                    pickedRomb.SetType(4);
                    pickedRomb.SetX(mouseX);
                    pickedRomb.SetY(resolution.y - mouseY);
                }
            }
        }
    }
    if (button == 1)
        if (pointsUp)
        {
            //Check if you try to pick a star point
            for (int i=0;i<3;i++)
                if (pointStars[i].GetToRand() && mouseX - 30 < pointStars[i].GetX() && pointStars[i].GetX() < mouseX + 30
                    && resolution.y - mouseY - 30 < pointStars[i].GetY() && pointStars[i].GetY() < resolution.y - mouseY + 30)
                {
                    pointsUp--;
                    if (totalPoints < 9)
                        totalPoints++;
                    pointStars[i].SetToRand(0);
                }
        }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    glm::ivec2 resolution = window->GetResolution();
    // Add mouse button release event
    //Check if a picked romb is realesed
    if (button == 1 && picked)
    {
        picked = 0;

        //1 1
        if (100 < mouseX && mouseX < 200 && 50 < resolution.y - mouseY && resolution.y - mouseY < 150 && rombs[0].GetPosition() == 0)
            if (DecreaseTotalPoints(pickedRomb.GetType()))
            {
                rombs[0].SetPosition(1);
                rombs[0].SetType(pickedRomb.GetType());
                rombs[0].SetScale(20);
                rombs[0].SetDie(0);
            }
        //1 2
        if (250 < mouseX && mouseX < 350 &&  50 < resolution.y - mouseY && resolution.y - mouseY <  150 && rombs[1].GetPosition() == 0)
            if (DecreaseTotalPoints(pickedRomb.GetType()))
            {
                rombs[1].SetPosition(1);
                rombs[1].SetScale(20);
                rombs[1].SetDie(0);
                rombs[1].SetType(pickedRomb.GetType());
            }
        //1 3
        if (400 < mouseX && mouseX < 500 &&  50 < resolution.y - mouseY && resolution.y - mouseY <150 
            && rombs[2].GetPosition() == 0 )
            if (DecreaseTotalPoints(pickedRomb.GetType()))
            {
                rombs[2].SetPosition(1);
                rombs[2].SetType(pickedRomb.GetType());
                rombs[2].SetScale(20);
                rombs[2].SetDie(0);
            }
        //2 1
        if (100 < mouseX && mouseX < 200 &&  200 < resolution.y - mouseY && resolution.y - mouseY < 300 && rombs[3].GetPosition() == 0)
            if (DecreaseTotalPoints(pickedRomb.GetType()))
            {
                rombs[3].SetPosition(1);
                rombs[3].SetType(pickedRomb.GetType());
                rombs[3].SetScale(20);
                rombs[3].SetDie(0);
            }
        //2 2
        if (250 < mouseX && mouseX < 350 && 200 < resolution.y - mouseY && resolution.y - mouseY <  300 && rombs[4].GetPosition() == 0)
            if (DecreaseTotalPoints(pickedRomb.GetType()))
            {
                rombs[4].SetPosition(1);
                rombs[4].SetType(pickedRomb.GetType());
                rombs[4].SetScale(20);
                rombs[4].SetDie(0);
            }
        //2 3
        if (400 < mouseX && mouseX < 500 && 200 < resolution.y - mouseY && resolution.y - mouseY <  300 && rombs[5].GetPosition() == 0)
            if (DecreaseTotalPoints(pickedRomb.GetType()))
            {
                rombs[5].SetPosition(1);
                rombs[5].SetType(pickedRomb.GetType());
                rombs[5].SetScale(20);
                rombs[5].SetDie(0);
            }
        //3 1
        if (100 < mouseX && mouseX < 200 && 350 < resolution.y - mouseY && resolution.y - mouseY <450 && rombs[6].GetPosition() == 0)
            if (DecreaseTotalPoints(pickedRomb.GetType()))
            {
                rombs[6].SetPosition(1);
                rombs[6].SetType(pickedRomb.GetType());
                rombs[6].SetScale(20);
                rombs[6].SetDie(0);
            }
        //3 2
        if (250 < mouseX && mouseX < 350 &&  350 < resolution.y - mouseY && resolution.y - mouseY < 450 && rombs[7].GetPosition() == 0)
            if (DecreaseTotalPoints(pickedRomb.GetType()))
            {
                rombs[7].SetPosition(1);
                rombs[7].SetType(pickedRomb.GetType());
                rombs[7].SetScale(20);
                rombs[7].SetDie(0);
            }
        //3 3
        if (400 < mouseX && mouseX < 500 &&  350 < resolution.y - mouseY && resolution.y - mouseY <  450 && rombs[8].GetPosition() == 0)
            if (DecreaseTotalPoints(pickedRomb.GetType()))
            {
                rombs[8].SetPosition(1);
                rombs[8].SetType(pickedRomb.GetType());
                rombs[8].SetScale(20);
                rombs[8].SetDie(0);
            }
    }
}

//Check if there are enough points for a romb and update total points
bool Tema1::DecreaseTotalPoints(int type)
{
    switch (type)
    {
    case 1:
    {
        if (totalPoints >= 0)
        {
            totalPoints--;
            return 1;
        }
        return 0;
    }
    case 2:
    {
        if (totalPoints >= 1)
        {
            totalPoints -= 2;

            return 1;
        }
        return 0;
    }
    case 3:
    {
        if (totalPoints >= 1)
        {
            totalPoints -= 2;

            return 1;
        }
        return 0;
    }
    case 4:
    {
        if (totalPoints >= 2)
        {
            totalPoints -= 3;
            return 1;
        }
        return 0;;
    }
    default:
        break;
    }
}
void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
