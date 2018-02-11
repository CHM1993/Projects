/* 
 * File:   bloomfilter.h
 * Author: adminuser
 *
 * Created on March 10, 2015, 10:49 AM
 */

#ifndef BLOOMFILTER_H
#define	BLOOMFILTER_H

void  SetBit( int *bloomfilter,  int k );
int TestBit( int *bloomfilter,  int k );

#endif	/* BLOOMFILTER_H */

