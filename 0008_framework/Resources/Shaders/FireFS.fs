precision mediump float;
uniform sampler2D u_texture;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform float u_time;
varying vec2 v_uv;

void main()
{
	vec2 disp = texture2D(u_texture1, vec2(v_uv.x, v_uv.y + u_time)).rg;
	float dMax = 0.2;
	vec2 offset = (2.0 * disp - 1.0) * dMax;
	vec2 Tex_coords_displaced = v_uv + offset;
	vec4 fire_color = texture2D (u_texture, Tex_coords_displaced);
	vec4 AlphaValue = texture2D(u_texture2, v_uv);
	gl_FragColor = fire_color * (1.0, 1.0, 1.0, AlphaValue.r);
}
