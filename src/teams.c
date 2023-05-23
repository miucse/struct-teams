#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "teams.h"
#define __IMPL_TEAMS_INTERNAL
#include "teams-hell.h"

typedef struct team_impl_struct {
	char name[255];
	char members[3][255];
	char institution[255];
	uint8_t solved;
} TEAM_impl;

// base functions
NEW(team, {
	return (TEAM_impl *)malloc(sizeof(TEAM_impl));
})

DEL(team, {
	if(self) free(self);
})

// Setter definitions
// @set char[]: TEAM.name -> bool
SETTER(team, name,			char *, {
	return !(strncpy(self->name, value, 255) == NULL);
})

// @set char[]: TEAM.institution -> bool
SETTER(team, institution,	char *, {
	return !(strncpy(self->institution, value, 255) == NULL);
})

// @set char[]: TEAM.member_name, int: id -> bool
SETTER(team, member_name,	char *, {
	return (id > 0 && id < 4 && !(strncpy(self->members[id-1], value, 255) == NULL));
}, int id)

// @set int: TEAM.solved -> bool
SETTER(team, solved,		uint8_t, {
	if (value <= 10)
		self->solved = value;
	return (value <= 10);
})

// Getter definitions
// @get TEAM.name -> char[]
GETTER(team, name,			char *, {
	return self->name;
})

// @get TEAM.institution -> char[]
GETTER(team, institution,	char *, {
	return self->institution;
})

// @get TEAM.solved -> int
GETTER(team, solved,		uint8_t, {
	return self->solved;
})

// @get TEAM.member_name, id -> char[]
GETTER(team, member_name,	char *, {
	return (id > 0 && id < 4)? self->members[id - 1] : "(incorrect id)";
}, int id)

DEFINE(team, printf, int, {
	return ask(team, fprintf, self, stdout);
})

DEFINE(team, fprintf, int, {
	return fprintf(file,
	               "Team name  : %s\n"
	               "Institution: %s\n"
	               "Solved     : %u\n"
	               "   Member 1: %s\n"
	               "   Member 2: %s\n"
	               "   Member 3: %s\n",
	               self->name,
	               self->institution,
	               self->solved,
	               self->members[0],
	               self->members[1],
	               self->members[2]);
}, FILE *file)

DEFINE(team, find_champion, team, {
	UNUSED(self);

	team champion = teams[num - 1];
	while(num --)
		if ( teams[num]->solved > champion->solved )
			champion = teams[num];
	return champion;
}, team *teams, unsigned num)
