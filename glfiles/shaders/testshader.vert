#version 120

attribute vec3 position;
attribute vec2 textcoord;

varying vec2 textcoord0;

void main(){

    gl_Position = vec4(position, 1.0);
    textcoord0 = textcoord;

}