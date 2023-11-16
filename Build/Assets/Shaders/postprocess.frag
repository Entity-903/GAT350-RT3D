#version 430

#define INVERT_MASK     1
#define GRAYSCALE_MASK  2
#define COLORTINT_MASK  4
#define GRAIN_MASK	    8
#define SCANLINE_MASK   16
#define EXTREMERGB_MASK 32


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

float random(vec2 st) 
{
	return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec4 grain(in vec4 color)
{
	return vec4(vec3(color) * random(gl_FragCoord.xy), color.a);
}

vec4 scanline(in vec4 color)
{
	int y = int(gl_FragCoord.y);
	return (y % 3 != 0) ? vec4(0, 0, 0, color.a) : color;
}

vec3 convertRGBToHSV(in vec3 color)
{
	// Divides color.r, color.g, and color.b values by 255
	// This creates a float value
	float r = color.r / 255.0f;
	float g = color.g / 255.0f;
	float b = color.b / 255.0f;

	// Calculate cmax, cmin, diff; Instantiates hue (h) and saturation (s)
	float cmax = max(r, max(g, b)); // Max of r, g, b
	float cmin = min(r, min(g, b)); // Min of r, g, b
	float diff = cmax - cmin;
	float h = -1; // Hue
	float s = -1; // Saturation

	// Defines hue
	if (cmax == cmin) h = 0;
	else if (cmax == r) h = mod(60 * ((g - b) / diff), 360);
	else if (cmax == g) h = mod(60 * ((b - r) / diff) + 120, 360);
	else if (cmax == b) h = mod(60 * ((r - g) / diff) + 240, 360);

	// Define Saturation
	s = (cmax == 0) ? 0 : (diff / cmax) * 100;

	// Compute value (v)
	float v = cmax * 100;

	return vec3(h, s, v);
}

vec3 convertHSVToRGB(in vec3 hsv)
{
	float C = hsv.y * hsv.z;
    float X = C * ( 1 - abs( mod( hsv.x/60.0, 2) - 1));
    float m = hsv.z - C;
    float r,g,b;

    if (hsv.x >= 0 && hsv.x < 60) r = C,g = X,b = 0;
    else if(hsv.x >= 60  && hsv.x < 120) r = X,g = C,b = 0;
    else if(hsv.x >= 120 && hsv.x < 180) r = 0,g = C,b = X;
    else if(hsv.x >= 180 && hsv.x < 240) r = 0,g = X,b = C;
    else if(hsv.x >= 240 && hsv.x < 300) r = X,g = 0,b = C;
    else r = C,g = 0,b = X;
    
    float R = (r+m) * 255; // *255
    float G = (g+m) * 255; // *255
    float B = (b+m) * 255; // *255

	return vec3( R, G, B);
}

// Originally was supposed to be tritanopia, Blue-Yellow colorblindness
vec4 extremergb(in vec4 color)
{
	vec3 hsv = convertRGBToHSV(color.rgb);

	// The closer Hue is to 60 or 240, the closer Value is set to 1
	// Within that group of values, Hue is then set to 180

	// Calculate altered hsv values
	//if (hsv.x < 180 && hsv.x >= 60)
	//{
	//	float percentage = (180 - hsv.x) / 120;
	//	//v -= v(percentage); 
	//	hsv.y -= hsv.y * percentage;
	//}
	//else if (hsv.x > 180 && hsv.x <= 240) 
	//{
	//	float percentage = (hsv.x - 180) / 60;
	//	hsv.z -= hsv.z * percentage;
	//	//s -= s(percentage);
	//}

	// Convert back to rgb
	color.rgb = convertHSVToRGB(hsv);


	return vec4(color);
}

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

		if (bool(params & GRAIN_MASK))
	{
		postprocess = grain(postprocess);
	}

		if (bool(params & SCANLINE_MASK))
	{
		postprocess = scanline(postprocess);
	}

		if (bool(params & EXTREMERGB_MASK))
	{
		postprocess = extremergb(postprocess);
	}

	ocolor = mix(baseColor, postprocess, blend);
}
