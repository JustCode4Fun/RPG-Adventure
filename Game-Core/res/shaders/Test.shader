#shader vertex
#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec4 col;
layout(location = 3) in float tid;

uniform mat4 PVM;

uniform float time = 0;

out VERTEX_DATA{
	vec2 pos;
	vec2 uv;
	vec4 col;
	float tid;
} vertex;

void main()
{
	vertex.pos = pos;
	vertex.uv = uv;
	vertex.col = col;
	vertex.tid = tid;
	gl_Position = PVM*vec4(pos, 0.0f, 1.0f);

}
#shader fragment
#version 330 core
out vec4 FragColor;

uniform sampler2D tex[32];
uniform float time = 0;

in VERTEX_DATA{
	vec2 pos;
	vec2 uv;
	vec4 col;
	float tid;
} vertex;

void main()
{
	//int(vertex.tid - 0.5f)
	vec4 texColor = vec4(1.0f);
	if (vertex.tid > 0)
		texColor = texture(tex[int(vertex.tid - 0.5f)], vertex.uv);
	FragColor = texColor *vertex.col;
}