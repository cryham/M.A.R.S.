uniform sampler2D Texture;
uniform sampler2D BumpMap;

void main(void) {
    vec2 TexCoord = vec2(gl_TexCoord[0]);
    vec2 distort  = vec2(texture2D(BumpMap, TexCoord).rb) - vec2(0.5f, 0.5f);

    gl_FragColor = texture2D(Texture, distort*0.02f +  TexCoord);
}

