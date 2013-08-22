//
//  game.c
//  
//
//  Created by Max Luzuriaga on 10/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "game.h"

void start_game()
{
	print_intro();
	
	char input[30];
	char target[30] = "START";
	for(;;) {
		printf("> ");
		
		fgets(input, sizeof input, stdin);
		strip(input);
		
		if(strcmp(target, input) == 0)
			break;
	}
	
	printf("\n\n");
	
	initialize_state();
	
	play_round();
}

void initialize_state()
{
	// CHANGE THESE VARIABLES WITH INPUT FROM GROUP
	state.health = 100;
	state.addictionLevel = 55;
	state.money = 1000;
	
	state.currentLodging = kParents;
	state.currentJob = kUnemployed;
	state.hivPositive = 0;
	
	state.roundsLeftInParents = 2;
	state.roundsLeftInFriends = 1;
	state.roundsPlayed = 0;
	
	lastState = state;
}

void print_intro()
{
	printf("\n\n::::::::::: :::    ::: ::::    ::: :::    :::      ::::::::::: :::     :::        :::::::::: ::::::::  \n    :+:     :+:    :+: :+:+:   :+: :+:   :+:           :+:   :+: :+:   :+:        :+:       :+:    :+: \n    +:+     +:+    +:+ :+:+:+  +:+ +:+  +:+            +:+  +:+   +:+  +:+        +:+       +:+        \n    +#+     +#+    +:+ +#+ +:+ +#+ +#++:++             +#+ +#++:++#++: +#+        +#++:++#  +#++:++#++ \n    +#+     +#+    +#+ +#+  +#+#+# +#+  +#+            +#+ +#+     +#+ +#+        +#+              +#+ \n#+# #+#     #+#    #+# #+#   #+#+# #+#   #+#           #+# #+#     #+# #+#        #+#       #+#    #+# \n #####       ########  ###    #### ###    ###          ### ###     ### ########## ########## ########\n\n\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - NOT EVEN ONCE - - - - - - - - - - - - - - - - - - - - - -\n\n");
	printf("Open this for maximum effect: http://endlessvideo.com/watch?v=Qwe10iDlFQo");
	printf("\n\n- - - Type \"START\" to continue - - -\n\n");
}