/*
 * Filename: revTimeCompare.s
 * Author: Shengkai He
 * Userid: cs30xcy
 * Description: This function will be used with qsort() to sort based on the
 *		modification times (newest first) of two struct fileInfo
 *		(which are passed in as void pointers)
 * Date: Mar 07 2017
 * Sources of Help: NONE
 */

 	.global revTimeCompare

	.section ".text"

/* Function name: revTimeCompare()
 * Function prototype: intrevTimeCompare(const void * p1, const void * p2);
 * Parameters: p1 - pointer to the first element
 *             p2 - pointer to the second element
 * Side effects: none
 * Error conditions: none
 * Return value: 1 if the first modification time is older, 0 if same, -1
 *               if otherwise
 * Registers used: 
 *               %o2 - statOffset / finalOffset
 *               %o3 - mtimeOffset / mTime1
 *               %o4 - mTime2
 */

revTimeCompare:
	set	statOffset, %o2
	ld	[%o2], %o2		! %o2 = statOffset

	set	mtimeOffset, %o3
	ld	[%o3], %o3		! %o3 = mtimeOffset

	add	%o2, %o3, %o2		! %o2 = finalOffset

	ld	[%o0 + %o2], %o3	! %o3 = mTime1
	ld	[%o1 + %o2], %o4	! %o4 = mTime2

	cmp	%o3, %o4
	bl	smaller
	nop

	cmp	%o3, %o4
	be	equal
	nop

	mov	-1, %o0
	ba	end
	nop

smaller:
	mov	1, %o0
	ba	end
	nop

equal:
	mov	0, %o0

end:
	retl
	nop
