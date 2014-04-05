Tutorial
========

Welcome to the Agreon Library Tutorial. I hope you set up the Library successfull.<br>
Let's start!<br>

The first programm will just create a screen and close it.<br>
The first thing to do is to import the Library and the cGraphics Manager and create a main function.
´´´
#include "AgreonLibrary/Agreon.h"
#include "AgreonLibrary/cGraphics.h"

int main( int argc, char* args[] )
{
	return 0;
}

´´´
Now we can create a Graphics Manager. The whole Library is seperated in Managers, e.g. for Graphics, Sound or Input<br>

´´´
cGraphics* Graphics = new cGraphcis();
´´´

With this manager, we can open a window and draw textures or text.<br>
We will use the init function.<br>

´´´
// Syntax: init( screen_width, screen_height, window_title, window_icon );
Graphics->init( 800, 600, "Test Program", NULL );
´´´
