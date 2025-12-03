
#define _CRT_SECURE_NO_DEPRECATE
//#define SK0FDEBUGGINGBAND
//#define SK0FDEBUGGING_EXT


#include <utility>
#include <limits.h>
#include "sk0__h.h"
#include "skb_permband.h"
#define SK0FSMALLBANDFUNCTIONS
#include "sk0_loads_cpp.h"
#include "maingp_user.h"
#include "skvcats.h"
#include "skb_permband_cpp.h"



int GetBandIndex(uint64_t r) {
	for (int i = 1; i <= 416; i++)		if (b1startcat[i] >= r) 
		return (  i - 1);	
	return -1;
}




void VcatFillBand( VCDESC * z ){
	register int ib = z->i416;
	vcat.InitBand1(ib);
	memcpy(z->g.b1, vcat.grid0, 4 * 27);
	z->i660k1 = b1r4[ib]; z->ir1 =0;
	z->i660k2 = b1r4[ib]; z->ir2 = 0;
}
void VcatFillRowStart(VCDESC* z) {
	register int ib = z->i416;
	vcat.InitBand1(ib);
	memcpy(z->g.b1, vcat.grid0, 4 * 27);
	z->i660k1 = b1r4[ib]; z->ir1 = 0;
	z->i660k2 = b1r4[ib]; z->ir2 = 0;
}

int  VcatFillRank(VCDESC* z) {
	register uint64_t r = z->rank;
	if (r > 5472730538) return -1;
	register int ib = GetBandIndex(r);
	if (ib < 0)return -1;
	z->i416 = ib; z->Fill_b1();
	register int iminir4 = GetMinir4id9992(ib, r);
	if (iminir4 < 0) return -1;
	z->i9992 = iminir4;
	uint32_t istartr4, iendr4;
	uint64_t rank_r4;
	GetR4PointersFrom_minir4(iminir4, rank_r4, istartr4, iendr4);

}

//====================== gen cat in min lex order
void VCAT::InitBand1(int iw) {
	uint64_t t1 = 0, t2 = 0, t3 = 0, t4 = 0;
	it16 = iw;
	SkbGetBandChar(it16, band1);
	for (int i = 0; i < 27; i++) {
		grid0[i] = band1[i] - '1';
		gbit[i] = 1 << grid0[i];
	}
	for (int ic = 0; ic < 9; ic++)
		colband1[ic] = gbit[ic] | gbit[ic + 9] | gbit[ic + 18];
	n_auto_b1 = SkbGetAutoMorphs(it16, & t_auto_b1);
	p_tpgc->bs_id[0] = it16;
}

#define CELLGO(N,G,R) 		while (gfree[N]) { \
bitscanforward(grid0[N], gfree[N]);gbit[N] = 1 << grid0[N]; \
gfree[N] ^= gbit[N];goto G;}goto R;

inline int CompRow(BANDPERM& p, int* ra, int* rb) {
	for (int i = 0; i < 9; i++) {// morph r5 < R4 ?
		int v = p.map[ra[p.cols[i]]];
		if (v < rb[i])return -1;
		if (v > rb[i])return 1;
	}
	return 0; // equal
}
inline void MorphRow(BANDPERM& p, int* ra, int* rb) {
	for (int i = 0; i < 9; i++)  rb[i] = p.map[ra[p.cols[i]]];
}

void  VCAT::InitRow4FromI10375(int i10375) {
	grid0[27] = 1;
	register int64_t r4 = row4t[i10375] - 200000000,
		w = r4 / 10000000;
	grid0[28] = (int)w - 1; r4 -= w * 10000000;
	w = r4 / 1000000; grid0[29] = (int)w - 1; r4 -= w * 1000000;
	w = r4 / 100000; grid0[30] = (int)w - 1; r4 -= w * 100000;
	w = r4 / 10000; grid0[31] = (int)w - 1; r4 -= w * 10000;
	w = r4 / 1000; grid0[32] = (int)w - 1; r4 -= w * 1000;
	w = r4 / 100; grid0[33] = (int)w - 1; r4 -= w * 100;
	w = r4 / 10; grid0[34] = (int)w - 1; r4 -= w * 10;
	grid0[35] = (int)r4 - 1;
	for (int i = 27; i < 36; i++) 	gbit[i] = 1 << grid0[i];
	b4dmr[0] = gbit[27] | gbit[28] | gbit[29];
	b5dmr[0] = gbit[30] | gbit[31] | gbit[32];
	pcptx = 0;
}
void VCAT::GoRow4From(int itr4) {
	int ir4 = tr4u[itr4];
	InitRow4FromI10375(ir4);
	GoRow5();
}


void VCAT::GoRow5() {
	if (outmode < 0)return;// undefined process
	go_back = 0;
	b6dmr[0] = gbit[33] | gbit[34] | gbit[35];
	gfree[36] = 0xff & ~ (b4dmr[0] | colband1[0]);// can not be 9
r5c1l: {CELLGO(36, r5c2, endr5)}
endr5:return;

r5c2:; gfree[37] = 0x1ff ^ (b4dmr[0] | gbit[36] | colband1[1]);
r5c2l: {CELLGO(37, r5c3, r5c1l)}

r5c3:b4dmr[1] = gbit[36] | gbit[37];
	gfree[38] = 0x1ff ^ (b4dmr[0] | b4dmr[1] | colband1[2]);
r5c3l: {CELLGO(38, r5c4, r5c2l)}
//______________________________________________________ box5
r5c4: b4dmr[1] = gbit[36] | gbit[37] | gbit[38];
	b5dkmr[1] = b4dmr[1] | b5dmr[0];
	// early back with repeated mini row and band 1 over 30
	isbandbelow31 = 0;
	int b5free = 0x1ff;
	if (b4dmr[1] == b5dmr[0]) {
		if(it16>30) goto r5c3l;
		isbandbelow31 = 1;
		b5free = b6dmr[0];
	}
	else if (b4dmr[1] == b6dmr[0]) {
		if (it16 > 30) goto r5c3l;
		isbandbelow31 = 1;
		b5free = b4dmr[0];
	}
	gfree[39] = b5free &~ (b5dkmr[1] | colband1[3]);
r5c4l: {CELLGO(39, r5c5, r5c3l)}

r5c5:gfree[40] = b5free & ~(b5dkmr[1] | gbit[39] | colband1[4]);

r5c5l: {CELLGO(40, r5c6, r5c4l)}

r5c6:b5dmr[1] = gbit[39] | gbit[40];
	gfree[41] = b5free & ~(b5dkmr[1] | b5dmr[1] | colband1[5]);
r5c6l: {CELLGO(41, r5c7, r5c5l)}
//______________________________________________________ box6
r5c7:b5dmr[1] = gbit[39] | gbit[40] | gbit[41];
	b4b5dmr[1] = b4dmr[1] | b5dmr[1]|b6dmr[0];// row + box known
	gfree[42] = 0x1ff ^ (b4b5dmr[1] | colband1[6]);
r5c7l: {CELLGO(42, r5c8, r5c6l)}

r5c8:gfree[43] = 0x1ff ^ (b4b5dmr[1] | gbit[42] | colband1[7]);
r5c8l: {CELLGO(43, r5c9, r5c7l)}

r5c9:gfree[44] = 0x1ff ^ (b4b5dmr[1] | gbit[42] | gbit[43] | colband1[8]);
	if (gfree[44]) {
		gbit[44] = gfree[44];
		bitscanforward(grid0[44], gfree[44]);// row 5 filled
		//for (int i = 27; i <= 44; i++) cout << grid0[i] + 1;
		//cout << " r4r5 " << endl;
		GoRow6();
	}
	if (go_back)return;
	goto r5c8l;
}
void VCAT::GoRow6() {
	// check first if rows 4 5 stay minimal with auto morphs band1
	if (n_auto_b1) {
		n_auto_b1r4r5 = 0;
		for (int imorph = 0; imorph < n_auto_b1; imorph++) {
			BANDPERM& p = t_auto_b1[imorph];
			int ir = CompRow(p, &grid0[36], &grid0[27]);
			if (ir < 0) return;			if (ir) continue;
			// r4 eq r5 morph si if r4morph < r5
			ir = CompRow(p, &grid0[27], &grid0[36]);
			if (ir < 0) return;	 // a lower exists
			if(!ir)t_auto_b1r4r5[n_auto_b1r4r5++] = p;
		}
		for (int imorph = 0; imorph < n_auto_b1r4; imorph++) {
			BANDPERM& p = t_auto_b1r4[imorph];
			int ir = CompRow(p, &grid0[36], &grid0[36]);// r5 =>r5
			if (ir < 0) return;		
			if (!ir)  t_auto_b1r4r5[n_auto_b1r4r5++] = p;			
		}
	}
	b6dmr[1] = gbit[42] | gbit[43] | gbit[44];
	// check free mini rows have  all digits
	r6mfree[0]= 0x1ff ^ (b4dmr[0] | b4dmr[1]);
	r6mfree[1] = 0x1ff ^ (b5dmr[0] | b5dmr[1]);
	r6mfree[2] = 0x1ff ^ (b6dmr[0] | b6dmr[1]);
	if ((r6mfree[0] | r6mfree[1] | r6mfree[2]) != 0x1ff) return;

	gfree[45] = r6mfree[0] & ~colband1[0];
	// can not be below r5c1
	gfree[45] &= ~(gbit[36] - 1);
	// if band1 over 30 can not be repetitive mini column
	if (it16 >30) {
		register int r = colband1[1]; //25?
		if (r & gbit[36])gfree[45] &= ~r;
	}
r6c1l: {CELLGO(45, r6c2, endr6)}
endr6:return;

r6c2:; gfree[46] = r6mfree[0] & ~(colband1[1]| gbit[45]);
r6c2l: {CELLGO(46, r6c3, r6c1l)}

r6c3:gfree[47] = r6mfree[0] & ~(colband1[2] | gbit[45] | gbit[46]);
	if (gfree[47]) {
		bitscanforward(grid0[47],gfree[47]);
		gbit[47] = gfree[47];
	}
	else    goto r6c2l;
	//______________________________________________________ box5 r6c4
	gfree[48] = r6mfree[1] & ~colband1[3];
	// if band1 over 30 can not be repetitive mini column
	if (it16 > 30) {
		register int r = colband1[4], r2 = colband1[5],
			v=gbit[30] | gbit[39];
		if(_popcnt32(r&v)==2)gfree[48] &= ~r;
		else if (_popcnt32(r2 & v) == 2)gfree[48] &= ~r2;
	}

r6c4l: {CELLGO(48, r6c5, r6c2l)}

r6c5:gfree[49] = r6mfree[1] & ~(colband1[4] | gbit[48]);
r6c5l: {CELLGO(49, r6c6, r6c4l)}

r6c6:gfree[50] = r6mfree[1] & ~(colband1[5] | gbit[48] | gbit[49]);
	if (gfree[50]) {
		bitscanforward(grid0[50], gfree[50]);
		gbit[50] = gfree[50];
	}
	else    goto r6c5l;
	//______________________________________________________ box6 r6c7
	gfree[51] = r6mfree[2] & ~colband1[6];
	// if band1 over 30 can not be repetitive mini column
	if (it16 > 30) {
		register int r = colband1[7], r2 = colband1[8],
			v = gbit[33] | gbit[42];
		if(_popcnt32(r&v)==2)gfree[51] &= ~r;
		else if (_popcnt32(r2 & v) == 2)gfree[51] &= ~r2;
	}
r6c7l: {CELLGO(51, r6c8, r6c5l)}

r6c8:gfree[52] = r6mfree[2] & ~(colband1[7] | gbit[51]);
r5c8l: {CELLGO(52, r6c9, r6c7l)}

r6c9:gfree[53] = r6mfree[2] & ~(colband1[8] | gbit[51] | gbit[52]);;
	if (gfree[53]) {
		bitscanforward(grid0[53], gfree[53]);// row 5 filled
		gbit[53] = gfree[53];
		GoNewBand2();
	}
	if (go_back)return;
	goto r5c8l;
}
void VCAT::GoNewBand2() {
	if (go_back)return;
	for (int i = 0; i < 18; i++)wtfillr4.r4r5[i] = grid0[36 + i] + '1';
	// check if band2 stays minimal with auto morphs band1
	/*
	if(0){// bug to see in ismin later
		int ir = GcatGetBandIndex(&grid0[27], it16);
		if (ir < 0) return;// lower band1
		if (!ir) {
			pband2 = *mypermbandout;
			it16_2 = pband2.i416;
		}
		else it16_2 = 500;
		p_tpgc->bs_id[1] = pband2.i416;
	}
	*/

	{
		SkbGetMappingInt(&grid0[27], &pband2);
		register int id = pband2.i416;
		if (id < it16) return;// lower band1 
		it16_2 = pband2.i416;
		p_tpgc->bs_id[1] = id;
	}

	// build now the gangster band 3
	for (int i = 0, j = 27; i < 9; i++, j++)
		b3colfree[i] = 0x1ff ^ (colband1[i] | gbit[j] | gbit[j + 9] | gbit[j + 18]);
	for (int i = 0, j = 0; i < 3; i++, j += 3)
		if ((b3colfree[j] | b3colfree[j+1] | b3colfree[j+2]) != 0x1ff) return;
	if (n_auto_b1) {
		for (int imorph = 0; imorph < n_auto_b1; imorph++) {
			BANDPERM& p = t_auto_b1[imorph];
			int band[27];
			p.MorphOrdered(&grid0[27], band);
			int ir = BandCompare(band, &grid0[27]);
			if (ir < 0) return;			
		}
	}	
	if (it16 == it16_2) {
		int banda[27];
		pband2.MorphOrdered(grid0, banda);
		int ir = BandCompare(banda, &grid0[27]);
		if (ir < 0) return;
		if (n_auto_b1) {
			for (int imorph = 0; imorph < n_auto_b1; imorph++) {
				BANDPERM& p = t_auto_b1[imorph];
				int band[27];
				p.MorphOrdered(banda, band);
				int ir = BandCompare(band, &grid0[27]);
				if (ir < 0) return;
			}
		}
	}
	mode2below = 0;

	if (outmode == 2) {// known sol look for rank
		//for (int i = 0; i < 27; i++) cout<< grid0[27 + i] + 1;
		//cout << " newband " << endl;
		for (int i = 9; i < 27; i++) {
			int ir = grid0[27 + i] - s_grid0[27 + i];
			if (ir < 0) {	mode2below = 1; break;}
			if(ir>0) {go_back = 2; return;	}// failed
		}		
	}
	GoB2GangsterAnalysis(); 


}

void VCAT::GoB2GangsterAnalysis() {
	char gg[28]; gg[27 ] = 0;
	int ggi[27];
	for (int i = 0,j=0; i < 9; i++) {
		int x[3],y= b3colfree[i];
		bitscanforward(x[0], y);
		y ^= 1 << x[0];
		bitscanforward(x[1], y);
		bitscanreverse(x[2], y);
		ggi[j] = x[0];	gg[j++] = x[0]+'1'; 
		ggi[j] = x[1]; gg[j++] = x[1] + '1';
		ggi[j] = x[2]; gg[j++] = x[2] + '1';
	}
	int ig = SkgGetGang(ggi);
	int nfillsok= SkgBuildMorphedTableSortedOver(it16);
	for (int i = 0; i < nfillsok; i++) {
		int* myb3 = Skg_GetMorphedOrdered(i, &it16_3);
		memcpy(&grid0[54], myb3, 4 * 27);
		p_tpgc->bs_id[2] = it16_3;
		//int ir = SkbsGetMinIsNotMin(grid0);
/*
		int g[81],irc=0;
		SkbsGetMin(grid0, g);
		for (int i = 0; i < 81; i++) {
			if (g[i] < grid0[i]) { irc = 1; break; }
		}
		if (ir != irc) {
			int* ii = p_tpgc->bs_id;
			cout << " error ir irc " << ir << " " << irc
				<< " ids "<< it16<<" "<< it16_2 << " " << it16_3
				<<" gid " << ii[0] << " " << ii[1] << " " << ii[2]
				<<" " << ii[3] << " " << ii[4] << " " << ii[5] << endl;
			ir = irc;
		}
*/

		//if (ir) continue;
		if (SkbsGetMinIsNotMin(grid0)) continue;
		if (mode2below) {	pcptx++; continue;}
		Outcat();
		if (go_back) return;
	}

}

void VCAT::Outcat() {
	if (outmode < 0) return; // undefined mode
	if (go_back)return;
	pcptx++;// row4 count of valid fills
	//register uint64_t R = s_r4start + pcptx;//old
	register uint64_t R = stc_rkr4_1 + pcptx;// current rank 1_..38

	switch (outmode) {
	case 2: {// search b3 ok with given
		for (int i = 0; i < 27; i++) {
			int ir = grid0[54 + i] - s_grid0[54 + i];
			if (ir < 0) return;
			if (ir > 0) { go_back = 2; return; }//failed
		}
		vcdesc_e.rank = R;
		//cout << "seen ok" << endl;
		go_back = 1;
		return;
	}// end case 2
	case 1: {// search rank=stc_k1= stc_k2
		if (R > s_rank) { go_back = 1; return; }// not expected
		if (R < s_rank) { return; }// not yet ok
		memcpy(s_grid0, grid0, sizeof grid0);
		//for (int i = 0; i < 81; i++)cout << grid0[i] + 1;
		//cout << " sol for rank " << R << endl;
		DO81ItoC(grid0, vcdesc_e.g.b1);
		go_back = 1; return;
	}// end case 1


	case 0: {// store for sequential access
		if (R < stc_k1) return;// out of the search
		for (int i = 0; i < 27; i++)wtfillr4.b3[i] = grid0[54 + i] + '1';
		tfillr4[stc_stn++] = wtfillr4;
		if (R >= stc_k2) go_back = 1;
		return;
	}// end case 0


	}// end switch
}

//==========================
int VCAT::GetBandIndex() {
	for (int i = 1; i <= 416; i++)		if (b1startcat[i] >= s_rank) {
		s_band = i - 1;
		return 0; 
	}
	return -1;
}

//_____________________________  search rank => sol
int VCAT::FindSolForRank(uint64_t rank) {
	if (rank > 5472730538) return -1;
	s_rank = rank;
	if (GetBandIndex() < 0) return -1;
	s_minir4 = GetMinir4id9992(s_band, s_rank);
	if (s_minir4 < 0) return -1;
	uint32_t istartr4, iendr4;
	GetR4PointersFrom_minir4(s_minir4, s_rank_r4, istartr4, iendr4);

	//cout << "s_rank_r4=" << s_rank_r4
	//	<< " istartr4=" << istartr4 << " iendr 4="<< iendr4 << endl;


	uint64_t rk = s_rank_r4;
	for (uint32_t i = istartr4; i < iendr4; i++) {
		rk+= tr4nsol[i];
		//if (op.opcode == 11)cout << i << " " << rk << endl;
		if (rk >= s_rank) {
			s_r4_index = i;
			s_r4start=rk- tr4nsol[i];
			return 0;
		}
	}
	return -1;
};
void VCAT::GoSolForRank() {
	//cout << s_rank << " status GoSolForRank band " << s_band		
	//<< " ir4=" << s_r4_index << " rk=" << s_r4start  << endl;
	stc_rkr4_1 = s_r4start;
	stc_k1 = s_rank;
	vcat.InitBand1(s_band);
	//p_cpt2g[5] = s_r4start;
	InitRow4FromI10375(tr4u[s_r4_index]);
	//for (int i = 0; i < 36; i++) cout << grid0[i] + 1;
	//  cout << endl;
	GoRow5();
	
}
//_____________________________ virtual file
int VCAT::GetNext() {
	//cout << " getnext ncur stn " << stc_ncur << " " << stc_stn << endl;
	if (stc_ncur < stc_stn) {// take out of the table
		vcdesc_e.rank = stc_kst + stc_ncur+1;
		memcpy(vcdesc_e.g.rx, &tfillr4[stc_ncur++], 45);
		return 0;
	}
	if (stc_4cur == stc_4end) {// end of file
		stc_end = 1;	return -1;	}
	stc_4cur++; LoadR4();// use next r4
	//cout<<" band" << stc_bandid << " r4="<< stc_4cur
	//	<< " loadr4 back stc-stn=" << stc_stn << endl;
	if(!stc_stn) {// end of file or bug
		stc_end = 1;	return -1;	}
	// first of the new r4
	stc_ncur=0;
	vcdesc_e.rank = stc_kst + stc_ncur+1;// 1_5472730538
	memcpy(vcdesc_e.g.rx, &tfillr4[stc_ncur++], 45);
	return 0;
}
void VCAT::LoadR4() {// entry new r4
	//cout << " entry load " << stc_4cur << " " << stc_4st <<" " << stc_4end << endl;
	stc_kst += stc_stn;
	stc_stn = go_back = 0;
	if (stc_4cur < stc_4st) return;// bug
	if (stc_4cur > stc_4end) return;// end
	// next r4 ranks
	stc_rkr4_1 = stc_rkr4_2;// is end of previous one
	stc_rkr4_2 += tr4nsol[stc_4cur];// nex first rank for next r4
	//cout << " go  load kx " << stc_rkr4_1 <<  " "<< stc_rkr4_2 
	//	<< " " << stc_kst <<" "<< stc_kend << endl;
	// next r4 used ranks
	if (stc_rkr4_2 < stc_kst) return;// bug 
	if (stc_rkr4_1 > stc_kend) return;// bug 
	if (stc_rkr4_1 < stc_kst)stc_k1 = stc_kst;
	else stc_k1 = stc_rkr4_1;
	if (stc_rkr4_2 < stc_kend)stc_k2 = stc_rkr4_2;
	else stc_k2 = stc_kend;
	//cout << stc_4cur << " check changed band stc_bandid= "<< stc_bandid
		//<< " " << b1r4[stc_bandid] << " " << b1r4[stc_bandid+1]
		//<< " stc_band_endr4 " << stc_band_endr4 << endl;

	// changed band ??
	//cout << "test change "<< stc_4cur<<" "<< (stc_band_endr4 - 1) << endl;
	if (stc_4cur == stc_band_endr4) {// new band active
		//cout << "test while " << ((int)b1r4[stc_bandid + 1]) << " " << (stc_4cur ) << endl;
		while ((int)b1r4[stc_bandid + 1] <= stc_4cur )stc_bandid++;
		//cout << " exit while stc_bandid " << stc_bandid << endl;

		stc_band_endr4 = b1r4[stc_bandid + 1];
		InitBand1(stc_bandid);
	}
	// load r4
	//cout << " start load  stc_bandid " << stc_bandid << endl;
	InitRow4FromI10375(tr4u[stc_4cur]);
	for (int i = 0; i < 27; i++)vcdesc_e.g.b1[i] = grid0[i] + '1';
	for (int i = 0; i < 9; i++)vcdesc_e.g.r4[i] = grid0[i+27] + '1';
	go_back = 0;
	//cout << " go load stc_4cur "<< stc_4cur << endl;
	GoRow5();
	//cout << "back nload= "<< stc_stn << " stc_end?? " << stc_end << endl;


	stc_ncur = 0;
}
void VCAT::OpenBands(int ib1, int ib2) {
	//cout << "open entry" << endl;
	stc_end= outmode=0;// open virtual file
	if (ib1 < 0 || ib2>415 || ib1 > ib2) {
		stc_end = 1; return;} // not correct close
	//cout << "open go " << ib1 << " " << ib2 << endl;
	stc_kst = stc_rkr4_2 =b1startcat[ib1];
	stc_kend = b1startcat[ib2 + 1];
	//cout << "open k= " << stc_kst << " " << stc_kend << endl;

	if(stc_kst== stc_kend){ stc_end = 1; return; }// empty
	stc_bandid = ib1 - 1; //dummy for the first load
	stc_band_endr4 = stc_4cur= stc_4st=b1r4[ib1];// dummy  forcing new band
	stc_4end= b1r4[ib2 + 1];
	//cout << "open call load" << endl;
	LoadR4();
	//stc_ncur = -1; //dummy for first get next
	// note never empty using  a valid R4
}
//________________________  searh sol => rank
int VCAT::FindRankForSolMin() {
	//cout << " entry find rank" << endl;
	if (outmode !=2) return -1;// not the right process
	BANDPERM perm_ret;
	SkbGetMappingInt(s_grid0, &perm_ret);
	if ((s_band = perm_ret.i416) < 0) return -1;
	s_minir4 = GetMinir4id9992(s_band, &s_grid0[27]);
	if (s_minir4 < 0)return -1;
	BuildVr4();
	s_r4_index = GetRow4tIndex(s_vr4);
	if (s_r4_index < 0)return -1;
	//cout << " builvr4 " << s_vr4<<endl
	//	 << " minindex" <<row4t[s_r4_index]<< endl;
	uint32_t istartr4, iendr4;
	//cout << " get pointers" << endl;
	GetR4PointersFrom_minir4(s_minir4, s_rank_r4, istartr4, iendr4);
	uint64_t rk = s_rank_r4;
	for (uint32_t i = istartr4; i < iendr4; i++) {
		rk += tr4nsol[i];
		if (tr4u[i] == s_r4_index) {
			s_rank = 0;// it is a searched rank
			s_r4start = rk - tr4nsol[i];
			return 0;
		}
	}
	//cout << " exit not ok" << endl;
	return -1;
}
void VCAT::GoSolForSearchRank() {
	//cout << s_rank << " status GoSolForSearch Rank band " << s_band
	//	<< " ir4=" << s_r4_index << " rk=" << s_r4start << endl;
	//p_cpt2g[5] = s_r4start;
	vcat.InitBand1(s_band);
	//p_cpt2g[5] = s_r4start;
	InitRow4FromI10375(s_r4_index);
//	for (int i = 0; i < 36; i++) cout << grid0[i] + 1;
//	cout << " grid0" << endl;
//	for (int i = 0; i < 81; i++) cout << s_grid0[i] + 1;
//	cout<< " s_grid0" << endl;
	stc_rkr4_1 = s_r4start;
	GoRow5();
}



extern "C" __declspec(dllexport) int  SkvcatSetModeGetVCDESK(int mode, VCDESC** pe);
extern "C" __declspec(dllexport) int  SkvcatSetChangeMode(int mode);

extern "C" __declspec(dllexport) int SkvcatFinSolForRank(uint64_t rank);
extern "C" __declspec(dllexport) uint64_t SkvcatGetRankFromSolMin(int * sgiven);

extern "C" __declspec(dllexport) uint64_t SkvcatGetRankFromSolNotMin(int* sgiven, int* sback);
extern "C" __declspec(dllexport) uint64_t SkvcatGetRankFromSolCharMin(char* sgiven);
extern "C" __declspec(dllexport) uint64_t SkvcatGetRankFromSolCharNotMin(char* sgiven, int* sback);

extern "C" __declspec(dllexport) int SkvOpennBands(int ib1, int ib2);
extern "C" __declspec(dllexport) int SkvGetNext();

extern "C" __declspec(dllexport) int skvcatIsVali81(char* z);



//==========  call to get rank of a given solution grid
int  SkvcatSetModeGetVCDESK(int mode, VCDESC** pe) {
	if (mode < 0 || mode>2)return -1;
	vcat.outmode = mode;
	*pe = &vcdesc_e;
	return 0;
}
int  SkvcatSetChangeMode(int mode) {
	if (mode < 0 || mode>2)return -1;
	vcat.outmode = mode;
	return 0;
}

int SkvcatFinSolForRank(uint64_t rank) {
	if (vcat.outmode < 0) return -1;
	vcat.outmode = 1; // be sure to have the right mode
	if( vcat.FindSolForRank(rank)) return -2;// not valid rank
	vcat.GoSolForRank();
	return 0;
}

uint64_t SkvcatGetRankFromSolMin(int * sgiven) {
	vcdesc_e.rank = 0;// set return to fail
	if (vcat.outmode < 0) return 0;// undefined process
	vcat.outmode = 2; // be sure to have the right mode
	memcpy(vcat.s_grid0, sgiven, sizeof vcat.s_grid0);
	if (vcat.FindRankForSolMin() < 0) {
		//cout << " bug FindRankForSolMin" << endl;
		return 0;
	}
	vcat.GoSolForSearchRank();
	return vcdesc_e.rank;
}
uint64_t SkvcatGetRankFromSolNotMin(int* sgiven, int* sback) {
	if (vcat.outmode < 0) return -1;// undefined process
	SkbsGetMin(sgiven, sback);
	return SkvcatGetRankFromSolMin(sback);
}

uint64_t SkvcatGetRankFromSolCharMin(char* sgiven) {
	int g[81];
	for (int i = 0; i < 81; i++)g[i] = sgiven[i] - '1';
	return SkvcatGetRankFromSolMin(g);
}
uint64_t SkvcatGetRankFromSolCharNotMin(char* sgiven, int* sback) {
	SkbsGetMinChar(sgiven, sback);
	return SkvcatGetRankFromSolMin(sback);
}

int SkvGetNext() {
	if (vcat.stc_end) return -1;
	vcat.outmode = 0; // be sure to have the right mode
	return vcat.GetNext();
}
int SkvOpennBands(int ib1, int ib2) {
	if (vcat.outmode < 0) return 1;// undefined process
	vcat.outmode = 0; // be sure to have the right mode
	vcat.OpenBands(ib1, ib2);
	return vcat.stc_end;
}



//=====================  check valid sol
int cellsInGroup[27][9] =
{
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8},{ 9,10,11,12,13,14,15,16,17},{18,19,20,21,22,23,24,25,26},
	{27,28,29,30,31,32,33,34,35},{36,37,38,39,40,41,42,43,44},{45,46,47,48,49,50,51,52,53},
	{54,55,56,57,58,59,60,61,62},{63,64,65,66,67,68,69,70,71},{72,73,74,75,76,77,78,79,80},
	{ 0, 9,18,27,36,45,54,63,72},{ 1,10,19,28,37,46,55,64,73},{ 2,11,20,29,38,47,56,65,74},
	{ 3,12,21,30,39,48,57,66,75},{ 4,13,22,31,40,49,58,67,76},{ 5,14,23,32,41,50,59,68,77},
	{ 6,15,24,33,42,51,60,69,78},{ 7,16,25,34,43,52,61,70,79},{ 8,17,26,35,44,53,62,71,80},
	{ 0, 1, 2, 9,10,11,18,19,20},{ 3, 4, 5,12,13,14,21,22,23},{ 6, 7, 8,15,16,17,24,25,26},
	{27,28,29,36,37,38,45,46,47},{30,31,32,39,40,41,48,49,50},{33,34,35,42,43,44,51,52,53},
	{54,55,56,63,64,65,72,73,74},{57,58,59,66,67,68,75,76,77},{60,61,62,69,70,71,78,79,80}
};

int skvcatIsVali81(char* z) {
	int g[81];
	for (int i = 0; i < 81; i++) {
		char c = z[i];
		if (c < '1' || c>'9') return 0;
		g[i] = c-'1';
	}
	for (int i1 = 0; i1 < 27; i1++) {// r,c,b
		register int r = 0,*tc= cellsInGroup[i1];
		for (int i2 = 0; i2 < 9; i2++) // cells
			r |= 1 << g[tc[i2]];
		if (r != 0777) return 0;
	}
	return 1;
}