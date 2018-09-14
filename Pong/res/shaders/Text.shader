#shader vertex
#version 410 core

layout(location = 0) in vec4 vertex;

out vec2 texCoords;

uniform mat4 projection2;

void main()
{
	texCoords = vertex.zw;
	gl_Position = projection2 * vec4(vertex.xy, 0.0, 1.0);

};

#shader fragment
#version 410 core

in vec2 texCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor2;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);
	color = vec4(textColor2, 1.0) * sampled;


};
