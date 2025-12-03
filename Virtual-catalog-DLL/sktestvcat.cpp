
/*
My standard start using maingp as command line analyser
contains the entry G0() called by main
*/
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define INCLUDE_DEBUGGING_CODE
#include <stdlib.h>
#include <sys/timeb.h>
using namespace std;
// nothing to do here
#include "maingp_cpp.h"
#include "dllusers\u05skvcar_user.h"

void C0() { // virtual seque,tial mode 
	char ws[82]; ws[81] = 0;
	cout << " C0_ virtual file bands -v0-  -v1- print if -v2-" << endl;
	if (SkvcatSetModeGetVCDESK(1, &pvcdesc))
		cout << " set mode failed" << endl;
	if (SkvOpennBands(sgo.vx[0], sgo.vx[1])) {
		cout << "could not open bands range "<< sgo.vx[0] <<" "<< sgo.vx[1] << endl;
		return;
	}
	else cout <<"open "<< sgo.vx[0] << " " << sgo.vx[1] <<" done " << endl;
	while (!SkvGetNext()) {
		if (sgo.vx[2]) {
			char ws[82]; ws[81] = 0;
			memcpy(ws, pvcdesc->g.b1, 81);
			cout << ws << " sol " ;
		}
		cout << pvcdesc->rank << " __ " << endl;
	}


}

void C1() {
	char ws[82]; ws[81] = 0;
	cout << " C1_ find sol from rank -v0-" << endl;
	if(  SkvcatSetModeGetVCDESK(1, &pvcdesc))
		cout <<" set mode failed"<<endl;
	if (SkvcatFinSolForRank(sgo.vx64[0]))
		cout << "find failed" << endl;
	else {
		memcpy(ws, pvcdesc->g.b1,81);
		cout <<ws<<" sol"<<endl;
	}
}

void C10() {
	char ws[82]; ws[81] = 0;
	cout << " C10_ find sol from rank file of ranks " << endl;
	char* ze = finput.ze;
	if (SkvcatSetModeGetVCDESK(1, &pvcdesc)) {
		cout << " set mode failed" << endl;
		return;
	}
	while (finput.GetLigne()) {
		if (strlen(ze) < 1)continue;// no empty line
		cout << ze << " rank to find sol" << endl;
		if (strlen(ze) >10)ze[10]=0;// no blank
		int64_t v= strtoll(ze, 0, 10);
		if (SkvcatFinSolForRank(v))
			cout << "find failed" << endl;
		else {
			memcpy(ws, pvcdesc->g.b1, 81);
			cout << ws << " sol" << endl;
		}
	}
	cout << "end of file   "  << endl;

}
void C11() {
	cout << " C11_ find rank for a file of solution grids " << endl;
	char* ze = finput.ze;
	int smin[81];
	if (SkvcatSetModeGetVCDESK(2, &pvcdesc)) {
		cout << " set mode failed" << endl;
		return;
	}
	while (finput.GetLigne()) {
		if (strlen(ze) < 81)continue;// no empty line
		cout << ze << " sol to find rank" << endl;
		if (!skvcatIsVali81(ze)) {
			cout << "not a valid sol" << endl;
			continue;
		}
		uint64_t r =SkvcatGetRankFromSolCharNotMin(ze, smin);
		if (!r) {
			cout << " failed to find rank" << endl;
			continue;
		}
		for (int i = 0; i < 81; i++) cout << smin[i] + 1;
		cout << " solmin rank" << r << endl;

	}
	cout << "end of file   " << endl;


}


/* strtoll example */

/*
#include <stdio.h>      // printf, NULL 
#include <stdlib.h>     // strtoll 

int main()
{
	char szNumbers[] = "1856892505 17b00a12b -01100011010110000010001101100 0x6fffff";
	char* pEnd;
	long long int lli1, lli2, lli3, lli4;
	lli1 = strtoll(szNumbers, &pEnd, 10);
	lli2 = strtoll(pEnd, &pEnd, 16);
	lli3 = strtoll(pEnd, &pEnd, 2);
	lli4 = strtoll(pEnd, NULL, 0);
	printf("The decimal equivalents are: %lld, %lld, %lld and %lld.\n", lli1, lli2, lli3, lli4);
	return 0;
}*/

void Go_0() {
	int need_input_file[3] = { 10,11,94 }, need = 0;
	for (int i = 0; i < 3; i++)
		if (sgo.command == need_input_file[i]) { need = 1; break; }


	// open  outputs files 1.txt
	if (sgo.foutput_name) {
		char zn[200];
		strcpy(zn, sgo.foutput_name);
		int ll = (int)strlen(zn);
		strcpy(&zn[ll], "_file1.txt");
		fout1.open(zn);
	}
	if (need) {// input file expected
		if (!sgo.finput_name) {
			cerr << "missing input file name" << sgo.finput_name << endl; return;
		}
		finput.open(sgo.finput_name);
		if (!finput.is_open()) {
			cerr << "error open file " << sgo.finput_name << endl;
			return;
		}
	}
	cerr << "running command " << sgo.command << endl;


	switch (sgo.command) {
	case 0: C0(); break;// virtual file sequential mode 
	case 1:C1(); break;// get sol from rank
	case 10: C10(); break;// get sol for a file of ranks

	case 11: C11(); break;

	}
	cerr << "go_0 return" << endl;
}

