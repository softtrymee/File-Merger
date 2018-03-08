/*
 * Filename: revFilenameCompare.s
 * Author: Shengkai He
 * Userid: cs30xcy
 * Description: This function will be used with qsort() to sort based on the
 *		names of two struct fileInfo, in reverse alphabetical order.
 * Date: Mar 07 2017
 * Sources of Help: NONE
 */


 	.global	revFilenameCompare

	.section ".text"

/* Function name: revFilenameCompare()
 * Function prototype: int revFilenameCompare(const void * p1, const void * p2);
 * Parameters: p1 - pointer to the first element
 *             p2 - pointer to the second element
 * Side effects: none
 * Error conditions: none
 * Return value: 1 if the first modification time is larger, 0 if same, -1
 *               if otherwise
 * Registers used: 
 *               %l0 - filenameOffset
 *               %o0 - filename1
 *               %o1 - filename2
 */

revFilenameCompare:
	save	%sp, -96, %sp

	set	filenameOffset, %l0
	ld	[%l0], %l0		! %l0 = filenameOffset

	ld	[%i0 + %l0], %o0	! %o0 = filename1
	ld	[%i1 + %l0], %o1	! %o1 = filename2

	call	strcmp
	nop

	cmp	%o0, %g0
	bl	less
	nop

	cmp	%o0, %g0
	be	equal
	nop

	mov	-1, %i0
	ba	end
	nop

less:
	mov	1, %i0
	ba	end
	nop

equal:
	mov	%g0, %i0
	
end:	
	ret
	restore

