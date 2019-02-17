#version 120

uniform sampler2D samp;

varying vec2 textcoord0;

void main(){


    gl_FragColor = texture2D(samp, textcoord0);

}