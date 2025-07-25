//Modify this file to change what commands output to your statusbar, and recompile using the make command.

static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
    {"",    "record-screen.sh -s",          5,     13},
    {"",    "sb-music.sh",                  2,      5},
    {"",    "sb-mailbox.sh",                10,    10},
    {"",    "sb-news.sh",                   10,    14},
    {"",    "sb-volume.sh",                 10,     2},
    {"",    "sb-nettraf.sh",                3,     12},
    {"",    "sb-memory.sh",                 5,      4},
    {"",    "sb-cpu.sh",                    5,      3},
//  {"",    "sb-battery.sh",                10,    11},
	{"",    "sb-clock.sh",					5,		1},
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
