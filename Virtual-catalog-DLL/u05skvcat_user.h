#pragma once
//skvcat_user.h - use virtual catalog and included DLLLs


/*
this DLL uses  other DLLs
corresponding entries are described in the files 

skbminlex_user.h
skbvcminlex_user.h
skgminlex_user.h
skgrid_minlex_user.h

The virtual catalog offers three main functionalities :

find the solution grid knowing the rank 1-5472730538
find the rank of a given solution grid
process a chunk of solution grids of the catalog

No check is done on the validity of the solution grid although the results are unpredictable if a false solution grid is entered.
A special call is available to check the validity of a given before the call to the relevant process.

An exchange structure is used to send back information in several cases.
The pointer to the strucutre must be first obtained. this is done in a first call telling which funtionality will be used.

In most cases, a return code tells if something wrong occured. 
If the return is the rank of a solution grid, a return 0 is then used as wrong return.

The current  entries are

//========= check validity
int skvcatIsVali81(char* z);
char * z is the pointer to the 81 field assumed to be a valid solution grid
return is 1 if it is ok, 0 if it is not
//========  define the process and get the pointer to the exchange area
This must be the first call. All other entries will usuall be cancelles if this call is not doen,  

int  SkvcatSetModeGetVCDESK(int mode, VCDESC** pe);

mode must be 0/1/2 
	0 sequential process on a virtual file
	1 rank => solution grid
	2 solution grid to rank
VCDESC** pe to get back the value of VCDESC * p

return value is -1 if the mode is not one of the expected values, o if the call is ok

________________
int  SkvcatSetChangeMode(int mode);

Although some call do it directly, this is an entry to chnage the mode if needed. 
It can be so if the calling program works first in rank => sol mode and then wants to swtch to a virtual file process.

//==================== mode 0 virtual file
in this first release, a virtual file is made of a chunk of first bands;
Later smalle chunks of ranks will be available. are planned
. first band plus first mini row in row 4
. first four rows
. a range of ranks.
the VCDESC exchange struct is designed fo such uses
Current entries are 
___________________

int SkvOpennBands(int ib1, int ib2);
defines the chunk 
ib1 first band index (0-415) 
ib2 last band index
the return value is -1 if something wrong happens
 missing first call or current mode not 0
 not valid ib1/ib2
__________________

int SkvGetNext();
to catch the next solution grid.
the return value is in the exchange area
the return code is -1 if 
 the end of virtual file has been reached
 anything wrong happened (as a missing mode or open)
 
//==================== mode 1 rank => solution grid
Here nothing special expected

int SkvcatFinSolForRank(uint64_t rank);
 The rank is given
 the solution grid comes back in the exchange area
 
 the return code is -1 is something wrong happened
	missing mode 1
	invalid rank
	
//==========================mode 2 solution grid => rank
In fact we have here only one process if we start from a solution grid in min lexical morp.
To make it simpler for the user, the given can be   
char [81] with digits 1-9
int [81   with values 0-8

Again, no check is done with unpredictable results if the entry is not valid. 
It is the responsability of the caller to use the minimal entry is the given is really a minimal morph
_______________________________

uint64_t SkvcatGetRankFromSolMin(int * sgiven);
uint64_t SkvcatGetRankFromSolCharMin(char* sgiven);

the return value is the rank 1-5472730538, 0 is something wrong happened

_________________________________________________

But the DLL accepts also given not minimal. Then, the min lexical morph is first searched and sent back as a int[81]

uint64_t SkvcatGetRankFromSolNotMin(int* sgiven, int* sback);
uint64_t SkvcatGetRankFromSolCharNotMin(char* sgiven, int* sback);

Same as above, but the int * sback is the pointer to the caller area receiving the min lexicla morph.

*/
struct VCDESC {
	uint64_t rank;
	int i416, i9992, i660k1, ir1, i660k2, ir2;
	struct G { char b1[27], r4[9], rx[45]; }g;
	
} * pvcdesc;

extern "C" __declspec(dllimport) int  SkvcatSetModeGetVCDESK(int mode, VCDESC** pe);
extern "C" __declspec(dllimport) int  SkvcatSetChangeMode(int mode);

extern "C" __declspec(dllimport) int SkvcatFinSolForRank(uint64_t rank);
extern "C" __declspec(dllimport) uint64_t SkvcatGetRankFromSolMin(int * sgiven);

extern "C" __declspec(dllimport) uint64_t SkvcatGetRankFromSolNotMin(int* sgiven, int* sback);
extern "C" __declspec(dllimport) uint64_t SkvcatGetRankFromSolCharMin(char* sgiven);
extern "C" __declspec(dllimport) uint64_t SkvcatGetRankFromSolCharNotMin(char* sgiven, int* sback);

extern "C" __declspec(dllimport) int SkvOpennBands(int ib1, int ib2);
extern "C" __declspec(dllimport) int SkvGetNext();

extern "C" __declspec(dllimport) int skvcatIsVali81(char* z);
