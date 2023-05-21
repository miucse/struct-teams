#ifndef __TEAMS_H__
#	define __TEAMS_H__
#	include <stdint.h>
#	include <stdbool.h>
#	define   GETTER(type, field, ...) type team_get_##field(TEAM team, ## __VA_ARGS__)
#	define   SETTER(type, field, ...) bool team_set_##field(TEAM team, ## __VA_ARGS__, type field)
#	define team_get(team, field, ...) team_get_##field(team, ## __VA_ARGS__)
#	define team_set(team, field, ...) team_set_##field(team, ## __VA_ARGS__)
// Type definition
typedef struct team_impl_struct * TEAM;

// base functions
TEAM team_new();
void team_del(TEAM team);

// field getters
SETTER(char *, name);
SETTER(char *, institution);
SETTER(char *, member_name, int);
SETTER(uint8_t, solved);

// field setters
GETTER(char *, name);
GETTER(char *, member_name, int);
GETTER(char *, institution);
GETTER(uint8_t, solved);

// helper functions
int		team_printf(TEAM);
int		team_fprintf(FILE *, TEAM);
TEAM	team_find_champion(TEAM teams[], unsigned num);

#	ifndef __IMPL_TEAMS_INTERNAL
#		undef GETTER
#		undef SETTER
#	endif
#endif /* __TEAMS_H__ */
