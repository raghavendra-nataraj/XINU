/* close.c - close */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  close  -  Close a device
 *------------------------------------------------------------------------
 */
syscall	close(
	  did32		descrp		/* Descriptor for device	*/
	)
{
	intmask		mask;		/* Saved interrupt mask		*/
	struct	dentry	*devptr;	/* Entry in device switch table	*/
	int32		retval;		/* Value to return to caller	*/

	mask = disable();
	if (isbaddev(descrp)) {
		restore(mask);
		return SYSERR;
	}
	pid32 pid = getpid();
	if (isbadpid(pid) || (pid == NULLPROC)) {
		restore(mask);
		return SYSERR;
	}
	struct procent  *procTemp = &proctab[pid];
	int i=0;
	for(i=0;i<procTemp->prdescNum;i++){
		if(procTemp->prdesc[i]==descrp){
			procTemp->prdesc[i] = -1;		
			break;
		}
	}
	devptr = (struct dentry *) &devtab[descrp];
	retval = (*devptr->dvclose) (devptr);
	restore(mask);
	return retval;
}
