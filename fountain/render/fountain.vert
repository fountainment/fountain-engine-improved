#version 130

in vec4 feiVertex;
in vec2 feiTexCoord;
out vec4 v_color;
out vec2 v_texcoord;
out vec3 v_worldcoord;

void main()
{
	v_color = gl_Color;
	v_texcoord = feiTexCoord;
	v_worldcoord = vec3(gl_ModelViewMatrix * feiVertex);
	gl_Position = gl_ModelViewProjectionMatrix * feiVertex;
}
