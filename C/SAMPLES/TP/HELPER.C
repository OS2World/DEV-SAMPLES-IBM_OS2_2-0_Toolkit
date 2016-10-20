#ifndef lint
static char *sccsid = "@(#)helper.c 1.3 1/22/92 16:10:13 [1/26/92] (c)IBM Corp. 1992";
#endif

/*
 * This class is adapted from the book
 *   Class Construction in C and C++, Object Oriented Fundamentals
 *   by Roger Sessions, Copyright (c) 1992 Prentice Hall.
 * Reprinted with permission.
 */

/* File: helper.c */

#include "helper.h"
#include <stdio.h>
#include <stdlib.h>

/* ************************************************************ */
void shouldHaveOverridden(SOMObject * thisObject, char *methodName)
{
    char *class = _somGetClassName(thisObject);

    printf("RUN TIME ERROR\n");
    printf("method: %s invoked on object of class: %s\n", methodName, class);
    printf("%s MUST override %s, and has not.\n", class, methodName);
    exit(1);
}
