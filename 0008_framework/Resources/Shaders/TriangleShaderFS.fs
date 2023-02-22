precision mediump float;
uniform sampler2D u_texture;
uniform vec3 u_camerapos;
varying vec2 v_uv;
varying vec3 v_posL;
void main()
{
	//float DisToCamrema = distance(u_camerapos, v_posL);
	//vec4 FogColor = vec4(1.0, 1.0, 1.0, 0.0);
	//float FogStart = 1.0;
	//float FogEnd = 10.0;
	//float FogLenght = FogEnd - FogStart;
	//float LerpValue = clamp((FogEnd - DisToCamrema)/FogLenght, 0.0, 1.0);

	vec4 TexelColor = texture2D(u_texture,v_uv);
	gl_FragColor = TexelColor;
	//gl_FragColor = mix(FogColor, TexelColor, LerpValue);
	//gl_FragColor.a = 1.0;
}
