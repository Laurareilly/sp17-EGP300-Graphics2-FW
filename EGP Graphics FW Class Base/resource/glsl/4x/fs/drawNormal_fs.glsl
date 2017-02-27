/*
	Draw Normal
	By Laura Reilly
*/
#version 410

//we are taking in the same vars from the vs with the same names labeled out
in vec3 LightDirection;
in vec2 Texcoord;
in vec3 ViewDirection;

uniform sampler2D tex_dm;
uniform sampler2D tex_normal;

//same as our struct in the vs
in vertex
{
	vec3 lightIntensity;
} data;

struct materialInfo
{
	vec3 ambience;
	vec3 specular;
	float shininess; //specular shininess factor
};
uniform materialInfo material;

layout(location = 0) out vec4 fragColor;

vec3 phongModel(vec3 norm, vec3 diffR)
{
	vec3 r = reflect(-LightDirection, norm);
	vec3 ambient = data.lightIntensity * material.ambience;
	float sDotN = max(dot(LightDirection, norm), 0.0);
	vec3 diffuse = data.lightIntensity * diffR * sDotN;

	vec3 specular = vec3(0.0);
	if(sDotN > 0.0) //i dont want ot use an if statement ahhh get rid of thise
	{
		specular = data.lightIntensity * material.specular * pow(max(dot(r, ViewDirection), 0.0), material.shininess);
	}
	
	return ambient + diffuse + specular;
}


void main()
{
	//lookup the normal from the normal map
	vec4 normal = 2.0 * texture(tex_normal, Texcoord) - 1.0;

	//the color texture is used as the diffuse reflectivity
	vec4 texColor = texture(tex_dm, Texcoord);
	vec3 tempColor = vec3(.5f, .5f, .5f);

	fragColor = vec4(phongModel(normal.xyz, texColor.rgb), 1.0);
}