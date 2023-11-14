#version 430

#define INVERT_MASK    1
#define GRAYSCALE_MASK 2
#define COLORTINT_MASK 4


in layout(location = 0) vec2 texcoord;

out layout(location = 0) vec4 ocolor;

layout(binding = 0) uniform sampler2D screenTex;

uniform float blend = 1;
uniform uint params = 0;
uniform vec3 tint = vec3(0);

vec4 invert(in vec4 color)
{
	return vec4(vec3(1) - color.rgb, color.a);
}

vec4 grayscale(in vec4 color)
{
	return vec4(vec3((color.r + color.g + color.b) * 0.3333333), color.a);
}

vec4 colortint(in vec4 color)
{
	return vec4(vec3(color) * tint, color.a);
}

// Grain/Scanline needs to be mplemented

void main()
{
	vec4 baseColor = texture(screenTex, texcoord);
	vec4 postprocess = baseColor;

	if (bool(params & INVERT_MASK))
	{
		postprocess = invert(postprocess);
	}

	if (bool(params & GRAYSCALE_MASK))
	{
		postprocess = grayscale(postprocess);
	}

	if (bool(params & COLORTINT_MASK))
	{
		postprocess = colortint(postprocess);
	}

	ocolor = mix(baseColor, postprocess, blend);
}
