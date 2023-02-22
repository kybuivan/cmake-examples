precision mediump float;
uniform vec3 u_camerapos;
uniform sampler2D u_texture;

uniform vec3 u_light1;
uniform vec3 u_color1;
varying vec3 v_posW;
varying vec3 v_norm;
varying vec2 v_uv;
void main()
{
vec3 normW = normalize(v_norm);
	vec4 ObjColor = texture2D(u_texture, v_uv);
	vec4 AmbientComponent = vec4(1.0, 1.0, 1.0, 1.0);
	float weight = 0.3;
	vec4 LightDirection = vec4(u_light1 - v_posW, 0.0);
	float disToCam = distance(u_light1, v_posW);
	float att = 1.0 / (disToCam*disToCam);
	vec4 DiffuseComponent = max(dot(vec4(normW, 0.0), LightDirection), 0.0)* vec4(u_color1, 1.0) * att;
	vec4 reflectVector = normalize(reflect(LightDirection, vec4(normW, 0.0)));
	vec3 toEye = normalize(u_camerapos - v_posW);
	vec4 SpecularComponent = pow(max(dot(reflectVector,vec4(-toEye, 1.0)),0.0),20.0)* vec4(u_color1, 1.0);
	gl_FragColor = vec4(((AmbientComponent * weight + DiffuseComponent * (1.0 - weight)) * ObjColor + SpecularComponent).xyz, ObjColor.w);
}
