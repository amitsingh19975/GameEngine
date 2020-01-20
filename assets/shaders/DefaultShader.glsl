
#type vertex
attribute vec3 a_Pos;
// varying vec4 v_Col;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main(){
    gl_Position = u_ViewProjection * u_Transform* vec4(a_Pos ,1.0);
}

#type fragment
uniform vec4 u_Color;
void main(){
    gl_FragColor = u_Color;
}