uniform float time;
uniform vec2 resolution;

void main() {
	vec2 uv = gl_FragCoord.xy / vec2(1920, 1080);
	
	vec3 col = cos(time - uv.x + vec3(0, 1, 4)) + 0.5;


	gl_FragColor = vec4(col, 1.0);
}
