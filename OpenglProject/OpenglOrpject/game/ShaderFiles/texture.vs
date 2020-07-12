attribute vec3 position;
attribute vec3 normals;
attribute vec2 texture_uv;
attribute vec3 tangent;
uniform mat4 MVP;
uniform mat3 model_mat;
uniform vec3 light;
varying vec2 _texture_uv;
varying vec3 _light;
void main(void) {
    _texture_uv = texture_uv;

    vec3 n = normalize(normals);
    vec3 t = normalize(tangent);
    vec3 b = cross(n,t);
    vec3 tempLight = model_mat * light;
    _light.x = dot(t,tempLight);
    _light.y = dot(b,tempLight);
    _light.z = dot(n,tempLight);

    vec4 v = vec4(position, 1.0);
    gl_Position = MVP * v;
}