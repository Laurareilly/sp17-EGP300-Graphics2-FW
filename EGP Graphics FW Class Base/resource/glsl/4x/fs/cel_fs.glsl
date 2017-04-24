///*
//	Cel fs
//	By Laura Reilly
//	Fragment shader for cel shading
//*/

#version 410

//varyings
in vertex
{
	vec4 normal;
	vec4 lightVec;
	vec4 eyeVec;
	vec2 texcoord;
} data;

//uniforms
uniform sampler2D tex_dm;
uniform sampler2D tex_sm;

//target
layout (location = 0) out vec4 fragColor;

vec2 rampCoord = vec2(0.0);
const vec3 ambience =  vec3(0.01, 0.0, 0.0);

void main()
{
	vec4 N = normalize(data.normal);
	vec4 L = normalize(data.lightVec);

	//the dot product of the normal and the lighting directure gives ur our texture coordinate
	float diffuse = dot(N, L); 

	rampCoord.x = diffuse * 0.5 + 0.5;
	vec4 rampSample = texture(tex_sm, rampCoord);
	fragColor = rampSample;
	//fragColor = texture(tex_sm, data.texcoord.xy);
}


