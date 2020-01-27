/*
  VerLib
  Copyright © 2019 Daniel Strayker Nowak
*/

#ifndef _VERLIB_
#define _VERLIB_

#include <stdbool.h>

// Version data:
struct Version
{
	int Major;
	int Minor;
	int Release;
	int Build;
};
typedef struct Version Version;

// Set version for app, use on app's start:

extern void SetVersionString(char *version);
extern void SetVersionMajor(int value);
extern void SetVersionMinor(int value);
extern void SetVersionRelease(int value);
extern void SetVersionBuild(int value);

// Get version number:

extern int GetVersionFull();
extern int GetVersionMajor();
extern int GetVersionMinor();
extern int GetVersionRelease();
extern int GetVersionBuild();

// Increment or decrement version, for development help:

extern void IncrementMajor();
extern void IncrementMinor();
extern void IncrementRelease();
extern void IncrementBuild();
extern void DecrementMajor();
extern void DecrementMinor();
extern void DecrementRelease();
extern void DecrementBuild();

// Write version to console or return version's string representation:

extern void ConsoleLogVersion();
extern char *LogVersionString();

// Additional functions:
extern bool CompareVersions(Version x, Version y); // checks, if two given versions are equal,

#endif
