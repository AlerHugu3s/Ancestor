#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Pos;

void main()
{
	v_Pos = a_Position;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
}

#type fragment
#version 330 core

out vec4 FragColor;
in vec3 v_Pos;

layout(location = 0) out vec4 color; 

void main()
{
	color = vec4(v_Pos,1.0);
}