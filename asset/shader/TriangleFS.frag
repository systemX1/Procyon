// #version 460 core
// out vec4 FragColor;

// layout (location = 0) in vec3 color;

// void main()
// {
//    FragColor = vec4(color, 1.0);
// } 

#version 460 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 

