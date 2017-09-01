#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=CLang-Generic
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/938967446/quicksort.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/randomizedQuicksort.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/quicksortandrandomizedquicksort

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/quicksortandrandomizedquicksort: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/quicksortandrandomizedquicksort ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/938967446/quicksort.o: ../oblig2/quicksort.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/938967446
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/938967446/quicksort.o ../oblig2/quicksort.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/randomizedQuicksort.o: randomizedQuicksort.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/randomizedQuicksort.o randomizedQuicksort.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/quicksortandrandomizedquicksort

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
