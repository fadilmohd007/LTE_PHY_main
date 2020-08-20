#include <stdio.h>
#include "./Reference_signal/cell_specific_ref.h"
#include "./PBCH/pbch.h"
#include "./global_vars.h"
#include <stdint.h>

int main() {
	//dynamic variables
	gsl_complex* lte_frame;
	gsl_complex* ref_sigs;

	//iterators
	int i, j, sf; //sf = subframe

	//flags
	int ref_signal_gereated = 0;


	//testing
	//initialized lte params
	int CP = 1;
	int n_RB = 100;
	int n_antennaports = 1;
	int nCellId = 404;
	int nBytes = 4;
	uint8_t message[7];
	message[0] = 0xB8;
	message[1] = 0x1F;
	message[2] = 0x2D;
	message[3] = 0x1C;
	//crc
	//message[4] = 0x27;
	// message[5] = 0x46;
	// message[6] = 0x38;
	int n_layers = 1;
	int n_codewords = 1;
	int transmission_scheme = 0;
	int is_CDD = 0;
	int code_bookindex = 0;
	int modulation_scheme = 0;
	/**
	 *
	 * lte_frame visualization
	 * (n_RB-1,0),(n_RB-1,1),(n_RB-1,2).... [14/12 - based on CP] 	| (n_RB-1,0),(n_RB-1,1),(n_RB-1,2).... [14/12 - based on CP] 	|
	 * (n_RB-2,0),(n_RB-2,1),(n_RB-2,2).... [14/12 - based on CP]	|																|
	 * (n_RB-3,0),(n_RB-3,1),(n_RB-3,2).... [14/12 - based on CP] 	|																|
	 * .															|																|
	 * .															|																|
	 * .															|																|
	 * .															|																|
	 * (0,0),      (0,1),    (0,2).... [14/12 - based on CP]		| * (0,0),      (0,1),    (0,2).... [14/12 - based on CP]		|
	 *-----------------------------sf-0------------------------------------------------------------sf-1-------------------------------
	 */

	if (CP == 1) { //noraml CP
		lte_frame = (gsl_complex *) calloc(n_antennaports * 14 * n_RB * 12 * 10, sizeof(gsl_complex));
	}
	else if (CP == 0) { //Extended CP
		lte_frame = (gsl_complex *) calloc(n_antennaports * 12 * n_RB * 12 * 10, sizeof(gsl_complex));
	}
	for (i = 0; i < n_antennaports * 12 * n_RB * 12 * 10; i++) {
		GSL_SET_COMPLEX(&lte_frame[i], 0, 0);
	}

	for (sf = 0 ; sf < 10 ; sf++) {
		printf("FOR sf %d\n", sf );
		ref_sigs = reference_sig_genrator( nCellId ,  CP,  n_antennaports,  ref_sigs, sf);
		lte_frame = re_mapping_cell_specific_ref(  nCellId, CP,  n_RB,  lte_frame,   ref_sigs, n_antennaports, sf) ;
	}
	free(ref_sigs);

	pbch_main(nBytes, message, nCellId, n_layers , n_codewords,  modulation_scheme, transmission_scheme,  is_CDD ,  n_antennaports,  code_bookindex , lte_frame, n_RB, CP);
	free(lte_frame);
	return 0;
}