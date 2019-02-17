#version 120

uniform sampler2D sam;

void main(){


    gl_FragColor = texture2D(sam, vec2(0.5f,0.5f));

}