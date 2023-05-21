#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __IMPL_TEAMS_INTERNAL
#include "teams.h"

typedef struct team_impl_struct {
	char name[255];
	char members[3][255];
	char institution[255];
	uint8_t solved;
} TEAM_impl;
// base functions
TEAM team_new()
{
	return (TEAM_impl *)malloc(sizeof(TEAM_impl));
}
void team_del(TEAM team)
{
	if(team) free(team);
}

// Setter definitions
// @set char[]: TEAM.name -> bool
SETTER(char*, name)
{
	return !(strncpy(team->name, name, 255) == NULL);
}
// @set char[]: TEAM.institution -> bool
SETTER(char*, institution)
{
	return !(strncpy(team->institution, institution, 255) == NULL);
}
// @set char[]: TEAM.member_name, int: id -> bool
SETTER(char*, member_name, int id)
{
	return (id > 0 && id < 4 && !(strncpy(team->members[id-1], member_name, 255) == NULL));
}
// @set int: TEAM.solved -> bool
SETTER(uint8_t, solved)
{
	if (solved <= 10)
		team->solved = solved;
	return (solved <= 10);
}

// Getter definitions
// @get TEAM.name -> char[]
GETTER(char*, name)
{
	return team->name;
}
// @get TEAM.institution -> char[]
GETTER(char*, institution)
{
	return team->institution;
}
// @get TEAM.solved -> int
GETTER(uint8_t, solved)
{
	return team->solved;
}
// @get TEAM.member_name, id -> char[]
GETTER(char*, member_name, int id)
{
	return (id > 0 && id < 4)? team->members[id - 1] : "(incorrect id)";
}

int team_printf(TEAM team)
{
	return team_fprintf(stdout, team);
}
int team_fprintf(FILE *file, TEAM team)
{
	return fprintf(file,
	               "Team name  : %s\n"
	               "Institution: %s\n"
	               "Solved     : %u\n"
	               "   Member 1: %s\n"
	               "   Member 2: %s\n"
	               "   Member 3: %s\n",
	               team->name, team->institution, team->solved,
	               team->members[0], team->members[1], team->members[2]);
}

TEAM team_find_champion(TEAM teams[], unsigned num)
{
	TEAM champion = teams[num - 1];
	while(num --)
		if ( teams[num]->solved > champion->solved )
			champion = teams[num];
	return champion;
}
