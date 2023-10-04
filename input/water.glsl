// @Vertex ==================================================================================
#version 330 core

layout (location = 0) in vec3 a_pos;
out vec3 color;

uniform mat4 u_xform;

void main()
{
  gl_Position = u_xform * vec4(a_pos, 1.0);
}

// @Fragment ================================================================================
#version 330 core

out vec4 frag_color;

void main()
{
  frag_color = vec4(color, 1.0);
}
