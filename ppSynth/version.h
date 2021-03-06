#pragma once

#define MAJ_VERSION_STR "1"
#define MAJ_VERSION_INT  1

#define SUB_VERSION_STR "1"
#define SUB_VERSION_INT  1

#define RELEASE_NUMBER_STR "0"
#define RELEASE_NUMBER_INT  0

#define BUILD_NUMBER_STR "0"
#define BUILD_NUMBER_INT  0

// Version with build number (example "1.0.3.342")
#define FULL_VERSION_STR MAJ_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR "." BUILD_NUMBER_STR

// Version without build number (example "1.0.3")
#define VERSION_STR MAJ_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR

