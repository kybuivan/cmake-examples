precision mediump float;
uniform samplerCube u_texture;
varying vec4 v_pos;

void main(void)
{
	gl_FragColor = textureCube(u_texture, v_pos.xyz);
}