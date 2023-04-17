// Basic Texture Shader

#type vertex
#version 410 core

layout(location = 0) in vec3 array_position_;
layout(location = 1) in vec4 array_color_;
layout(location = 2) in vec2 texture_coord_;

uniform mat4 view_projection_;
uniform mat4 transform_;

out vec4 view_color_;
out vec2 view_texture_coord_;

void main()
{
	view_color_ = array_color_;
	view_texture_coord_ = texture_coord_;
	gl_Position = view_projection_ * vec4(array_position_, 1.0);
}

#type fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec4 view_color_;
in vec2 view_texture_coord_;

uniform vec4 uniform_color_;
uniform float uniform_tiling_factor_;
uniform sampler2D texture_;

void main()
{
	color = view_color_;
}
