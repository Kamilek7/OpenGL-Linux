#version 330 core

out vec4 FragColor;
in vec3 pos;
in vec3 normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

// Blender ma skill issue z teksturami
uniform vec3 generatedColor;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight()
{	
	vec3 lightVec = lightPos - pos;
	float dist = length(lightVec);
	float a = 0.0;
	float b = 0.3;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	float ambient = 0.20f;
	vec3 normalL = normalize(normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normalL, lightDirection), 0.0f);
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - pos);
	vec3 reflectionDirection = reflect(-lightDirection, normalL);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;
	
	vec4 tex = texture(diffuse0, texCoord);
	//Skill issue Blendera bo niezaleznie od tego ile razy eksportuje plik tekstur w ogole nie ma
	
	if (tex == vec4(0.0f,0.0f,0.0f,1.0f))
	{
		tex = vec4(generatedColor,1.0f);
	}

	return (tex * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

void main()
{
	FragColor = pointLight();
}