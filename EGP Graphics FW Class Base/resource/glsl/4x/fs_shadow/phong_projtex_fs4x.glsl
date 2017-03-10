/*
	Phong with Projective Texturing
	By Dan Buckstein
	Fragment shader that performs Phong shading and projective texturing.
	
	Modified by: ______________________________________________________________
*/

#version 410


// varyings: 
in vertexdata
{
	vec4 position_clip_alt;
	vec4 normal;
	vec4 texcoord;
	vec4 lightVec;
	vec4 eyeVec;
} pass;


// uniforms: 
uniform sampler2D tex_dm;
uniform sampler2D tex_sm;

uniform sampler2D tex_bool;
uniform sampler2D projtex;

uniform vec4 lightColor;


// target: 
layout (location = 0) out vec4 fragColor;


// constants/globals: 
const vec4 AMBIENT = vec4(0.02, 0.01, 0.0, 0.0);
vec2 booleanSample = vec2(0.0);


void main()
{
	vec4 projector_uv = pass.position_clip_alt / pass.position_clip_alt.w;
	vec4 projectedTex = texture(projtex, projector_uv.xy);

	// determine if point is in front of the light's near plane
//	booleanSample.x = pass.position_clip_alt.z + 1.0;
//	projectedTex *= texture(tex_bool, booleanSample).r;
	
	// albedo
	vec4 diffuseColor = texture(tex_dm, pass.texcoord.xy);
	vec4 specularColor = texture(tex_sm, pass.texcoord.xy);

	// diffuse shading
	vec4 N = normalize(pass.normal);
	vec4 L = normalize(pass.lightVec);
	float kd = dot(N, L);
	
	// specular shading
	vec4 V = normalize(pass.eyeVec);
	vec4 R = (kd+kd)*N - L;
	float ks = dot(V, R);
	
	// clamp
	kd = max(0.0, kd);
	ks = max(0.0, ks);
	
	// specular exponent
	ks *= ks;
	ks *= ks;
	ks *= ks;
	ks *= ks;
	ks *= ks;
	ks *= ks;

	// phong model with projective texture
	fragColor = (diffuseColor*kd + specularColor*ks)*lightColor*projectedTex + AMBIENT;
	
// DEBUGGING
//	fragColor = lightColor;
//	fragColor = normalize(pass.lightVec) * 0.5 + 0.5;
//	fragColor = normalize(pass.eyeVec) * 0.5 + 0.5;
//	fragColor = normalize(pass.normal) * 0.5 + 0.5;
//	fragColor = vec4(projector_dist);
//	fragColor = projectedTex;
}