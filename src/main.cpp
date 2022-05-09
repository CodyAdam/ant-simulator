#include <Canvas.h>

/// <summary>
/// The main program.
/// </summary>
/// <param name="argc">The number of arguments.</param>
/// <param name="argv">The arguments.</param>
/// <returns></returns>
int main(int /*argc*/, char ** /*argv*/)
{
	Canvas *canvas = new Canvas();
	canvas->loop();
	return 0;
}
