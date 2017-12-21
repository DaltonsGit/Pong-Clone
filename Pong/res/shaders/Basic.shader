#shader vertex
#version 410 core

layout(location = 0) in vec4 vertex;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 Projection;

void main()
{
	texCoords = vertex.zw;
	gl_Position = Projection * model * vec4(vertex.xy, 0.0, 1.0);
};



#shader fragment
#version 410 core

layout(location = 0)

in vec2 texCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 u_color;

void main()
{
	color =  texture(image, texCoords);
};