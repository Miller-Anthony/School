//------------------------------------------------------------------------------
// file:	CP_Image.h
// author:	Daniel Hamilton
// brief:	API for loading and displaying images
//
// DO NOT INCLUDE THIS HEADER IN YOUR PROJECTS DIRECTLY
// SEE: C_Processing.h
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "CP_Export.h"

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

typedef struct PImage_struct* PImage;
typedef enum ShapeMode ShapeMode;

//------------------------------------------------------------------------------
// Public Enums:
//------------------------------------------------------------------------------

enum CP_ImageFlags {
	CP_IMAGE_GENERATE_MIPMAPS	= 1 << 0,	// Generate mipmaps during creation of the image.
	CP_IMAGE_REPEATX			= 1 << 1,	// Repeat image in X direction.
	CP_IMAGE_REPEATY			= 1 << 2,	// Repeat image in Y direction.
	CP_IMAGE_FLIPY				= 1 << 3,	// Flips (inverses) image in Y direction when rendered.
	CP_IMAGE_NEAREST			= 1 << 5,	// Image interpolation is Nearest instead Linear.
	CP_IMAGE_STORE_PIXEL_DATA	= 1 << 6,	// This saves a copy of the pixel data (NOTE: this can be memory expensive)
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// setup any image flags needed for loading and rendering of images (see: CP_ImageFlags)
DLL_EXPORT void setImageFlags(int imageFlags);

// Load the given image from a filepath and return a filepath, uses imageFlags settings
DLL_EXPORT PImage loadImage(const char * filepath);

// Create a new image from an array of pixel data in format (R, G, B, A, R, G, ...), uses imageFlags settings
DLL_EXPORT PImage createImage(unsigned char * data, int w, int h);

// Release an image from the image management system and clean up memory
DLL_EXPORT void freeImage(PImage * img);

// Draw an image at a specific point (x, y) with a size (stretched)
DLL_EXPORT void image(PImage img, float x, float y, float w, float h, int alpha);

// Draw an image at a specific point (x, y) with a size (stretched) rotated by a given degrees
DLL_EXPORT void imageRotated(PImage img, float x, float y, float w, float h, int alpha, float degrees);

// Get the width of a loaded image
DLL_EXPORT int imageWidth(PImage img);

// Get the height of a loaded image
DLL_EXPORT int imageHeight(PImage img);

// Fill out two variables with the width and height of a given image
DLL_EXPORT void imageSize(PImage img, int* w, int* h);

// How to draw the image (drawn similar to a rectangle)
DLL_EXPORT void imageMode(ShapeMode mode);

// Index directly into the image, must be an image created with CP_IMAGE_STORE_PIXEL_DATA
DLL_EXPORT PColor imagePixel(PImage img, int x, int y);

// Create a new image as a subsection of an existing image, uses imageFlags settings (NOTE: can be memory expensive)
// Source image must have been created with CP_IMAGE_STORE_PIXEL_DATA
DLL_EXPORT PImage imageCreateSubimage(const PImage srcImg, int x, int y, int w, int h);

// Create a copy of the image tinted by a specified color, uses imageFlags settings (NOTE: can be memory expensive)
// Source image must have been created with CP_IMAGE_STORE_PIXEL_DATA
DLL_EXPORT PImage imageCreateTint(const PImage srcImg, const PColor tint);

// Access the entire array of pixel data in format (R, G, B, A, R, G, ...)
// Source image must have been created with CP_IMAGE_STORE_PIXEL_DATA
DLL_EXPORT unsigned char * imageData(PImage img);

// Tell the graphics system about an updated image.  Must first change the pixel data by using imageData()
// CANNOT change the width and height of the image
// Source image must have been created with CP_IMAGE_STORE_PIXEL_DATA
DLL_EXPORT void imageUpdate(PImage img);

// Reads the frame buffer and stores it in a new image, uses imageFlags settings
DLL_EXPORT PImage readFrameBuffer(int x, int y, int w, int h);
