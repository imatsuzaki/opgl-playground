# version 150 core
uniform mat4 model;
in vec4 position;
void main()
{
    gl_position = model * position;
}
