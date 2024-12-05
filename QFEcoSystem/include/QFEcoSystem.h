#pragma once
#include <nlohmann/json.hpp>

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
/* qfJson
	Custom json wrapper in case of implementing something into it later on (extension)  
*/
#include "../src/QFJson.h"
/* qfEncryption 
	Simple encryption class, trying to make is as fast as possible
*/
#include "../src/QFEncryption.h"
/* qfString 
	Custom std::string wrapper in case of implementhing something later on 
*/
#include "../src/QFString.h"
/* qfRect
	Simple Rect class 
*/
#include "../src/QFRect.h"
/* QFCall
	From callbacks to eventsystems 
*/
#include "../src/QFCall.h"
/* QFAnim 
	Simple Animation class 
*/
#include "../src/QFAnim.h"