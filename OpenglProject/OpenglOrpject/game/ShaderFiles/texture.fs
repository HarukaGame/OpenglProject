uniform sampler2D texture;
uniform sampler2D normal_map;
uniform vec3 light;
varying vec2 _texture_uv;
void main(void) {
    //gl_FragColor = vec4(_texture_uv.x,_texture_uv.y,0.0,1.0) + vec4(_normal.x,_normal.y,_normal.z,1.0)*0.01;
    vec3 normal = (texture2D(normal_map,_texture_uv) * 2.0 -1.0).rgb;
    vec3 elight = normalize(light);
    float d = clamp(dot(elight,normal),0.2,1);
    gl_FragColor = texture2D(texture,_texture_uv) * vec4(vec3(d),1.0);
}