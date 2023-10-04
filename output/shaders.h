const char *wavy_vert_src = "#version 330 core layout (location = 0) in vec3 a_pos; out vec3 color; uniform mat4 u_xform; void main() {   gl_Position = u_xform * vec4(a_pos, 1.0); } ";
const char *wavy_frag_src = "#version 330 core out vec4 frag_color; void main() {   frag_color = vec4(color, 1.0); } ";

const char *fog_vert_src = "#version 330 core layout (location = 0) in vec3 a_pos; out vec3 color; uniform mat4 u_xform; void main() {   gl_Position = u_xform * vec4(a_pos, 1.0); } ";
const char *fog_frag_src = "#version 330 core out vec4 frag_color; void main() {   frag_color = vec4(color, 1.0); } ";

const char *generic_vert_src = "#version 330 core layout (location = 0) in vec3 a_pos; out vec3 color; uniform mat4 u_xform; void main() {   gl_Position = u_xform * vec4(a_pos, 1.0); } ";
const char *generic_frag_src = "#version 330 core out vec4 frag_color; void main() {   frag_color = vec4(color, 1.0); } ";

const char *fire_vert_src = "#version 410 core layout (location = 0) in vec3 a_pos; layout (location = 1) in vec3 a_color; out vec3 color; uniform mat3 u_xform; void main() {   gl_Position = vec4(a_pos * u_xform, 1.0);   color = a_color; } ";
const char *fire_frag_src = "#version 410 core in vec3 color; out vec4 frag_color; void main() {   frag_color = vec4(color, 1.0); } ";

const char *water_vert_src = "#version 330 core layout (location = 0) in vec3 a_pos; out vec3 color; uniform mat4 u_xform; void main() {   gl_Position = u_xform * vec4(a_pos, 1.0); } ";
const char *water_frag_src = "#version 330 core out vec4 frag_color; void main() {   frag_color = vec4(color, 1.0); } ";

const char *lighting_vert_src = "#version 330 core layout (location = 0) in vec3 a_pos; out vec3 color; uniform mat4 u_xform; void main() {   gl_Position = u_xform * vec4(a_pos, 1.0); } ";
const char *lighting_frag_src = "#version 330 core out vec4 frag_color; void main() {   frag_color = vec4(color, 1.0); } ";

const char *sky_vert_src = "#version 330 core layout (location = 0) in vec3 a_pos; out vec3 color; uniform mat4 u_xform; void main() {   gl_Position = u_xform * vec4(a_pos, 1.0); } ";
const char *sky_frag_src = "#version 330 core out vec4 frag_color; void main() {   frag_color = vec4(color, 1.0); } ";

const char *explosion_vert_src = "#version 330 core layout (location = 0) in vec3 a_pos; out vec3 color; uniform mat4 u_xform; void main() {   gl_Position = u_xform * vec4(a_pos, 1.0); } ";
const char *explosion_frag_src = "#version 330 core out vec4 frag_color; void main() {   frag_color = vec4(color, 1.0); } ";

const char *reflection_vert_src = "#version 330 core layout (location = 0) in vec3 a_pos; out vec3 color; uniform mat4 u_xform; void main() {   gl_Position = u_xform * vec4(a_pos, 1.0); } ";
const char *reflection_frag_src = "#version 330 core out vec4 frag_color; void main() {   frag_color = vec4(color, 1.0); } ";

const char *smoke_vert_src = "#version 330 core layout (location = 0) in vec3 a_pos; out vec3 color; uniform mat4 u_xform; void main() {   gl_Position = u_xform * vec4(a_pos, 1.0); } ";
const char *smoke_frag_src = "#version 330 core out vec4 frag_color; void main() {   frag_color = vec4(color, 1.0); } ";

