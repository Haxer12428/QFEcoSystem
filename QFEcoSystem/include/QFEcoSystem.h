#pragma once

/* General purposes ecosystem
	Utilites for qf
*/

/* QF Filesystem:
	Quick way to manage files
*/
#include "../src/QFFileSystem.h"
/* QF assertion: 
	Quick way to do checks that cannot fail!
*/
#include "../src/QFAssert.h"
/* QF Shutdown: 
	Best way to shutdown application on error||crash 
*/
#include "../src/QFShutdown.h"
/* QF Vec2
	Simple vec2 struct based on glm's vec2 for performance 
*/
#include "../src/QFVec2.h"
/* QF Debug 
	Simple yet very efficient for logging 
*/
#include "../src/QFDebug.h"
/* QF Compare
	Compare for example if flag is in a pool (bitwise)
*/
#include "../src/QFCompare.h"
/* QF Transform 
	Transform things, for example std::string to uppercase 
*/
#include "../src/QFTransform.h"
/* QF System
	Window's operations like: Clipboard
*/
#include "../src/QFSystem.h"
/* QF Color 
	Simple color class based on glm::vec4 for performance, its always normalized to 0.0f-1.0f
*/
#include "../src/QFColor.h"
