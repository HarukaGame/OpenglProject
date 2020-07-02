attribute vec3 position;
attribute vec2 texture_uv;
uniform vec3 add;
uniform vec3 scale;
varying vec2 _texture_uv;
void main(void) {
    _texture_uv = texture_uv;
    vec3 newPos = vec3(position.x * scale.x,position.y*scale.y,position.z);
    gl_Position = vec4(newPos,1) + vec4(add,0);
}