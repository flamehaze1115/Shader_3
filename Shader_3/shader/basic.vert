#version 400
layout (location = 0) in vec3 VertexPosition;  
layout (location = 1) in vec3 VertexNormal;  

out vec3 LightIntensity;

struct LightInfo{
	vec4 Direction;
	vec3 Intensity;
};

struct MaterialInfo{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};

uniform LightInfo Light;
uniform	MaterialInfo Material;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;


void getEyeSpace(out vec3 norm, out vec4 position)
{
	norm =  normalize(NormalMatrix * VertexNormal);
	position = ModelViewMatrix * vec4(VertexPosition, 1.0);
}



vec3 ads(vec4 position, vec3 norm)
{
	vec3 s;
	if(Light.Direction.w == 0.0)
		s = normalize(vec3(Light.Direction));
	else
		s = normalize(vec3(Light.Direction - position));
	vec3 v = normalize(vec3(-position));
	vec3 r = reflect(-s, norm);

	return Light.Intensity * (Material.Ka + Material.Kd*max(dot(s,norm), 0.0) + 
	       Material.Ks * pow(max(dot(r,v),0.0), Material.Shininess));
}

void main()
{
	vec3 eyeNorm;
	vec4 eyePosition;
	getEyeSpace(eyeNorm, eyePosition);
	LightIntensity = ads(eyePosition, eyeNorm);
	
	gl_Position = MVP * vec4( VertexPosition, 1.0);
}
