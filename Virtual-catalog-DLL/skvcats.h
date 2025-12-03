



#include "dllusers\skbminlex_user.h"
#include "dllusers\skbvcminlex_user.h"
#include "dllusers\skgminlex_user.h"
#include "dllusers\skgrid_minlex_user.h"
#include "f_externs.h"

int C_transpose_d[81] = {
	0, 9, 18, 27, 36, 45, 54, 63, 72, 1, 10, 19, 28, 37, 46, 55, 64, 73,
	2, 11, 20, 29, 38, 47, 56, 65, 74, 3, 12, 21, 30, 39, 48, 57, 66, 75,
	4, 13, 22, 31, 40, 49, 58, 67, 76, 5, 14, 23, 32, 41, 50, 59, 68, 77,
	6, 15, 24, 33, 42, 51, 60, 69, 78, 7, 16, 25, 34, 43, 52, 61, 70, 79,
	8, 17, 26, 35, 44, 53, 62, 71, 80,
};


#define stack1_54 07007007007007007
//		for (int i = 0; i < 27; i++)D[i] = S[i] - '1';
#define DO27CtoI(S,D) for (int i = 0; i < 27; i++)D[i] = S[i] - '1';
#define DO27ItoC(S,D) for (int i = 0; i < 27; i++)D[i] = S[i] + '1';
#define DO81CtoI(S,D) for (int i = 0; i < 81; i++)D[i] = S[i] - '1';
#define DO81ItoC(S,D) for (int i = 0; i < 81; i++)D[i] = S[i] + '1';

struct TFILLR4 {
	char r4r5[18], b3[27];
}tfillr4[63000], wtfillr4;// max seen 62887 bnad index 9
struct VCDESC {
	uint64_t rank;
	int i416, i9992, i660k1, ir1, i660k2, ir2;
	struct G { char b1[27], r4[9], rx[45]; }g;
	void Fill_b1() {	SkbGetBandChar(i416,g.b1);	}
} vcdesc_e;

//____ entry builder
struct VCAT {// encapsulating global data 
	TPGC* p_tpgc;
	int modeb12, go_back, diagmore, diagbug, 
		it16, it16_2, it16_3,isbandbelow31;
	int idt16[3];// diagonal
	BANDPERM* mypermbandout;
	BANDPERM pband1;// initial  for call to DLL
	BANDPERM permd[3];// storing permms diag if ==
	int irtw2,iret_diag;
	char band1[27],band2[27],band3[27],
		zsol[82], rband2[28];
	int grid0[81],gbit[81],gfree[81],colband1[9],
		grid1[81], gw[81], tc[6], ntc,
		*g0_2,*g0_3;
	int gd[81], need_diagcheck;// diagonal of a fill
	int zsa[27], zsb[27], zsmin[81];
	BANDPERM *t_auto_b1, * t_auto_p1,// maxi is 107
		t_auto_b1r4[108], t_auto_b1r4r5[108],
		pband2, pband3;
	int n_auto_b1, n_auto_p1,
		n_auto_b1r4, n_auto_b1r4r5;
	int b4dmr[3], b5dmr[3], b6dmr[3], b4b5dmr[3];
	int b5dkmr[3], r6mfree[3], b3colfree[9];
	//_________________ gangster 
	int gangcols[9];// 9 bits fields band3 for each colum (see valid band2)
	int gangb12[9]; // digit bf bands 12 per column
	//____________________________ find link solution rank
	uint64_t s_rank, s_rank_r4, s_r4start,s_vr4;
	int s_band, s_minir4, s_r4_index;
	int s_row4[9], s_grid0[81];
	uint32_t pcptx;
	void BuildVr4() {
		s_vr4 = s_grid0[27]+1;
		for (int i = 28; i < 36; i++) {
			s_vr4=10*s_vr4+ s_grid0[i]+1;
		}
	}

	//_______________________ outcat control
	int outmode, mode2below; // 0 strore 1 rank=>sol 2 sol=>rank
	uint64_t stc_kst, stc_kend,// ranks for the chunk
		stc_rkr4_1, stc_rkr4_2,// for current ir4 in sequential mode
		stc_k1,stc_k2;// ranks for the current load
	int stc_bandid,stc_band_endr4,
		stc_4st, stc_4end, stc_4cur, // r4 start end current index
		stc_stn, stc_ncur, // index in load
		stc_end;// end of process get

	VCAT() {
		g0_2 = &grid0[27];
		g0_3 = &grid0[54];
		mypermbandout= GcatGetMappingPointer();
		p_tpgc= SkbsSetModeWithAutos();
		p_tpgc->tpe[0] = &pband1;
		p_tpgc->tpe[1] = &pband2;
		pband1.InitBase(0);// dummy id to have "no perm status"
		outmode = -1;// undefined mode
		stc_end = 1;
	}

	void InitBand1(int iw);
	void InitRow4FromI10375(int i10375);
	void GoRow4From(int itr4);
	void GoRow5();
	void GoRow6();
	void GoNewBand2();
	void GoB2GangsterAnalysis();
	void Outcat();
	//===============  
	int FindSolForRank(uint64_t rank);
	int GetBandIndex();
	void GoSolForRank();
	int FindRankForSolMin();
	void GoSolForSearchRank();
	// start with not minlex
	void  LoadR4();
	int GetNext();
	void OpenBands(int ib1, int ib2);
	void OpenMiniR4(int i1, int i2);
	void OpenR4(int i1, int i2);
	void OpenRank(uint64_t r1, uint64_t r2);

}vcat;
