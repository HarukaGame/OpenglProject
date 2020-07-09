attribute vec3 position;
attribute vec2 texture_uv;
uniform mat4 MVP;
varying vec2 _texture_uv;
void main(void) {
    _texture_uv = texture_uv;
    vec4 v = vec4(position, 1.0);
    gl_Position = MVP * v;
}