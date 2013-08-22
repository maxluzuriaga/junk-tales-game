//
//  utils.c
//  
//
//  Created by Max Luzuriaga on 10/3/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "utils.h"

void strip(char *s)
{
	char *p2 = s;
	while(*s != '\0') {
		if(*s != '\t' && *s != '\n') {
			*p2++ = *s++;
		} else {
			++s;
		}
	}
	*p2 = '\0';
}

int roll_dice_with_chances(double chance)
{
	// Return 1 or 0 for whether a dice roll was successful.
	// 'chance' should be in the form of a float out of 1
	
	return 1;
}