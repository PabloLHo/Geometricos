#version 450

layout (location = 0) in vec3 vPosition;
layout (location = 5) in vec3 vOffset;
layout (location = 6) in vec3 vColor;

uniform vec3 lineColor;
uniform mat4 mModelViewProj;	
uniform vec3 globalScale;

out vec3 color;

subroutine vec3 instanceType();
subroutine uniform instanceType instanceUniform;


// ------------------------------------
// ---------- MULTI_INSTANCE ----------
// ------------------------------------

subroutine(instanceType)
vec3 multiInstanceUniform()
{
	color = vColor;
	return vPosition * globalScale + vOffset;
}

subroutine(instanceType)
vec3 singleInstanceUniform()
{
	color = lineColor;
	return vPosition;
}


void main() 
{
	gl_Position = mModelViewProj * vec4(instanceUniform(), 1.0f);
}