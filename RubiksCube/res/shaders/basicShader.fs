#version 130

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 color0;

uniform vec3 lightDirection;
uniform vec3 lightColor;

void main()
{
	if(texCoord0.x < 0.05 || texCoord0.x > 0.95 || texCoord0.y < 0.05 || texCoord0.y > 0.95)
		gl_FragColor = vec4(0,0,0,0);
	else{
	    vec3 tmp =/* dot(-lightDirection, normal0) * */ color0 ;
		gl_FragColor =  clamp(vec4(tmp,1.0), 0.0, 1.0);
	}



}
