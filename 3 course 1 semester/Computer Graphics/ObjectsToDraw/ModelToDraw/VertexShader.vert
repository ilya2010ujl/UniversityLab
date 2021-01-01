uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;
attribute vec3 vertex;
attribute vec3 normal;

attribute vec3 color;
varying vec3 m_color;

varying vec3 m_vertex;
varying vec3 m_normal;

void main(void)
{
    m_vertex = vec3(modelViewMatrix * vec4(vertex, 1.0));
    m_normal = vec3(normalMatrix * vec4(normal, 1.0));
    m_color = color;
    gl_Position = projectionMatrix * vec4(m_vertex, 1.0);
}
