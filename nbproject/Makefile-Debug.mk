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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
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
	${OBJECTDIR}/allegro_start_shutdown.o \
	${OBJECTDIR}/draw_fractals.o \
	${OBJECTDIR}/input_manage_verification.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/main_parsing_eda.o


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
LDLIBSOPTIONS=`pkg-config --libs allegro-5.0` `pkg-config --libs allegro_primitives-5.0` `pkg-config --libs allegro_image-5.0` -lm  `pkg-config --libs allegro_main-5.0` `pkg-config --libs allegro_audio-5.0` `pkg-config --libs allegro_dialog-5.0` `pkg-config --libs allegro_acodec-5.0`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/eda_tp2

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/eda_tp2: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/eda_tp2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/allegro_start_shutdown.o: allegro_start_shutdown.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_acodec-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/allegro_start_shutdown.o allegro_start_shutdown.c

${OBJECTDIR}/draw_fractals.o: draw_fractals.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_acodec-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/draw_fractals.o draw_fractals.c

${OBJECTDIR}/input_manage_verification.o: input_manage_verification.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_acodec-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/input_manage_verification.o input_manage_verification.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_acodec-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/main_parsing_eda.o: main_parsing_eda.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_acodec-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_parsing_eda.o main_parsing_eda.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/eda_tp2

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
