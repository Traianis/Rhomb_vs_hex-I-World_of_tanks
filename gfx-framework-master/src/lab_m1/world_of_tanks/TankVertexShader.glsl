#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;
uniform int life;

// Output
out vec3 frag_position;
out vec3 frag_color;
flat out int frag_life;

void main()
{
    frag_position = v_position;
    frag_color = object_color;
    frag_life = life;

    float dmg = 0;
    if (frag_life == 3)
       {dmg = 1.f;}
    else 
    {
        if (frag_life == 2)
            dmg = 0.8f;
        else
            dmg = 0.6f;
    }
    frag_position.y *= dmg;
    gl_Position = Projection * View * Model * vec4(frag_position, 1.0);

}
