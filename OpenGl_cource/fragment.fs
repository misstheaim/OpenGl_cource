#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float trans;
  
void main()
{
    FragColor = mix(texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), texture(texture1, TexCoord), 0.8);//texture(texture2, TexCoord);// * vec4(ourColor, 1.0);
     
}