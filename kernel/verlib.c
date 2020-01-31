/*
  VerLib
  Copyright © 2019 Daniel Strayker Nowak
*/

#include "klib/verlib.h"
#include "klib/kio.h"
#include "klib/kstdlib.h"
#include "klib/kstring.h"
#include "klib/kmem.h"

// Default version format in VerLib is: "Major.Minor.Release Build",

// Default version in VerLib is "0.0.0 0"
Version ver;

// Additional functions:

// Comapare, if two given versions are equal:
bool CompareVersions(Version x, Version y)
{
	if(x.Major != y.Major) return false;
	else if(x.Minor != y.Minor) return false;
	else if(x.Release != y.Release) return false;
	else if(x.Build != y.Build) return false;
	
	return true;
}

// Count, how many digits is in number:
int CountDigits(int checking)
{
	int len = 0;
	
	for(; checking >= 1; len++)
       checking = checking / 10;
       
    return len;
}

/*
	Major and Minor numbers can't have more than 3 digits,
	Release can't have more than 4 digits
	and Build can't have more than 100 digits!
*/

// Set version data:

// - by string,
void SetVersionString(char *version)
{
	// "version" string data is given in sequence: "Major.Minor.Release.Build\0",
	// Example: 20.11.121.1014\0
	
	char MajorChar[3];
	char MinorChar[3];
	char ReleaseChar[4];
	char BuildChar[100];
	
	int MajorLen = 0;
	int MinorLen = 0;
	int ReleaseLen = 0;
	int BuildLen = 0;
	int i = 0;
	
	for(; version[i] != '.'; i++)
	{
		MajorChar[MajorLen] = version[i];
		MajorLen++;
	}
	
	//printf("i = %i\n", i);
	i++;
	
	for(; version[i] != '.'; i++)
	{
		MinorChar[MinorLen] = version[i];
		MinorLen++;
	}
	
	//printf("i = %i\n", i);
	i++;
	
	for(; version[i] != '.'; i++)
	{
		ReleaseChar[ReleaseLen] = version[i];
		ReleaseLen++;
	}
	
	//printf("i = %i\n", i);
	i++;
	
	for(; version[i] != '\0'; i++)
	{
		BuildChar[BuildLen] = version[i];
		BuildLen++;
	}
	
	//printf("i = %i\n", i);
	i = 0;
	
	/*
	printf("Major Length: %i\n", MajorLen);
	printf("Minor Length: %i\n", MinorLen);
	printf("Release Length: %i\n", ReleaseLen);
	printf("Build Length: %i\n\n", BuildLen);
	printf("Major Value: %s\n", MajorChar);
	printf("Minor Value: %s\n", MinorChar);
	printf("Release Value: %s\n", ReleaseChar);
	printf("Build Value: %s\n\n", BuildChar);
	printf("Given Version: %s\n\n", version);
	*/
	
	ver.Major = katoi((const char *)MajorChar);
	ver.Minor = katoi((const char *)MinorChar);
	ver.Release = katoi((const char *)ReleaseChar);
	ver.Build = katoi((const char *)BuildChar);
}

// - by individual integer,
void SetVersionMajor(int value)
{
	ver.Major = value;
}

void SetVersionMinor(int value)
{
	ver.Minor = value;
}

void SetVersionRelease(int value)
{
	ver.Release = value;
}

void SetVersionBuild(int value)
{
	ver.Build = value;
}

// Get version number:

int GetVersionFull()
{ // This function returns integer representing version of active library settings, eg. if version is set to "1.0.0 Build 10" the output will be 10010:
	int len = 0;
    len = len + CountDigits(ver.Major);
    len = len + CountDigits(ver.Minor);
	len = len + CountDigits(ver.Release);
	len = len + CountDigits(ver.Build);
	
	/*
	printf("Length of Major: %i\n", CountDigits(ver.Major));
	printf("Length of Minor: %i\n", CountDigits(ver.Minor));
	printf("Length of Release: %i\n", CountDigits(ver.Release));
	printf("Length of Build: %i\n", CountDigits(ver.Build));
	printf("Major Value: %i\n", ver.Major);
	printf("Minor Value: %i\n", ver.Minor);
	printf("Release Value: %i\n", ver.Release);
	printf("Build Value: %i\n", ver.Build);
	*/
	
	char *versionPtr = kcalloc(len, sizeof(char));
	char buffer[100];

	/*
	printf("Version length: %i\n", len);
	printf("Version value: %s\n", versionPtr);
	printf("Major digits: %i\n", CountDigits(ver.Major));
	printf("Buffer value: %s\n", buffer);
	*/
	
	kitoa(ver.Major, buffer, 10);
	kstrcat(versionPtr, buffer);
	memset(buffer, '0', 100);
	
	kitoa(ver.Minor, buffer, 10);
	kstrcat(versionPtr, buffer);
	memset(buffer, '0', 100);
	
	kitoa(ver.Release, buffer, 10);
	kstrcat(versionPtr, buffer);
	memset(buffer, '0', 100);
	
	kitoa(ver.Build, buffer, 10);
	kstrcat(versionPtr, buffer);
	memset(buffer, '0', 100);
	
	int verint = katoi(versionPtr);
	
	return verint;
}

int GetVersionMajor() { return ver.Major; }

int GetVersionMinor() { return ver.Minor; }

int GetVersionRelease() { return ver.Release; }

int GetVersionBuild() { return ver.Build; }

// Increment or decrement given version number:

void IncrementMajor() { ver.Major++; }

void IncrementMinor() { ver.Minor++; }

void IncrementRelease() { ver.Release++; }

void IncrementBuild() { ver.Build++; }

void DecrementMajor() { ver.Major--; }

void DecrementMinor() { ver.Minor--; }

void DecrementRelease() { ver.Release--; }

void DecrementBuild() { ver.Build--; }

// Write in console full version of app:
void ConsoleLogVersion()
{
	kprintf("%i.%i.%i %i", ver.Major, ver.Minor, ver.Release, ver.Build);
}

// Return string same as console's:
char *LogVersionString()
{
	int len = 0;
    len = len + CountDigits(ver.Major);
    len = len + CountDigits(ver.Minor);
	len = len + CountDigits(ver.Release);
	len = len + CountDigits(ver.Build);
	
	char *versionPtr = kcalloc(len, sizeof(char));
	char buffer[100];
	
	kitoa(ver.Major, buffer, 10);
	kstrcat(versionPtr, buffer);
	kstrcat(versionPtr, ".");
	
	kitoa(ver.Minor, buffer, 10);
	kstrcat(versionPtr, buffer);
	kstrcat(versionPtr, ".");
	
	kitoa(ver.Release, buffer, 10);
	kstrcat(versionPtr, buffer);
	kstrcat(versionPtr, ".");
	
	kitoa(ver.Build, buffer, 10);
	kstrcat(versionPtr, buffer);
	kstrcat(versionPtr, "\0");
	
	/*
	printf("Buffer value: %s\n", buffer);
	printf("Version value: %s\n", versionPtr);
	*/
	
	return versionPtr;
}

