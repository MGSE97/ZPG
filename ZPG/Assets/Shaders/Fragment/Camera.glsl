#version 330
uniform float color;
out vec4 frag_colour;
void main () {
        frag_colour = vec4 (color, 1.0-color, 0.0, 1.0);
}