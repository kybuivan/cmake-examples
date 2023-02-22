attribute vec3 a_posL;
attribute vec3 a_normL;
uniform mat4 u_mvpMatrix;
uniform mat4 u_wMatrix;

varying vec3 v_posW;
varying vec3 v_normW;
void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_mvpMatrix*posL;
	v_normW = vec3(u_wMatrix * vec4(a_normL, 0.0));
	v_posW = vec3(u_wMatrix * posL);
}