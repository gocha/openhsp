#if defined(OPENGL_ES) || defined(GL_ES)
#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif
#endif

///////////////////////////////////////////////////////////
// Uniforms
uniform sampler2D u_diffuseTexture;
uniform float u_length;

///////////////////////////////////////////////////////////
// Varyings
varying vec2 v_texCoord;
varying vec4 v_color;

void main()
{
    vec4 sum = vec4(0.0);
 
   // blur in y (vertical) take nine samples, with the distance u_length between them
   sum += texture2D(u_diffuseTexture, vec2(v_texCoord.x - 4.0 * u_length, v_texCoord.y)) * 0.05;
   sum += texture2D(u_diffuseTexture, vec2(v_texCoord.x - 3.0 * u_length, v_texCoord.y)) * 0.09;
   sum += texture2D(u_diffuseTexture, vec2(v_texCoord.x - 2.0 * u_length, v_texCoord.y)) * 0.12;
   sum += texture2D(u_diffuseTexture, vec2(v_texCoord.x -       u_length, v_texCoord.y)) * 0.15;
   sum += texture2D(u_diffuseTexture, vec2(v_texCoord.x, v_texCoord.y)) * 0.16;
   sum += texture2D(u_diffuseTexture, vec2(v_texCoord.x +       u_length, v_texCoord.y)) * 0.15;
   sum += texture2D(u_diffuseTexture, vec2(v_texCoord.x + 2.0 * u_length, v_texCoord.y)) * 0.12;
   sum += texture2D(u_diffuseTexture, vec2(v_texCoord.x + 3.0 * u_length, v_texCoord.y)) * 0.09;
   sum += texture2D(u_diffuseTexture, vec2(v_texCoord.x + 4.0 * u_length, v_texCoord.y)) * 0.05;
 
   gl_FragColor = sum;
}

