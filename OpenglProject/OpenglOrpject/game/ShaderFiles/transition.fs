uniform sampler2D texture;
uniform vec4 color;
uniform float ratio;
uniform float slope;
varying vec2 _texture_uv;

void main(void) {
    //gl_FragColor = vec4(_texture_uv.x,_texture_uv.y,0.0,1.0) + vec4(_normal.x,_normal.y,_normal.z,1.0)*0.01;
    vec4 rule = texture2D(texture,_texture_uv);
    vec4 newcolor = color;
    //newcolor.a = step(ratio,rule.x);
    newcolor.a = slope * clamp(rule.x + (ratio * 2.0 -1.0),0.0,1.0) - 0.5 * slope + 0.5;
    gl_FragColor = newcolor;
}