// Flat Color Shader

#type vertex
#version 410 core

layout(location = 0) in vec3 array_position_;

uniform mat4 view_projection_;
uniform mat4 transform_;

void main()
{
	gl_Position = view_projection_ * transform_ * vec4(array_position_, 1.0);
}

#type fragment
#version 410 core

layout(location = 0) out vec4 color;

uniform vec4 uniform_color;

void main()
{
	color = uniform_color;
}
