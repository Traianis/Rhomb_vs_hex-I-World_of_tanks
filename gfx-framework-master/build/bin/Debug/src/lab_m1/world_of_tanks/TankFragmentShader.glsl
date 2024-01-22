#version 330

// Input
in vec3 frag_position;
in vec3 frag_color;
flat in int frag_life;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    float dmg = 0.f;
    if (frag_life == 3)
       {dmg = 0.f;}
    else 
    {
        if (frag_life == 2)
            dmg = 30.f;
        else
            dmg = 60.f;
    }
    out_color = vec4(frag_color, 1);
    out_color[0] = out_color[0] * (1.f - dmg / 100.f);
    out_color[1] = out_color[1] * (1.f - dmg / 100.f);
    out_color[2] = out_color[2] * (1.f - dmg / 100.f);

}
