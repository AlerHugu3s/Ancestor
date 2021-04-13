#type vertex
#version 330 core
layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out vec2 v_TexCoords;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

void main()
{
	v_TexCoords = a_TexCoords;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos, 1.0);
}

#type fragment
#version 330 core
out vec4 FragColor;

in vec2 v_TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
    //FragColor = texture(texture_diffuse1, v_TexCoords);
	FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}