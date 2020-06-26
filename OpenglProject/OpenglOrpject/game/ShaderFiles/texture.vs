attribute vec3 position;
attribute vec3 normals;
attribute vec2 texture_uv;
uniform mat4 MVP;
varying vec3 _normal;
varying vec2 _texture_uv;
void main(void) {
    _normal = normals;
    _texture_uv = texture_uv;
    vec4 v = vec4(position, 1.0);
    gl_Position = MVP * v;
}