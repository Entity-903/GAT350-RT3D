#version 430

in layout(location = 0) vec3 texcoord;

out layout(location = 0) vec4 ocolor;

layout(binding = 4) uniform samplerCube cubemap;

void main()
{
	ocolor = texture(cubemap, texcoord);
}
