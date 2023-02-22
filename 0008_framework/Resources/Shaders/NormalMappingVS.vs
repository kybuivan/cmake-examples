attribute vec3 a_posL;
attribute vec3 a_normL;
attribute vec3 a_tangentL;
attribute vec3 a_bitangentL;
attribute vec2 a_uv;
uniform mat4 u_mvpMatrix;
uniform mat4 u_wMatrix;

varying vec3 v_tangentW;
varying vec3 v_bitangentW;
varying vec3 v_posW;
varying vec3 v_norm;
varying vec2 v_uv;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_mvpMatrix*posL;
	v_norm = vec3(u_wMatrix*vec4(a_normL,0.0));
	v_tangentW = normalize((u_wMatrix * vec4(a_tangentL, 0.0)).xyz);
    v_bitangentW = normalize((u_wMatrix * vec4(a_bitangentL, 0.0)).xyz);
	v_uv = a_uv;
	v_posW = vec3(u_wMatrix * posL);
}