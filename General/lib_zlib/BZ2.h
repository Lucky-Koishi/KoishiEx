
/*-------------------------------------------------------------*/
/*--- Public header file for the library.                   ---*/
/*---                                               bzlib.h ---*/
/*-------------------------------------------------------------*/

/* ------------------------------------------------------------------
   This file is part of bzip2/libbzip2, a program and library for
   lossless, block-sorting data compression.

   bzip2/libbzip2 version 1.0.6 of 6 September 2010
   Copyright (C) 1996-2010 Julian Seward <jseward@bzip.org>

   Please read the WARNING, DISCLAIMER and PATENTS sections in the 
   README file.

   This program is released under the terms of the license contained
   in the file LICENSE.
   ------------------------------------------------------------------ */

extern int BZ2_bzBuffToBuffCompress (char* dest, unsigned int* destLen,	char* source, unsigned int sourceLen,int blockSize100k,int verbosity,int workFactor);
extern int BZ2_bzBuffToBuffDecompress (char* dest, unsigned int* destLen,char* source,unsigned int sourceLen,int __small, int verbosity);
