#version 130

const int RENDER_PLAIN = 0;
const int RENDER_BLUR = 1;
const int RENDER_BASIC = 2;
const int RENDER_HDR = 3;
const int RENDER_FINAL = 4;

const float eps = 0.00001;
const float Pi = 3.14159265358979323846;
const vec3 LuminanceVector = vec3(0.2125, 0.7154, 0.0721);

const float DefaultSpotCosCutOff = 0.97;
const float DefaultSpotExponent = 5.0;
const int LightMaxNum = 64;
const int POINT_LIGHT = 0;
const int DIRECTIONAL_LIGHT = 1;
const int SPOT_LIGHT = 2;

//Engine
uniform int feiRenderMode;
uniform vec2 feiMouse;
uniform float feiTime;
uniform vec3 feiViewCoord;

out vec4 feiColorOutput;
out vec4 feiEmitOutput;

//Basic
uniform bool feiUseTex;
uniform bool feiUseEmitTex;
uniform bool feiUseNormalTex;
uniform bool feiUseCullTex;
uniform bool feiUseLight;

uniform sampler2D feiTex;
uniform sampler2D feiEmitTex;
uniform sampler2D feiNormalTex;
uniform sampler2D feiCullTex;

uniform vec3 feiNormalValue;

//Blur
uniform float feiBlurRadius;
uniform float feiSampleNum;

//Material
uniform vec3 feiKd; // Cdiff/Pi
uniform vec3 feiKs; // ((m+8)/8Pi)Cspec
uniform float feiSmoothness;
uniform float feiEmitValue;
float feiEmitHaloValue = 0.5;
uniform float feiEmitAllValue;

//Light Source
uniform int feiLightNum;
uniform int feiLightType[LightMaxNum];
uniform vec3 feiLightPos[LightMaxNum];
uniform vec3 feiLightDirection[LightMaxNum];
uniform vec4 feiLightColor[LightMaxNum];
uniform float feiLightRadius[LightMaxNum];

//HDR
uniform float feiLw; //HDR
uniform float feiLwhite;

in vec4 v_color;
in vec2 v_texcoord;
in vec3 v_worldcoord;

vec3 g_ViewDirection = normalize(v_worldcoord - feiViewCoord);
float g_gamma = 2.2;

//Utility
vec3 getNormalFromNormalMap(sampler2D normalMap, vec2 texCoord, mat3 normalMatrix);
vec4 blur(sampler2D texture, vec2 texCoord, float blurRadius, float sampleNum);

void rgb2hsv(inout vec3 color);
void hsv2rgb(inout vec3 color);

void rgb2hsl(inout vec3 color);
void hsl2rgb(inout vec3 color);

void rgb2linear(inout vec3 rgb);
void linear2rgb(inout vec3 linear);

float getLuminance(vec4 color);

void DirectionalLight(inout vec4 result, vec4 texColor, vec3 normal, vec3 lightDirection, vec3 lightColor, float lightIntensity);
void PointLight(inout vec4 result, vec4 texColor, vec3 normal, vec3 lightPos, float lightRadius, vec3 lightColor, float lightIntensity);
void SpotLight(inout vec4 result, vec4 texColor, vec3 normal, vec3 lightPos, vec3 lightDirection, float lightRadius, float lightCosCutOff, vec3 lightColor, float lightIntensity);
float ToneMap(float Lw);

//Render Pass
void renderPlain();
void renderBlur();
void renderBasic();
void renderHDR();
void renderFinal();

void main()
{
	switch (feiRenderMode) {
	case RENDER_PLAIN:
		renderPlain();
		break;
	case RENDER_BLUR:
		renderBlur();
		break;
	case RENDER_BASIC:
		renderBasic();
		break;
	case RENDER_HDR:
		renderHDR();
		break;
	case RENDER_FINAL:
		renderFinal();
		break;
	default:
		renderPlain();
		break;
	}
}

vec3 getNormalFromNormalMap(sampler2D normalMap, vec2 texCoord, mat3 normalMatrix)
{
	vec3 ret = vec3(texture2D(normalMap, texCoord));
	ret *= 2.0;
	ret -= vec3(1.0);
	ret.r *= -1.0;
	ret = normalize(normalMatrix * ret);
	return ret;
}

void PointLight(inout vec3 result, vec3 texColor, vec3 normal, vec3 lightPos, float lightRadius, vec3 lightColor, float lightIntensity)
{
	if (lightIntensity == 0.0) {
		return;
	}
	vec3 pl = lightPos;
	vec3 El = lightColor * lightIntensity;
	float m = feiSmoothness;
	vec3 p = v_worldcoord;

	vec3 n = normal;
	vec3 l = pl - p;
	vec3 nl = normalize(l);
	float len = 0.0;

	float cosThetai = dot(n, nl);
	float cosThetah = 0.0;
	if (cosThetai > 0.0) {
		len = length(l);
		vec3 v = -g_ViewDirection;
		vec3 h = normalize(nl + v);
		cosThetah = max(dot(n, h), 0.0);
	} else {
		return;
	}
	float attenuation = 1.0 / pow((len / lightRadius) + 1.0, 2.0);
	vec3 L0 = (feiKd * texColor + feiKs * pow(cosThetah, m)) * (El * cosThetai * attenuation);
	result += L0;
}

void DirectionalLight(inout vec3 result, vec3 texColor, vec3 normal, vec3 lightDirection, vec3 lightColor, float lightIntensity)
{
	if (lightIntensity == 0.0) {
		return;
	}
	vec3 El = lightColor * lightIntensity;
	float m = feiSmoothness;

	vec3 n = normal;
	vec3 l = -lightDirection;
	vec3 nl = normalize(l);
	float len = 0.0;

	float cosThetai = dot(n, nl);
	float cosThetah = 0.0;
	if (cosThetai > 0.0) {
		len = length(l);
		vec3 v = vec3(0.0, 0.0, 1.0);
		vec3 h = normalize(nl + v);
		cosThetah = max(dot(n, h), 0.0);
	} else {
		return;
	}
	vec3 L0 = (feiKd * texColor + feiKs * pow(cosThetah, m)) * (El * cosThetai);
	result += L0;
}

void SpotLight(inout vec3 result, vec3 texColor, vec3 normal, vec3 lightPos, vec3 lightDirection, float lightRadius, float lightCosCutOff, vec3 lightColor, float lightIntensity)
{
	if (lightIntensity == 0.0) {
		return;
	}
	vec3 pl = lightPos;
	vec3 El = lightColor * lightIntensity;
	float m = feiSmoothness;
	vec3 p = v_worldcoord;

	vec3 n = normal;
	vec3 l = -lightDirection;
	vec3 nl = normalize(l);
	float len = 0.0;

	float cosThetai = dot(n, nl);
	float cosThetah = 0.0;
	if (cosThetai > 0.0) {
		len = length(l);
		vec3 v = -g_ViewDirection;
		vec3 h = normalize(nl + v);
		cosThetah = max(dot(n, h), 0.0);
	} else {
		return;
	}
	float attenuation = 1.0 / pow((len / lightRadius) + 1.0, 2.0);
	float spotCos = dot(l, -lightDirection);
	float cutOffFadeOut = (1.0 - lightCosCutOff) * 2.0;
	float secondCosCutOff = lightCosCutOff - cutOffFadeOut;
	if (spotCos < secondCosCutOff) {
		attenuation = 0.0;
	} else {
		attenuation *= pow(spotCos, DefaultSpotExponent);
		if (spotCos < lightCosCutOff) {
			attenuation *= (spotCos - secondCosCutOff) / cutOffFadeOut;
		}
	}
	vec3 L0 = (feiKd * texColor + feiKs * pow(cosThetah, m)) * (El * cosThetai * attenuation);
	result += L0;
}

vec4 blur(sampler2D texture, vec2 texCoord, float blurRadius, float sampleNum)
{
	if (blurRadius > 0.0 && sampleNum > 1.0) {
		vec4 col = vec4(0.0);
		vec2 unit = 1.0 / textureSize(texture, 0);

		float r = blurRadius;
		float sampleStep = r / sampleNum;

		float count = 0.0;

		for (float x = -r; x < r; x += sampleStep) {
			for (float y = -r; y < r; y += sampleStep) {
				float weight = (r - abs(x)) * (r - abs(y));
				col += texture2D(texture, texCoord + vec2(x * unit.x, y * unit.y)) * weight;
				count += weight; 
			}
		}
		return col / count;
	}
	return texture2D(texture, texCoord);
}

void rgb2hsv(inout vec3 color)
{
	float r = color.r;
	float g = color.g;
	float b = color.b;

	float M = max(max(r, g), b);
	float m = min(min(r, g), b);
	float C = M - m;

	//Hue
	if (C == 0.0) {
		color[0] = -eps; //Undefined
	} else if (M == r) {
		color[0] = 60.0 * mod((g - b) / C, 6.0);
	} else if (M == g) {
		color[0] = 60.0 * (b - r) / C + 120.0;
	} else if (M == b) {
		color[0] = 60.0 * (r - g) / C + 240.0;
	}

	//Saturation
	color[1] = C / M;

	//Value
	color[2] = M;
}

void hsv2rgb(inout vec3 color)
{
	float h = color[0];
	float s = color[1];
	float v = color[2];

	float C = v * s;
	float H = h / 60.0;
	float X = C * (1.0 - abs(mod(H, 2.0) - 1.0));
	if (H < 0.0) color = vec3(0.0);
	else if (H < 1.0) color = vec3(C, X, 0.0);
	else if (H < 2.0) color = vec3(X, C, 0.0);
	else if (H < 3.0) color = vec3(0.0, C, X);
	else if (H < 4.0) color = vec3(0.0, X, C);
	else if (H < 5.0) color = vec3(X, 0.0, C);
	else color = vec3(C, 0.0, X);
	color += vec3(v - C);
}

void rgb2hsl(inout vec3 color)
{
	float r = color.r;
	float g = color.g;
	float b = color.b;

	float M = max(max(r, g), b);
	float m = min(min(r, g), b);
	float C = M - m;
	float L = (M + m) * 0.5;

	//Hue
	if (C == 0.0) {
		color[0] = -eps;
	} else if (M == r) {
		color[0] = 60.0 * mod((g - b) / C, 6.0);
	} else if (M == g) {
		color[0] = 60.0 * (b - r) / C + 120.0;
	} else if (M == b) {
		color[0] = 60.0 * (r - g) / C + 240.0;
	}

	//Saturation
	color[1] = C / (1.0 - abs(2.0 * L - 1.0));

	//Luminance
	color[2] = L;
}

void hsl2rgb(inout vec3 color)
{
	float h = color[0];
	float s = color[1];
	float l = color[2];

	float C = (1.0 - abs(2.0 * l - 1.0)) * s;
	float H = h / 60.0;
	float X = C * (1.0 - abs(mod(H, 2.0) - 1.0));

	if (H < 0.0) color = vec3(0.0);
	else if (H < 1.0) color = vec3(C, X, 0.0);
	else if (H < 2.0) color = vec3(X, C, 0.0);
	else if (H < 3.0) color = vec3(0.0, C, X);
	else if (H < 4.0) color = vec3(0.0, X, C);
	else if (H < 5.0) color = vec3(X, 0.0, C);
	else color = vec3(C, 0.0, X);
	color += vec3(l - C * 0.5);
}

void rgb2linear(inout vec3 rgb)
{
	rgb = pow(rgb, vec3(g_gamma));
}

void linear2rgb(inout vec3 linear)
{
	linear = pow(linear, vec3(1.0 / g_gamma));
}

//Render Pass

void renderPlain()
{
	vec4 color = v_color;

	if (color.a <= 0.0) {
		discard;
	}
	if (feiUseTex) {
		color *= texture2D(feiTex, v_texcoord);
		if (color.a <= 0.0) {
			discard;
		}
	}
	feiColorOutput = color;
}

void renderBlur()
{
	vec4 color = v_color;

	if (color.a <= 0.0) {
		discard;
	}
	color *= blur(feiTex, v_texcoord, feiBlurRadius, feiSampleNum);
	if (color.a <= 0.0) {
		discard;
	}
	feiColorOutput = color;
}

void renderBasic()
{
	vec4 color = v_color;
	vec4 result = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 emitColor = vec4(0.0, 0.0, 0.0, 1.0);
	vec3 normal;

	if (color.a <= 0.0) {
		discard;
	}
	if (feiUseCullTex) {
		if (texture2D(feiCullTex, v_texcoord).rgb == vec3(0.0)) {
			discard;
		}
	}
	if (feiUseTex) {
		vec4 texColor = texture2D(feiTex, v_texcoord);
		if (texColor.a <= 0.0) {
			discard;
		}
		rgb2linear(texColor.rgb);
		color *= texColor;
	}
	if (feiUseEmitTex) {
		emitColor = texture2D(feiEmitTex, v_texcoord);
		if (emitColor.a <= 0.0) {
			emitColor.rgb = vec3(0.0);
		}
		emitColor.a = 1.0;
		rgb2linear(emitColor.rgb);
		emitColor.rgb *= feiEmitValue;
	}
	if (feiUseNormalTex) {
		normal = getNormalFromNormalMap(feiNormalTex, v_texcoord, gl_NormalMatrix);
	} else {
		normal = normalize(gl_NormalMatrix * feiNormalValue);
	}
	if (feiUseLight) {
		result.a = color.a;
		for (int i = 0; i < feiLightNum; i++) {
			switch (feiLightType[i]) {
			case POINT_LIGHT:
				PointLight(result.rgb, color.rgb, normal, feiLightPos[i], feiLightRadius[i], feiLightColor[i].rgb, feiLightColor[i].a);
				break;
			case DIRECTIONAL_LIGHT:
				DirectionalLight(result.rgb, color.rgb, normal, feiLightDirection[i], feiLightColor[i].rgb, feiLightColor[i].a);
				break;
			case SPOT_LIGHT:
				SpotLight(result.rgb, color.rgb, normal, feiLightPos[i], feiLightDirection[i], feiLightRadius[i], DefaultSpotCosCutOff, feiLightColor[i].rgb, feiLightColor[i].a);
				break;
			}
		}
	} else {
		result = color;
	}
	emitColor.rgb += result.rgb * feiEmitAllValue;
	result.rgb += emitColor.rgb * (1.0 - feiEmitHaloValue);
	feiColorOutput = result;
	linear2rgb(emitColor.rgb);
	feiEmitOutput = emitColor;
}

float getLuminance(vec4 color)
{
	return dot(vec3(color), LuminanceVector);
}

float ToneMap(float Lw)
{
	float a = 0.18;
	float Lww = feiLw;
	float L = a / Lww * Lw;
	float Ld = L * (1.0 + L / (feiLwhite * feiLwhite)) / (1.0 + L);
	return Ld;
}

void renderHDR()
{
	vec4 color = texture2D(feiTex, v_texcoord);
	if (color.a <= 0.0) {
		discard;
	}
	linear2rgb(color.rgb);
	float Lw = getLuminance(color);
	rgb2linear(color.rgb);
	float Ld = ToneMap(Lw);
	color.rgb *= Ld / Lw;
	feiColorOutput = color;
}

void renderFinal()
{
	vec4 color = v_color;
	color *= texture2D(feiTex, v_texcoord);
	vec4 emitColor = texture2D(feiEmitTex, v_texcoord);
	rgb2linear(emitColor.rgb);
	color.rgb += emitColor.rgb * feiEmitHaloValue;
	linear2rgb(color.rgb);
	feiColorOutput = color;
}
