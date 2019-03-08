#version 120

attribute vec3 position;
attribute vec2 texturecoord;

varying vec2 textcoord;

void main(){

   gl_Position = vec4(position, 1.0);
   textcoord= texturecoord ;
}