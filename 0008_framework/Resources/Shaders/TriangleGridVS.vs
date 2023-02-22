attribute vec3 a_posL;
attribute vec2 a_uv;
uniform mat4 u_mvpMatrix;
varying vec3 v_posL;
varying vec2 v_uv;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_mvpMatrix*posL;
	v_uv = a_uv;
	v_posL = a_posL;
}