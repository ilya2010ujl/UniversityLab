varying vec3 m_vertex;
varying vec3 m_normal;
varying vec3 m_color;

void main(void)
{
    vec3 color = m_color;

    gl_FragColor = vec4(color, 1.0);
}
