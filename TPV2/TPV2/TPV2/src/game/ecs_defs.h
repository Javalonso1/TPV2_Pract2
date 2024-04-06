// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// Components list - must have at least one element
//
#define _CMPS_LIST_ \
	TRANSFORM, \
	IMAGE, \
	HEALTH, \
	IMAGEWITHFRAMES, \
	STARMOTION, \
	POINTS

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	STARS,\
	GHOST

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    PACMAN

// Systems list - must have at least one element
//
#define _SYS_LIST_ \
    STARS, \
	PACMAN, \
	GHOST, \
	RENDER, \
	GAMECTRL, \
	COLLISIONS

