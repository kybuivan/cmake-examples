precision mediump float;
uniform samplerCube u_enviroMap;
uniform vec3 u_camerapos;

varying vec3 v_posW;
varying vec3 v_normW;
void main()
{
	vec3 toEye = u_camerapos - v_posW;
    vec3 R = reflect(normalize(-toEye), normalize(v_normW));
	gl_FragColor = textureCube(u_enviroMap, R);
}
