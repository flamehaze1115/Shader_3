#version 400
layout (location = 0) in vec3 VertexPosition;  
layout (location = 1) in vec3 VertexNormal;  

out vec3 LightIntensity;

struct SpotLightInfo{
	vec4 position;
	vec3 direction;
	vec3 intensity;
	float exponent;
	float cutoff;
};

struct MaterialInfo{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};

uniform SpotLightInfo Spot;
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



vec3 adsSpotLight(vec4 position, vec3 norm)
{
	vec3 s = normalize(vec3(Spot.position - position));
	float angle = acos(dot(-s, normalize(Spot.direction)));
	float cutoff = radians(clamp(Spot.cutoff, 0.0, 90.0));
	vec3 ambient = Spot.intensity * Material.Ka;
	
	if(angle < cutoff){
		float spotFactor = pow(dot(-s, normalize(Spot.direction)), Spot.exponent);
		vec3 v = normalize(vec3(-position));
		vec3 h = normalize(v + s);
		return ambient + spotFactor * Spot.intensity * (Material.Kd * max(dot(s, norm),0.0)
		      + Material.Ks * pow(max(dot(h,norm), 0.0),Material.Shininess)); 
	}
	else
	{
		return ambient; 
	}
	       
}

void main()
{
	vec3 eyeNorm;
	vec4 eyePosition;
	getEyeSpace(eyeNorm, eyePosition);
	
	LightIntensity = adsSpotLight(eyePosition, eyeNorm);
	
	gl_Position = MVP * vec4( VertexPosition, 1.0);
}
