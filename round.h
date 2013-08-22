//
//  round.h
//  
//
//  Created by Max Luzuriaga on 10/3/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "state.h"
#import "action.h"
#import "utils.c"
#import "game.c"

Action currentAction;
int should_withdraw;

void play_round();
void get_input();
void print_state_of_game();
int respond_to_input(char input[]);
void show_submenu_for_action(Action action);
void withdraw();