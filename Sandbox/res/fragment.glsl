#version 440
in vec3 fPos;
out vec4 color;

void main() {
    color = vec4(fPos.x+0.5f, 0.5f, fPos.y+0.5f, 1);
}