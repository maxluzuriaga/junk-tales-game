//
//  round.c
//  
//
//  Created by Max Luzuriaga on 10/3/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "round.h"

void play_round()
{
	should_withdraw = 0;
	currentAction = kNothing;
	print_state_of_game();
	get_input();
	
	printf("\n...\n\n");
	
	lastState = state;
	
	if(should_withdraw == 1) {
		int healthReduction = rand() % 110 + 30;
		state.health -= healthReduction;
		state.addictionLevel -= 35;
	}
	
	state.money -= 100;
	
	int random = rand() % 100 + 1;
	int takeHeroin = (random < state.addictionLevel) ? 1 : 0;
	
	if(takeHeroin == 1) {
		printf("You shoot up heroin this round.\n\n");
		state.addictionLevel += 10;
		state.health -= 10;
		state.money -= 250;
		
		if(state.hivPositive != 1) {
			random = rand() % 100 + 1;
			state.hivPositive = (random < 5) ? 1 : 0;
		}
	} else {
		printf("You do not shoot up heroin this round.\n\n");
		state.addictionLevel -= 5;
	}
	
	if(state.hivPositive == 1)
		state.health -= 20;
	
	if(state.currentLodging == kHomeless) {
		state.health -= 5;
	} else if(state.currentLodging == kApartment) {
		state.money -= 125;
		state.health += 5;
	} else {
		switch (state.currentLodging) {
			case kParents:
			state.roundsLeftInParents -= 1;
			if(state.roundsLeftInParents == 0)
				state.currentLodging = kHomeless;
			break;
			
			case kFriends:
			state.roundsLeftInFriends -= 1;
			if(state.roundsLeftInFriends == 0)
				state.currentLodging = kHomeless;
			break;
		}
	}
	
	if(state.addictionLevel > 40 && state.currentJob != kUnemployed)
		state.currentJob = kUnemployed;
	
	if(state.currentJob == kLowPayingJob)
		state.money += 300;
	else if(state.currentJob == kMediumPayingJob)
		state.money += 400;
	else if(state.currentJob == kHighPayingJob)
		state.money += 500;
	
	if(state.currentJob != kUnemployed) {
		state.roundsSincePromotion++;
		
		if(state.roundsSincePromotion == 5) {
			switch (state.currentJob) {
				case kLowPayingJob:
				state.currentJob = kMediumPayingJob;
				break;
				
				case kMediumPayingJob:
				state.currentJob = kHighPayingJob;
				break;
			}
		}
	}
	
	if(state.health >= 100)
		state.health = 100;
	
	if(state.addictionLevel >= 100)
		state.addictionLevel = 100;
	
	if(state.money <= 0)
		state.money = 0;
	
	state.roundsPlayed++;
	
	if(state.health <= 0)
		printf("\n\n- - - YOU LOSE! - - -\n\n");
	else if (state.addictionLevel <= 0)
		printf("\n\n- - - YOU WIN! - - -\n\n");
	else
		play_round();
}

void get_input()
{
	char input[30];
	for(;;) {
		printf("> ");
		
		fgets(input, sizeof input, stdin);
		strip(input);
		
		if(respond_to_input(input) == 1)
			break;
	}
}

void print_state_of_game()
{
	// Current health, addiction, etc.
	printf("- - - - - - - - ROUND: %d - - - - - - -", state.roundsPlayed + 1);
	
	if (state.roundsPlayed < 9)
		printf(" -");
	
	int healthDiff = state.health - lastState.health;
	int addictionDiff = state.addictionLevel - lastState.addictionLevel;
	int moneyDiff = state.money - lastState.money;
	
	printf("\n\nHealth: %d%%", state.health);
	if(healthDiff != 0)
		printf(" (%s%d%%)", healthDiff >= 0 ? "+" : "", healthDiff);
	
	printf("\nAddiction: %d%%", state.addictionLevel);
	if(addictionDiff != 0)
		printf(" (%s%d%%)", addictionDiff >= 0 ? "+" : "", addictionDiff);
	
	printf("\nMoney: $%d", state.money);
	if(moneyDiff != 0)
		printf(" (%s$%d)", moneyDiff >= 0 ? "+" : "", moneyDiff);
	
	printf("\n\n");
	
	printf("Lodging: ");
	
	switch (state.currentLodging) {
		case kHomeless:
		printf("Homeless");
		break;
		
		case kParents:
		printf("Parents (%d rounds left)", state.roundsLeftInParents);
		break;
		
		case kFriends:
		printf("Friends (%d rounds left)", state.roundsLeftInFriends);
		break;
		
		case kApartment:
		printf("Apartment ($125/round)");
	}
	
	printf("\nJob: ");
	
	switch (state.currentJob) {
		case kUnemployed:
		printf("Unemployed");
		break;
		
		case kLowPayingJob:
		printf("Low level position");
		break;
		
		case kMediumPayingJob:
		printf("Medium level position");
		break;
		
		case kHighPayingJob:
		printf("High level position");
		break;
	}
	
	printf("\nHIV: %s\n", (state.hivPositive == 1 ? "YES" : "NO"));
	
	printf("\n- - - - - - - - - - - - - - - - - - - -\n");
	
	printf("\nYOU CAN:\n\n");
	printf("0. Go on to the next round\n");
	printf("1. Change current lodging\n");
	printf("2. %s\n", (state.currentJob != kUnemployed ? "Quit job" : "Try to get a job"));
	printf("3. Enter withdrawal\n\n");
}

int respond_to_input(char input[])
{
	strip(input);
	
	if(currentAction == kNothing) {
		if(strcmp(input, "1") == 0) {
			currentAction = kChangeLodging;
		} else if (strcmp(input, "2") == 0) {
			currentAction = kChangeJob;
		} else if (strcmp(input, "3") == 0) {
			currentAction = kWithdraw;
		} else if (strcmp(input, "0") == 0) {
			return 1;
		}
		
		if(currentAction != kNothing) {
			show_submenu_for_action(currentAction);
			get_input();
			return 1;
		}
	} else {
		if(strcmp(input, "0") == 0) {
			printf("\n\n");
			print_state_of_game();
			
			currentAction = kNothing;
			get_input();
			
			return 1;
		}
		
		if(currentAction == kChangeLodging) {
			if(strcmp(input, "1") == 0) {
				if(state.money >= 125) {
					state.currentLodging = kApartment;
					show_submenu_for_action(currentAction);
				}
				return 0;
			} else if (strcmp(input, "2") == 0) {
				if(state.roundsLeftInParents != 0) {
					state.currentLodging = kParents;
					show_submenu_for_action(currentAction);
					return 0;
				} else {
					printf("No rounds left.\n");
					return 0;
				}
			} else if(strcmp(input, "3") == 0) {
				if(state.roundsLeftInFriends != 0) {
					state.currentLodging = kFriends;
					show_submenu_for_action(currentAction);
					return 0;
				} else {
					printf("No rounds left.\n");
					return 0;
				}
			} else if(strcmp(input, "4") == 0) {
				state.currentLodging = kHomeless;
				show_submenu_for_action(currentAction);
				return 0;
			}
		} else if(currentAction == kChangeJob && strcmp(input, "1") == 0) {
			if(state.currentJob == kUnemployed) {
				state.currentJob = kLowPayingJob;
				state.roundsSincePromotion = 0;
			} else {
				state.currentJob = kUnemployed;
			}
		} else if(currentAction == kWithdraw && strcmp(input, "1") == 0) {
			should_withdraw = 1;
			return 1;
		}
	}
	
	return 0;
}

void show_submenu_for_action(Action action)
{
	if(action == kChangeLodging) {
		printf("\nChanging Lodging. Choose one:\n\n");
		
		printf("0. Cancel\n");
		
		printf("1. Apartment ($125/round)");
		if(state.currentLodging == kApartment)
			printf(" [CURRENTLY SELECTED]");
			
		printf("\n2. Parents (%d rounds left)", state.roundsLeftInParents);
		if(state.currentLodging == kParents)
			printf(" [CURRENTLY SELECTED]");
		
		printf("\n3. Friends (%d rounds left)", state.roundsLeftInFriends);
		if(state.currentLodging == kFriends)
			printf(" [CURRENTLY SELECTED]");
			
		printf("\n4. Become Homeless (-10 health/round)");
		if(state.currentLodging == kHomeless)
			printf(" [CURRENTLY SELECTED]");
			
		printf("\n\n");
	} else if(action == kChangeJob) {
		if(state.addictionLevel <= 40 && state.currentJob == kUnemployed) {
			printf("\nGet a job?\n\n");
			printf("0. No.\n");
			printf("1. Yes\n");
		} else if(state.currentJob != kUnemployed) {
			printf("\nQuit your job?\n\n");
			printf("0. No.\n");
			printf("1. Yes\n\n");
		} else {
			printf("\nYou can only get a job when your addiction level is below 40%%.\n\n");
			currentAction = kNothing;
		}
	} else if(action == kWithdraw) {
		printf("\nEnter withdrawal? Your health will be sharply decreased.\n\n");
		printf("0. No.\n");
		printf("1. Yes\n\n");
	}
}

void withdraw()
{
	
}