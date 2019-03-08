#version 120

uniform sampler2D unit;

varying vec2 textcoord;

void main(){

    gl_FragColor = texture2D(unit, textcoord);
}