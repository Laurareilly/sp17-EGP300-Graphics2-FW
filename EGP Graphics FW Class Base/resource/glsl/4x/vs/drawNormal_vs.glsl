/*
	Draw Normal
	By Laura Reilly
*/

#version 410

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;
layout(location = 8) in vec2 texcoord;
layout(location = 18) in vec4 tangent; //i think this is the one I want?

out vertex
{
	vec3 lightIntensity; //intensity of the ambient, diffuse, & specular
} data;

out vec3 LightDirection;
out vec2 Texcoord;
out vec3 ViewDirection;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 mvp;
uniform mat3 normalMatrix;
uniform vec4 lightPos;

void main()
{
	//transform normal and tangent to eye space
	vec3 norm = normalize(normalMatrix * normal);
	vec3 tang = normalize(normalMatrix * vec3(tangent));

	//compute the binormal
	vec3 binormal = normalize(cross(norm, tang)) * tangent.w;

	//matrix for transformation to tangent space
	mat3 toObjectLocal = mat3(tang.x, binormal.x, norm.x, 
							  tang.y, binormal.y, norm.y,
							  tang.z, binormal.z, norm.z);

	//get the position in eye coords
	vec3 pos = vec3(modelViewMatrix * vec4(position, 1.0));

	//transform light direction and view direction to tangent space
	LightDirection = normalize(toObjectLocal * (lightPos.xyz - pos));

	ViewDirection = toObjectLocal * normalize(-pos);

	//pass along the texture coordinate
	Texcoord = texcoord;

	gl_Position = mvp * vec4(position, 1.0);
}