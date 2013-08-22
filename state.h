//
//  state.h
//  
//
//  Created by Max Luzuriaga on 10/3/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

typedef enum {
	kApartment,
	kParents,
	kFriends,
	kHomeless
} Lodging;

typedef enum {
	kUnemployed,
	kLowPayingJob,
	kMediumPayingJob,
	kHighPayingJob
} Job;

typedef struct State {
	int health;
	int addictionLevel;
	int money;
	
	Lodging currentLodging;
	Job currentJob;
	int hivPositive;
	
	int roundsLeftInParents;
	int roundsLeftInFriends;
	int roundsSincePromotion;
	int roundsPlayed;
} State;

State state;
State lastState;