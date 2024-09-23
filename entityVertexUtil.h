#ifndef ENTITY_VERTEX_UTIL_H
#define ENTITY_VERTEX_UTIL_H

// To use centroid sampling we need to have version 300 es shaders, which requires changing:
// attribute to in
// varying to out when in vertex shaders or in when in fragment shaders
// defining an out vec4 FragColor and replacing uses of gl_FragColor with FragColor
// texture2D to texture
#if __VERSION__ >= 300
#define attribute in
#define varying out

#ifdef MSAA_FRAMEBUFFER_ENABLED
#define _centroid centroid
#else
#define _centroid
#endif

_centroid out vec2 uv;

#else

varying vec2 uv;

#endif


#ifndef _UNIFORM_WORLD_CONSTANTS_H
#define _UNIFORM_WORLD_CONSTANTS_H

#ifndef _UNIFORM_MACRO_H
#define _UNIFORM_MACRO_H

#ifdef MCPE_PLATFORM_NX
// Unfortunately this macro does not work on old Amazon platforms #define BEGIN_UNIFORM_BLOCK(x) uniform x {
#define END_UNIFORM_BLOCK };
#define UNIFORM 
#else
// Unfortunately this macro does not work on old Amazon platforms #define BEGIN_UNIFORM_BLOCK(x) 
#define END_UNIFORM_BLOCK
#define UNIFORM uniform 
#endif

#if __VERSION__ >= 420
#define LAYOUT_BINDING(x) layout(binding = x)
#else
#define LAYOUT_BINDING(x) 
#endif

#endif


#ifdef MCPE_PLATFORM_NX
layout(binding = 1) uniform WorldConstants {
#endif
// BEGIN_UNIFORM_BLOCK(WorldConstants) - unfortunately this macro does not work on old Amazon platforms so using above 3 lines instead
UNIFORM MAT4 WORLDVIEWPROJ;
UNIFORM MAT4 WORLD;
UNIFORM MAT4 WORLDVIEW;
UNIFORM MAT4 PROJ;
END_UNIFORM_BLOCK

#endif

#ifndef _UNIFORM_ENTITY_CONSTANTS_H
#define _UNIFORM_ENTITY_CONSTANTS_H

#ifndef _UNIFORM_MACRO_H
#define _UNIFORM_MACRO_H

#ifdef MCPE_PLATFORM_NX
// Unfortunately this macro does not work on old Amazon platforms #define BEGIN_UNIFORM_BLOCK(x) uniform x {
#define END_UNIFORM_BLOCK };
#define UNIFORM 
#else
// Unfortunately this macro does not work on old Amazon platforms #define BEGIN_UNIFORM_BLOCK(x) 
#define END_UNIFORM_BLOCK
#define UNIFORM uniform 
#endif

#if __VERSION__ >= 420
#define LAYOUT_BINDING(x) layout(binding = x)
#else
#define LAYOUT_BINDING(x) 
#endif

#endif


#ifdef MCPE_PLATFORM_NX
uniform ActorConstants {
#endif
// BEGIN_UNIFORM_BLOCK(ActorConstants) - unfortunately this macro does not work on old Amazon platforms so using above 3 lines instead
UNIFORM vec4 OVERLAY_COLOR;
UNIFORM vec4 TILE_LIGHT_COLOR;
UNIFORM vec4 CHANGE_COLOR;
UNIFORM vec4 GLINT_COLOR;
UNIFORM vec4 UV_ANIM;
UNIFORM vec2 UV_OFFSET;
UNIFORM vec2 UV_ROTATION;
UNIFORM vec2 GLINT_UV_SCALE;
UNIFORM vec4 MULTIPLICATIVE_TINT_CHANGE_COLOR;
END_UNIFORM_BLOCK

#endif

#ifndef _UNIFORM_PER_FRAME_CONSTANTS_H
#define _UNIFORM_PER_FRAME_CONSTANTS_H

#ifndef _UNIFORM_MACRO_H
#define _UNIFORM_MACRO_H

#ifdef MCPE_PLATFORM_NX
// Unfortunately this macro does not work on old Amazon platforms #define BEGIN_UNIFORM_BLOCK(x) uniform x {
#define END_UNIFORM_BLOCK };
#define UNIFORM 
#else
// Unfortunately this macro does not work on old Amazon platforms #define BEGIN_UNIFORM_BLOCK(x) 
#define END_UNIFORM_BLOCK
#define UNIFORM uniform 
#endif

#if __VERSION__ >= 420
#define LAYOUT_BINDING(x) layout(binding = x)
#else
#define LAYOUT_BINDING(x) 
#endif

#endif


#ifdef MCPE_PLATFORM_NX
layout(binding = 2) uniform PerFrameConstants {
#endif
// BEGIN_UNIFORM_BLOCK(PerFrameConstants) - unfortunately this macro does not work on old Amazon platforms so using above 3 lines instead
UNIFORM vec3 VIEW_POS;
#ifdef MCPE_NETEASE
// TIME will loop from [0, 210]
// make sure your shader handles the case when it transitions from 210 to 0
#endif
UNIFORM float TIME;
#ifdef MCPE_NETEASE
UNIFORM vec4 BLEND_COLOR;
UNIFORM vec4 USER_FOR_COLOR_NEAR;
UNIFORM vec4 USER_FOR_COLOR_FAR;
#endif
UNIFORM vec4 FOG_COLOR;
UNIFORM vec2 FOG_CONTROL;
UNIFORM float RENDER_DISTANCE;
UNIFORM float FAR_CHUNKS_DISTANCE;
UNIFORM float OCCLUSION_HEIGHT_OFFSET;
END_UNIFORM_BLOCK

#endif

#ifdef USE_SKINNING
#ifndef _UNIFORM_ANIMATION_CONSTANTS_H
#define _UNIFORM_ANIMATION_CONSTANTS_H

#ifndef _UNIFORM_MACRO_H
#define _UNIFORM_MACRO_H

#ifdef MCPE_PLATFORM_NX
// Unfortunately this macro does not work on old Amazon platforms #define BEGIN_UNIFORM_BLOCK(x) uniform x {
#define END_UNIFORM_BLOCK };
#define UNIFORM 
#else
// Unfortunately this macro does not work on old Amazon platforms #define BEGIN_UNIFORM_BLOCK(x) 
#define END_UNIFORM_BLOCK
#define UNIFORM uniform 
#endif

#if __VERSION__ >= 420
#define LAYOUT_BINDING(x) layout(binding = x)
#else
#define LAYOUT_BINDING(x) 
#endif

#endif


#ifdef MCPE_PLATFORM_NX
layout(binding = 4) uniform AnimationConstants {
#endif
// BEGIN_UNIFORM_BLOCK(AnimationConstants) - unfortunately this macro does not work on old Amazon platforms so using above 3 lines instead
#if defined(LARGE_VERTEX_SHADER_UNIFORMS)
UNIFORM MAT4 BONES[8];
#else
UNIFORM MAT4 BONE;
#endif
END_UNIFORM_BLOCK


UNIFORM mat3x4 BONES_70[70];

mat4 mat3x4ToMat4(mat3x4 boneMat3x4){
		mat4 boneMat4x4;
		
		boneMat4x4[0] = boneMat3x4[0];
		boneMat4x4[1] = boneMat3x4[1];
		boneMat4x4[2] = boneMat3x4[2];
		boneMat4x4[3] = vec4(0, 0, 0, 1);
		
		return boneMat4x4;
}

mat4 GetBoneMatForNetease(int boneId){
    return transpose(mat3x4ToMat4(BONES_70[boneId]));
}

#ifdef USE_INSTANCE
UNIFORM mat4x3 INSTANCE_WORLDMAT_50[50];

mat4 mat4x3ToMat4(mat4x3 worldMat4x3){
		mat4 worldMat4x4;
		
		worldMat4x4[0] = vec4(worldMat4x3[0], 0);
		worldMat4x4[1] = vec4(worldMat4x3[1], 0);
		worldMat4x4[2] = vec4(worldMat4x3[2], 0);
		worldMat4x4[3] = vec4(worldMat4x3[3], 1);
		
		return worldMat4x4;
}

mat4 GetInstanceWorldMatForNetease(){
	return mat4x3ToMat4(INSTANCE_WORLDMAT_50[gl_InstanceID]);
}
#endif

#endif

#endif
#line 11

/**************** Preset Variables Begin ****************/
attribute mediump vec4 POSITION;
attribute vec2 TEXCOORD_0;
attribute vec4 NORMAL;
#if defined(USE_SKINNING)
	#ifdef MCPE_PLATFORM_NX
		attribute uint BONEID_0;
	#else
		attribute float BONEID_0;
	#endif
#endif

#ifdef RNGL_LIGHT
uniform vec4 HIDE_COLOR;
#endif

#ifdef COLOR_BASED
	attribute vec4 COLOR;
	varying vec4 vertColor;
#endif

#ifdef USE_OVERLAY
	// When drawing horses on specific android devices, overlay color ends up being garbage data.
	// Changing overlay color to high precision appears to fix the issue on devices tested
	varying highp vec4 overlayColor;
#endif

#ifdef TINTED_ALPHA_TEST
	varying float alphaTestMultiplier;
#endif

#ifdef USE_UV_FRAME_ANIM
uniform vec4 UV_FRAME_ANIM_PARAM;	//(gridRowInverse, gridColInverse, gridCol, curFrame)

vec2 calculateFrameAnimUV(vec2 uv, float gridRowInverse, float gridColInverse, float gridCol, float curFrame) {
	float curRow = floor(curFrame * gridColInverse + 0.1);
	float curCol = curFrame - curRow * gridCol;	
	return (uv + vec2(curCol, curRow)) * vec2(gridColInverse, gridRowInverse);
}
#endif

#ifdef GLINT
varying vec2 layer1UV;
varying vec2 layer2UV;
varying vec4 tileLightColor;
varying vec4 glintColor;
#endif
/**************** Preset Variables End ****************/

vec2 _calculateLayerUV(float offset, float rotation) {
	vec2 uv = TEXCOORD_0;
	uv -= 0.5;
	float rsin = sin(rotation);
	float rcos = cos(rotation);
	uv = mat2(rcos, -rsin, rsin, rcos) * uv;
	uv.x += offset;
	uv += 0.5;

	return uv * GLINT_UV_SCALE;
}

const float AMBIENT = 0.45;
const float XFAC = -0.1;
const float ZFAC = 0.1;
float _lightIntensity(vec4 position, vec4 normal) {
#if defined(RNGL_UNLIT) || !defined(FANCY)
	return 1.0;
#else
	vec3 N = normalize( (WORLD * normal).xyz );
	N.y *= TILE_LIGHT_COLOR.w; //TILE_LIGHT_COLOR.w contains the direction of the light

	//take care of double sided polygons on materials without culling
	#ifdef FLIP_BACKFACES
		vec3 viewDir = normalize((WORLD * position).xyz);
		if( dot(N, viewDir) > 0.0 )
			N *= -1.0;
	#endif

	#ifdef RNGL_LIGHT
		vec3 lightDir = normalize(HIDE_COLOR.xyz);  // light dir uses world coords
		float dLight = max(0.0, dot(N, lightDir));  // diffuse in directional light
		return dLight * (1.0-AMBIENT-0.2) + AMBIENT+0.2;  // origin range [0.65, 1.0]
	#else
		float yLight = (1.0+N.y) * 0.5;
		return yLight * (1.0-AMBIENT) + N.x*N.x * XFAC + N.z*N.z * ZFAC + AMBIENT;
	#endif // RNGL_LIGHT
#endif
}


vec4 getLightColor(vec4 entitySpacePosition, vec4 entitySpaceNormal) {
	float L = _lightIntensity(entitySpacePosition, entitySpaceNormal);

#ifdef USE_OVERLAY
	L += OVERLAY_COLOR.a * 0.35;
#endif

	return vec4(TILE_LIGHT_COLOR.xyz * L, 1.0);
}

void getEntitySpacePositionAndNormal(out POS4 entitySpacePosition, out POS4 entitySpaceNormal) {
#ifdef USE_SKINNING
	#ifdef NETEASE_SKINNING
		MAT4 boneMat = GetBoneMatForNetease(int(BONEID_0));
		entitySpacePosition = boneMat * POSITION;
		entitySpaceNormal = boneMat * NORMAL;
	#else
		#if defined(LARGE_VERTEX_SHADER_UNIFORMS)
			entitySpacePosition = BONES[int(BONEID_0)] * POSITION;
			entitySpaceNormal = BONES[int(BONEID_0)] * NORMAL;
		#else
			entitySpacePosition = BONE * POSITION;
			entitySpaceNormal = BONE * NORMAL;
		#endif
	#endif
#else
	entitySpacePosition = POSITION;
	entitySpaceNormal = NORMAL;
#endif
}

void applyUVAnim(inout vec2 uv) {
#ifdef USE_UV_ANIM
	uv = UV_ANIM.xy + (uv * UV_ANIM.zw);
#endif

#ifdef USE_UV_FRAME_ANIM
	uv = calculateFrameAnimUV(uv, UV_FRAME_ANIM_PARAM.x, UV_FRAME_ANIM_PARAM.y, UV_FRAME_ANIM_PARAM.z, UV_FRAME_ANIM_PARAM.w);	
#endif
}

void calculateGlint(){
#ifdef GLINT
	glintColor = GLINT_COLOR;
	layer1UV = _calculateLayerUV(UV_OFFSET.x, UV_ROTATION.x);
	layer2UV = _calculateLayerUV(UV_OFFSET.y, UV_ROTATION.y);
	tileLightColor = TILE_LIGHT_COLOR;
#endif
}

void calculateOverlayColor(){
#ifdef USE_OVERLAY
	overlayColor = OVERLAY_COLOR;
#endif
}

vec4 getFogColor(vec4 pos){
	float fogControl = ((pos.z / RENDER_DISTANCE) - FOG_CONTROL.x) / (FOG_CONTROL.y - FOG_CONTROL.x);
	return vec4(
		FOG_COLOR.rgb,
		clamp(fogControl, 0.0, 1.0)
	);
}

void entityCommonVert() {
#ifdef TINTED_ALPHA_TEST
	alphaTestMultiplier = OVERLAY_COLOR.a;
#endif

#ifdef COLOR_BASED
	vertColor = COLOR;
#endif
}

#endif // ENTITY_VERTEX_UTIL_H
