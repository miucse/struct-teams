#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "teams.h"
#define getline(x, y) \
	while(((x)[strcspn((x), "\r\n")] = 0) == 0 && strncmp((x), "", (y)) == 0) \
		fgets((x), (y), stdin)

int main()
{
	unsigned num = 0, i = 0;
	char line[255] = "";
	TEAM *teams;

	getline(line, 255);
	sscanf(line, "%u", &num);
	strncpy(line, "", 255);
	teams = (TEAM *)malloc(sizeof(TEAM) * num);

	if (teams == NULL) {
		printf("Failed to reserve memory");
		return 1;
	}

	for(i = 0; i < num; i++) {
		teams[i] = team_new();
		unsigned idx = 0, s = 0;
		while (idx ++ < 6) {
			getline(line, 255);
			switch(idx) {
			case 1:
				team_set(teams[i], name, line);
				break;
			case 2:
				team_set(teams[i], institution, line);
				break;
			case 3:
				sscanf(line, "%u", &s);
				team_set(teams[i], solved, s);
				break;
			case 4: // falls through
			case 5: // falls through
			case 6:
				team_set(teams[i], member_name, idx - 3, line);
				break;
			default:
				break;
			}
			strncpy(line, "", 255);
		}
	}
	team_printf(team_find_champion(teams, num));
	return 0;
}
