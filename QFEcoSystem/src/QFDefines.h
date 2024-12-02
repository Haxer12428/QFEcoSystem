#pragma once

#ifndef NDEBUG
	#define _qfDebugBuild
#endif // !NDEBUG

/* 
	QF Debug Levels 0 - 3: 
		0: Every shit is here, unreadable console 
		1: More important shit is here like, togging a switch 
		2: Even more important stuff, for example: constructor || destructor calls
		3: Most important shit, for example suggestions
*/
#define _qfDebugLevelAll 0
#define _qfDebugLevelRegular 1
#define _qfDebugLevelImportant 2
#define _qfDebugLevelCritical 3

#ifndef _qfDebugLevel
		#define _qfDebugLevel _qfDebugLevelCritical
#endif // !_qfDebugLevel

/* Usage: prints self and upper levels */
#ifdef _qfExample
	#if _qfDebugLevel <= _qfDebugLevelRegular
		//log something 
	#endif 
#endif 

/* Fancy string */
#define _qfEmptyString ""