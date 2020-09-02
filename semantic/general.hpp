/******************************************************************************
 *  CVS version:
 *     $Id: general.h,v 1.1 2004/05/05 22:00:08 nickie Exp $
 ******************************************************************************
 *
 *  C header file : general.h
 *  Project       : PCL Compiler
 *  Version       : 1.0 alpha
 *  Written by    : Nikolaos S. Papaspyrou (nickie@softlab.ntua.gr)
 *  Date          : May 5, 2004
 *  Description   : Generic symbol table in C, general header file
 *  Modified by	  : Minaidis P., Kimonides A.
 *  
 */


#ifndef __GENERAL_HPP__
#define __GENERAL_HPP__


void *allocate (size_t);
void deallocate (void *);


extern int lineno;
extern const char * filename;


#endif
