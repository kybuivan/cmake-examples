precision mediump float;
uniform samplerCube u_enviroMap;
varying vec4 v_pos;

void main(void)
{
	gl_FragColor = textureCube(u_enviroMap, v_pos.xyz);
}