#version 440
in vec3 pos;
out vec3 fPos;
uniform mat4 worldMatrix;
uniform mat4 projectionMatrix;

void main() {
    fPos = pos;
    gl_Position = projectionMatrix * worldMatrix * vec4(pos, 1.0);

}