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

#define _qfDebugLevel _qfDebugLevelImportant

/* WARNING: prints self and upper levels -> Should not use this anymore!
	If u see something like this in the code change this to _qfLogIf -> newer, clearer version of this
*/
#ifdef _qfDontUseThis_IfUSeeThisChangeItToNewerVersionDescribedBelowAs_qfLogIf
	#if _qfDebugLevel <= _qfDebugLevelRegular
		// log something using the old method (deprecated)
	#endif 
#endif 

/* Thing from comment above is obselete, this is new way of logging with level  */
#ifdef _qfDebugBuild
	#define _qfLogIf(level, action) \
			do { \
					if (_qfDebugLevel <= (level)) { action; } \
			} while (false)
#else 
		#define _qfLogIf(level, action) ((void)(level), void(0))
#endif

/* Fancy string */
#define _qfEmptyString ""