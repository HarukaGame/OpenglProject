attribute vec3 position;
attribute vec2 texture_uv;
uniform vec3 add;
uniform vec2 uv;
varying vec2 _texture_uv;
void main(void) {
    _texture_uv = texture_uv + uv;
    gl_Position = vec4(position,1) + vec4(add,0);
}