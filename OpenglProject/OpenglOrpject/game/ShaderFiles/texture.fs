uniform sampler2D texture;
varying vec3 _normal;
varying vec2 _texture_uv;
void main(void) {
    //gl_FragColor = vec4(_texture_uv.x,_texture_uv.y,0.0,1.0) + vec4(_normal.x,_normal.y,_normal.z,1.0)*0.01;
    gl_FragColor = texture2D(texture,_texture_uv);
}