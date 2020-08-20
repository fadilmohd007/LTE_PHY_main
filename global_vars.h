#define n_RB_max 110
#define getbit(byte,nbit)   ((int) (byte >> nbit ) & 1)
#define E  1920

/*
 * Macro: get_lte_frame_pos
 * ----------------------------
 *   Returns an integer corresponding to the lte_frame position for inputs 
 *
 *
 *   n_slot     			int (slot number 0 to 19)
 *   n_DL_SYM          		int(7 or 6 based on CP)
 *   k						int(freq domain)
 *	 l 		    			int (symbol 0 to 6/7)
 * 	 p 						int(antenna port)
 *
 *   returns: position in the single dimension array of lte_frame
 */
#define get_lte_frame_pos(n_slot, n_DL_SYM, k, l, p ) (l + (n_slot * n_DL_SYM) + (k * 10 * 2 * n_DL_SYM)  + (p * 2 * n_DL_SYM * 10 * n_RB * 12))