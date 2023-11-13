#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec2 texcoord;

out layout(location = 0) vec2 otexcoord;

void main()
{
	otexcoord = texcoord;

	gl_Position = vec4(position, 1.0);
}
