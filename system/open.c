/* open.c - open */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  open  -  Open a device (some devices ignore name and mode parameters)
 *------------------------------------------------------------------------
 */
syscall	open(
	  did32		descrp,		/* Descriptor for device	*/
	  char		*name,		/* Name to use, if any		*/
	  char		*mode		/* Mode for device, if any	*/
	)
{
	intmask		mask;		/* Saved interrupt mask		*/
	struct dentry	*devptr;	/* Entry in device switch table	*/
	int32		retval;		/* Value to return to caller	*/

	mask = disable();
	if (isbaddev(descrp)) {
		restore(mask);
		return SYSERR;
	}
	devptr = (struct dentry *) &devtab[descrp];
	retval = (*devptr->dvopen) (devptr, name, mode);
	
	pid32 pid = getpid();
	if (isbadpid(pid) || (pid == NULLPROC)) {
		restore(mask);
		return SYSERR;
	}
	struct procent  *procTemp = &proctab[pid];
	int i=0;
	for(i=0;i<procTemp->prdescNum;i++){
		if(procTemp->prdesc[i]==-1){
			procTemp->prdesc[i] = descrp;		
			restore(mask);
			return retval;
		}
	}
	if(i==NDESC){
		restore(mask);
		return SYSERR;
	}
	procTemp->prdesc[procTemp->prdescNum++] = descrp;
	restore(mask);
	return retval;
}
