precision highp float;
float rand(vec2 uv){
    return fract(sin(dot(uv, vec2(0.5161573, 0.4346789)))
    * 13571.5977913417);
}

vec4 galaxy(){
	vec4 color = texture2D( TEXTURE_0, uv );

	/********** Galaxy Effect **********/
	vec3 view_norm = normalize(eyeDir.xyz);
	float view_dist = eyeDir.w;

	// calculate spherical coordinates
	vec2 view_uv = vec2(
		atan(-view_norm.z, view_norm.x) * INV_PI * 0.5 + 0.5,
		0.5 - view_norm.y * 0.5
	) * uv_scale;
	view_uv = fract(view_uv * max(floor(view_dist * 0.3), 2.0) + TIME * UV_FLOW);

	/********** Fresnel Effect **********/
	float noise = texture2D(
		TEXTURE_2,
		fract(uv * NOISE_SCALE + TIME * FRESNEL_FLOW)
	).r;
	vec3 fresColor = fresnel_color * fresnel_ex(normalize(worldSpaceNormal), -view_norm, FRESNEL_OFFSET, 1.0, 2.0);
	fresColor = smoothstep(0.05, 1.0, fresColor) * noise;

	/********** Gradient Color Effect **********/
	vec3 galaxyColor = texture2D(
		TEXTURE_1,
		view_uv
	).rgb;
	vec3 gradientColor = gradient_color + delta_color_horizontal * abs(view_uv.x * 2.0 - 1.0) + delta_color_vertical * (view_norm.y * 0.5 + 0.5);
	float gradientStep = step(GRADIENT_MODE, 0.5);
	// MUL mode or ADD mode
	galaxyColor = gradientStep * (galaxyColor * gradientColor) + (1.0 - gradientStep) * (galaxyColor + gradientColor);

	/********** Star Effect **********/
	vec2 star_uv = floor(floor(view_uv * vec2(1024.0, 512.0) * uv_scale) / STAR_SIZE);
    vec2 move_dir = normalize(vec2(rand(star_uv * 0.4987368153), rand(-star_uv * 0.31168489)) - 0.5);
    star_uv = fract((star_uv + TIME * move_dir) * 2.0 / 512.0);
	float star_val = texture2D(TEXTURE_2, star_uv).g;
    star_val = smoothstep(0.8 - 0.2 * STAR_DENSITY, 0.8, star_val);
	
	vec3 starColor = (gradientStep * star_val * gradientColor + (1.0 - gradientStep) * (star_val + gradientColor));

	// use black hole to cover the artifect caused by spherical texturing
	// when abs(view_norm.y) is nearly 1.0
	view_norm.xz *= view_dist * 2.4; // black hole should scale with camera distance
	mediump float yLerp = normalize(view_norm).y;
	vec3 shaderColor = mix(galaxyColor + fresColor + starColor, vec3(0.05), smoothstep(0.5, 1.0, yLerp * yLerp));

	/********** Mixture **********/
	float colorStep = step(color.a, 0.5);
	color.rgb = (1.0 - colorStep) * color.rgb + colorStep * shaderColor;
    return vec4(color.rgb, 1.0);
}
