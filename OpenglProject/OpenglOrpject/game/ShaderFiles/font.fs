uniform sampler2D texture;
varying vec2 _texture_uv;
void main(void) {
    vec4 tempColor = texture2D(texture,_texture_uv);
    float a = step(0.5,tempColor.r);
    gl_FragColor = vec4(tempColor.r,tempColor.g,tempColor.b,a);
}