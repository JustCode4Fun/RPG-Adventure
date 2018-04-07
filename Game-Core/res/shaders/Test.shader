#shader vertex
#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 col;

uniform mat4 PVM;

uniform float time = 0;

out vec4 o_color;

void main()
{
	o_color = col;
	gl_Position = PVM*vec4(pos.xy+vec2(sin(time/2.0f),cos(time*2.0f)),0.0f,1.0f);
}
#shader fragment
#version 330 core
out vec4 FragColor;

uniform float time = 0;

in vec4 o_color;

void main()
{
	FragColor = vec4(o_color.xzy, sin(time)*.5f+0.5f);
}