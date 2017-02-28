
/*
	Draw Color
	By Dan Buckstein
	Fragment shader that displays color received from previous piipeline stage.
	
	Modified by: ______________________________________________________________
*/

// version (same idea)
#version 410

in vec4 passColor;


layout(location = 0) out vec4 color;

// shader entry point: function executes once per-fragment
void main()
{
	color = passColor;
}