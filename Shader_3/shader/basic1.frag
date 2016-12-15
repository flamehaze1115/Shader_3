#version 400

in vec3 LightIntensity;

void main(void)
{
	gl_FragColor = vec4(LightIntensity, 1.0);
	//gl_FragColor = vec4(1.0,1.0,0.5, 1.0);
}
