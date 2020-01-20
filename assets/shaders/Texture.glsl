#type vertex
attribute vec3 a_Pos;
attribute vec2 a_TextCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

varying vec2 v_TextCoord;
void main(){
    v_TextCoord = a_TextCoord;
    gl_Position = u_ViewProjection * u_Transform* vec4(a_Pos ,1.0);
}

#type fragment
varying vec2 v_TextCoord;
uniform sampler2D u_Texture;
void main(){
    gl_FragColor = texture2D(u_Texture,v_TextCoord);
}
