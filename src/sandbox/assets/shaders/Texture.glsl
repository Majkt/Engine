// Basic Texture Shader

#type vertex
#version 410 core

layout(location = 0) in vec3 array_position_;
layout(location = 1) in vec2 texture_coord_;

uniform mat4 view_projection_;
uniform mat4 transform_;

out vec2 view_texture_coord_;

void main()
{
	view_texture_coord_ = texture_coord_;
	gl_Position = view_projection_ * transform_ * vec4(array_position_, 1.0);
}

#type fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec2 view_texture_coord_;

uniform vec4 uniform_color;
uniform sampler2D texture_;

void main()
{
	color = texture(texture_, view_texture_coord_ * 10.0) * uniform_color;
}
