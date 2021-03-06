#version 450

uniform int workGroupsX;
uniform sampler2D texture1;

in VertexShaderOutput{
	vec3 positionVS;
	vec2 texCoord;
	vec3 normalVS;
} fragment_in;


out vec4 frag_colour;

#define POINT_LIGHT 0
#define SPOT_LIGHT 1
#define DIRECTIONAL_LIGHT 2

struct Light
{
    vec4  PositionWS;
    vec4  DirectionWS;
    vec4  PositionVS;
    vec4  DirectionVS;
    vec4  Color;
    float SpotlightAngle;
    float Range;
    float Intensity;
    bool  Enabled;
    bool  Selected;
    uint  Type;
    vec2  Padding;
};

struct LightingResult
{
    vec4 Diffuse;
    vec4 Specular;
};

layout(binding = 0) readonly buffer LightBuffer {
	Light data[];
} lights;

layout(binding = 1) readonly buffer LightGrid {
	uvec2 data[];
} lightGrid;

layout(binding = 2) readonly buffer LightIndexList {
	uint data[];
} lightIndexList;



vec4 DoDiffuse(Light light, vec4 L, vec4 N)
{
	float NdotL = max(dot(N,L),0);
	return light.Color * NdotL;
}

vec4 DoSpecular(Light light, vec4 V, vec4 L, vec4 N)
{
	vec4 R = normalize(reflect(-L, N));
	float RdotV = max(dot(R, V), 0);

	return light.Color * pow(RdotV, 128);
}

float DoAttenuation( Light light, float d )
{
    return 1.0f - smoothstep( light.Range * 0.75f, light.Range, d );
}

LightingResult DoPointLight(Light light, vec4 V, vec4 P, vec4 N)
{
	LightingResult result;
	vec4 L = light.PositionVS - P;
	float distance = length(L);
	L = L / distance;

	float attenuation = DoAttenuation(light, distance);
	result.Diffuse = DoDiffuse(light, L, N) * light.Intensity * attenuation;

	result.Specular = DoSpecular(light, V, L, N) * light.Intensity * attenuation;
	
	return result;
}


#define BLOCK_PIXEL_SIZE 32
#define TEXTURE_SIZE 1024

#define TILE_SIZE 16
void main () {

	ivec2 location = ivec2(gl_FragCoord.xy);
	ivec2 tileID = location / ivec2(TILE_SIZE, TILE_SIZE);
	uint index = tileID.y * workGroupsX + tileID.x;

	uint startOffSet = lightGrid.data[index].x;
	uint lightCount = lightGrid.data[index].y;

	vec4 eyePos = vec4(0, 0, 0, 1);
	vec4 P = vec4(fragment_in.positionVS, 1);
	vec4 V = normalize(vec4(eyePos - P));

	// NORMALS - TODO: ADD NORMALMAP
	vec4 N = normalize(vec4(fragment_in.normalVS, 0));

	LightingResult totalResult;
	totalResult.Diffuse = vec4(0);
	totalResult.Specular = vec4(0);

	for(uint i = 0; i < lightCount; i++)
	{
		uint lightIndex = lightIndexList.data[startOffSet + i];
        Light light = lights.data[lightIndex];

        LightingResult result;
        result.Diffuse = vec4(0);
        result.Specular = vec4(0);

        switch(light.Type)
        {
        	case POINT_LIGHT:
        	{
        		result = DoPointLight(light, V, P, N);
        	}
        	break;
        	// todo: do rest.
        }

        totalResult.Diffuse += result.Diffuse;
        totalResult.Specular += result.Specular;
	}

	//float ratio = float(lightCount) / float(256);
	vec2 realTexCoord = fragment_in.texCoord * BLOCK_PIXEL_SIZE / TEXTURE_SIZE;
	//frag_colour = mix(vec4(vec3(ratio), 1.0), texture(texture1, realTexCoord), 0.5f);
	frag_colour = mix(vec4(vec3(totalResult.Diffuse.rgb) + vec3(totalResult.Specular.rgb), 1.0), texture(texture1, realTexCoord), 0.5f);
}