This program parses, computes, and displays statistics from various “League of Legends” matches:

	DESCRIPTION OF 1ST STATISTIC: 
	The 1st statistic creates a “players” table, containing all players who participated in one or more matches in the
	input file. Each row contains the number of kills credited to this player, the number of times they died and
	re-spawned during the match, the kill-to-death ratio (KDR), and the names of the champion(s) used by that
	player. If a player played more than one champion in different matches, the names of the champions are sorted
	alphabetically. Overall, the rows of this table are sorted by KDR. If two players are tied in KDR, they are 
	sorted by kills (highest first), then by deaths, and if tied in all of the above, alphabetically by player name. 

	DESCRIPTION OF 2ND STATISTIC: 
	The 1st statistic creates a “champions” table, which contains all champions that were used in one or more matches
	in the input file. This table contains the number of wins & losses, the corresponding win percentage, and the
	number of times that champion was killed not by another champion, but by a minion (rather embarrassing if
	you think about it...). Overall this table is sorted by win percentage, highest first. If tied in win percentage,
	champions are sorted by wins, then by losses, and finally by name if all of the above are equal.


	DESCRIPTION OF 3RD STATISTIC: 
	My 3rd statisitic keeps track of the time of the first kill,
	the time of the last kill, as well as the average time between kills. It outputs the stats in order of the match id.
	What I've concluded from the stats is that regardless of the length of the match (last kill), the average time between
	kills is roughly the same. Average time between kills fluctuates around 30 seconds. This shows that League of Legions,
	is a very fast paced game. There are constantly kills happening.



	RESULTS FROM 3RD STATISTIC:
	input: input_medium.txt
	output:
	Mathc ID                 Time of First Kill   Time of Last Kill    Aversge Time between Kills
	1778934506                  21.53 seconds      2096.69 seconds          27.27 seconds
	1778936129                  19.63 seconds      1565.45 seconds          34.23 seconds
	1778937369                  22.41 seconds      1209.28 seconds          32.84 seconds
	1778940456                  20.51 seconds      2662.17 seconds          31.91 seconds
	1778942262                   5.92 seconds      2303.59 seconds          33.50 seconds
	1778933327                  13.76 seconds      2746.25 seconds          27.46 seconds
	1779004846                  17.53 seconds      1468.64 seconds          44.60 seconds
	1779005298                  31.73 seconds      1211.72 seconds          38.89 seconds
	1779006394                  22.44 seconds      1278.63 seconds          47.92 seconds
	1778979165                  17.62 seconds      1816.67 seconds          24.48 seconds

	Again the average time between kills for each match fluctates from 24.48 secs to 44.6 secs. This is roughly 2 kills
	per minute. This indicates that this game moves pretty fast. 

