precision mediump float;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform vec3	u_camerapos;

varying vec3 v_posL;
varying vec2 v_uv;

void main()
{
	//float DisToCamrema = distance(u_camerapos, v_posL);
	//vec4 FogColor = vec4(1.0, 1.0, 1.0, 0.0);
	//float FogStart = 1.0;
	//float FogEnd = 10.0;
	//float FogLenght = FogEnd - FogStart;
	//float LerpValue = clamp((FogEnd - DisToCamrema)/FogLenght, 0.0, 1.0);

	vec4 ColorTex1 = texture2D(u_texture0,20.0*v_uv);
	vec4 ColorTex2 = texture2D(u_texture1,20.0*v_uv);
	vec4 ColorTex3 = texture2D(u_texture2,20.0*v_uv);
	vec4 Blendmap = texture2D(u_texture3,v_uv);
	vec4 TexelColor = (Blendmap.g * ColorTex1 + Blendmap.r * ColorTex2 + Blendmap.b * ColorTex3) / (Blendmap.b + Blendmap.r + Blendmap.g);
	gl_FragColor = TexelColor;
	//gl_FragColor = mix(FogColor, TexelColor, LerpValue);
	//gl_FragColor.a = 1.0;
}