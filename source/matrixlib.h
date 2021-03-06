
#ifndef MATRIXLIB_H
#define MATRIXLIB_H

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

extern const matrix4x4_t identitymatrix;

// functions for manipulating 4x4 matrices

// copy a matrix4x4
void Matrix4x4_Copy (matrix4x4_t *out, const matrix4x4_t *in);
// copy only the rotation portion of a matrix4x4
void Matrix4x4_CopyRotateOnly (matrix4x4_t *out, const matrix4x4_t *in);
// copy only the translate portion of a matrix4x4
void Matrix4x4_CopyTranslateOnly (matrix4x4_t *out, const matrix4x4_t *in);
// multiply two matrix4x4 together, combining their transformations
// (warning: order matters - Concat(a, b, c) != Concat(a, c, b))
void Matrix4x4_Concat (matrix4x4_t *out, const matrix4x4_t *in1, const matrix4x4_t *in2);
// swaps the rows and columns of the matrix
// (is this useful for anything?)
void Matrix4x4_Transpose (matrix4x4_t *out, const matrix4x4_t *in1);
// swaps the rows and columns of the rotation matrix
// (inverting the rotation, but leaving everything else the same)
void Matrix4x4_Transpose3x3 (matrix4x4_t *out, const matrix4x4_t *in1);
// creates a matrix that does the opposite of the matrix provided
// only supports translate, rotate, scale (not scale3) matrices
void Matrix4x4_Invert_Simple (matrix4x4_t *out, const matrix4x4_t *in1);

// creates an identity matrix
// (a matrix which does nothing)
void Matrix4x4_CreateIdentity (matrix4x4_t *out);
// creates a translate matrix
// (moves vectors)
void Matrix4x4_CreateTranslate (matrix4x4_t *out, float x, float y, float z);
// creates a rotate matrix
// (rotates vectors)
void Matrix4x4_CreateRotate (matrix4x4_t *out, float angle, float x, float y, float z);
// creates a scaling matrix
// (expands or contracts vectors)
// (warning: do not apply this kind of matrix to direction vectors)
void Matrix4x4_CreateScale (matrix4x4_t *out, float x);
// creates a squishing matrix
// (expands or contracts vectors differently in different axis)
// (warning: this is not reversed by Invert_Simple)
// (warning: do not apply this kind of matrix to direction vectors)
void Matrix4x4_CreateScale3 (matrix4x4_t *out, float x, float y, float z);
// creates a matrix for a quake entity
void Matrix4x4_CreateFromQuakeEntity(matrix4x4_t *out, float x, float y, float z, float pitch, float yaw, float roll, float scale);

// converts a matrix4x4 to a set of 3D vectors for the 3 axial directions, and the translate
void Matrix4x4_ToVectors(const matrix4x4_t *in, float vx[3], float vy[3], float vz[3], float t[3]);
// creates a matrix4x4 from a set of 3D vectors for axial directions, and translate
void Matrix4x4_FromVectors(matrix4x4_t *out, const float vx[3], const float vy[3], const float vz[3], const float t[3]);

// blends two matrices together, at a given percentage (blend controls percentage of in2)
void Matrix4x4_Blend (matrix4x4_t *out, const matrix4x4_t *in1, const matrix4x4_t *in2, float blend);

// transforms a 3D vector through a matrix4x4
void Matrix4x4_Transform (const matrix4x4_t *in, const float v[3], float out[3]);
// transforms a 4D vector through a matrix4x4
// (warning: if you don't know why you would need this, you don't need it)
// (warning: the 4th component of the vector should be 1.0)
void Matrix4x4_Transform4 (const matrix4x4_t *in, const float v[4], float out[4]);
// reverse transforms a 3D vector through a matrix4x4, at least for *simple*
// cases (rotation and translation *ONLY*), this attempts to undo the results
// of Transform
//void Matrix4x4_SimpleUntransform (const matrix4x4_t *in, const float v[3], float out[3]);
// transforms a direction vector through the rotation part of a matrix
void Matrix4x4_Transform3x3 (const matrix4x4_t *in, const float v[3], float out[3]);

// ease of use functions
// immediately applies a Translate to the matrix
void Matrix4x4_ConcatTranslate (matrix4x4_t *out, float x, float y, float z);
// immediately applies a Rotate to the matrix
void Matrix4x4_ConcatRotate (matrix4x4_t *out, float angle, float x, float y, float z);
// immediately applies a Scale to the matrix
void Matrix4x4_ConcatScale (matrix4x4_t *out, float x);
// immediately applies a Scale3 to the matrix
void Matrix4x4_ConcatScale3 (matrix4x4_t *out, float x, float y, float z);

// extracts origin vector (translate) from matrix
void Matrix4x4_OriginFromMatrix (const matrix4x4_t *in, float *out);
// extracts scaling factor from matrix (only works for uniform scaling)
float Matrix4x4_ScaleFromMatrix (const matrix4x4_t *in);

#endif
