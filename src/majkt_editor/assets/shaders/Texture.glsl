// Basic Texture Shader

#type vertex
#version 410 core

layout(location = 0) in vec3 array_position_;
layout(location = 1) in vec4 array_color_;
layout(location = 2) in vec2 array_texture_coord_;
layout(location = 3) in float array_texture_index_;
layout(location = 4) in float array_tiling_factor_;

uniform mat4 view_projection_;
uniform mat4 transform_;

out vec4 view_color_;
out vec2 view_texture_coord_;
out float view_texture_index_;
out float view_tiling_factor_;

void main()
{
	view_color_ = array_color_;
	view_texture_coord_ = array_texture_coord_;
	view_texture_index_ = array_texture_index_;
	view_tiling_factor_ = array_tiling_factor_;
	gl_Position = view_projection_ * vec4(array_position_, 1.0);
}

#type fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec4 view_color_;
in vec2 view_texture_coord_;
in float view_texture_index_;
in float view_tiling_factor_;

uniform sampler2D uniform_textures_[16];

void main()
{
	vec4 texture_val_;
	int texture_index_ = int(view_texture_index_);

	switch (texture_index_) {
        case 0:  texture_val_ = texture(uniform_textures_[0],  view_texture_coord_ * view_tiling_factor_); break;
        case 1:  texture_val_ = texture(uniform_textures_[1],  view_texture_coord_ * view_tiling_factor_); break;
        case 2:  texture_val_ = texture(uniform_textures_[2],  view_texture_coord_ * view_tiling_factor_); break;
        case 3:  texture_val_ = texture(uniform_textures_[3],  view_texture_coord_ * view_tiling_factor_); break;
        case 4:  texture_val_ = texture(uniform_textures_[4],  view_texture_coord_ * view_tiling_factor_); break;
        case 5:  texture_val_ = texture(uniform_textures_[5],  view_texture_coord_ * view_tiling_factor_); break;
        case 6:  texture_val_ = texture(uniform_textures_[6],  view_texture_coord_ * view_tiling_factor_); break;
        case 7:  texture_val_ = texture(uniform_textures_[7],  view_texture_coord_ * view_tiling_factor_); break;
        case 8:  texture_val_ = texture(uniform_textures_[8],  view_texture_coord_ * view_tiling_factor_); break;
        case 9:  texture_val_ = texture(uniform_textures_[9],  view_texture_coord_ * view_tiling_factor_); break;
        case 10: texture_val_ = texture(uniform_textures_[10], view_texture_coord_ * view_tiling_factor_); break;
        case 11: texture_val_ = texture(uniform_textures_[11], view_texture_coord_ * view_tiling_factor_); break;
        case 12: texture_val_ = texture(uniform_textures_[12], view_texture_coord_ * view_tiling_factor_); break;
        case 13: texture_val_ = texture(uniform_textures_[13], view_texture_coord_ * view_tiling_factor_); break;
        case 14: texture_val_ = texture(uniform_textures_[14], view_texture_coord_ * view_tiling_factor_); break;
        case 15: texture_val_ = texture(uniform_textures_[15], view_texture_coord_ * view_tiling_factor_); break;
	}

	color = texture_val_ * view_color_;
}
