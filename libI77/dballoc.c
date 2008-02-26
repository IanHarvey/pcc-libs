/*	$Id$	*/
/*
 * Copyright(C) Caldera International Inc. 2001-2002. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code and documentation must retain the above
 * copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditionsand the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 * 	This product includes software developed or owned by Caldera
 *	International, Inc.
 * Neither the name of Caldera International, Inc. nor the names of other
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * USE OF THE SOFTWARE PROVIDED FOR UNDER THIS LICENSE BY CALDERA
 * INTERNATIONAL, INC. AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL CALDERA INTERNATIONAL, INC. BE LIABLE
 * FOR ANY DIRECT, INDIRECT INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OFLIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */
#define debug YES
#ifndef debug
#define ASSERT(p)
#endif
#ifdef debug
#define ASSERT(p) if(!(p))botch("p");else
botch(s)
char *s;
{
	printf("assertion botched: %s\n",s);
	abort();
}
#endif
/*	C storage allocator
 *	circular first-fit strategy
 *	works with noncontiguous, but monotonically linked, arena
 *	each block is preceded by a ptr to the (pointer of) 
 *	the next following block
 *	blocks are exact number of words long; BUSY
 *	bit in ptr is 1 for busy, 0 for idle
 *	gaps in arena are merely noted as busy blocks
 *	last block of arena (pointed to by alloct) is empty and
 *	has a pointer to first
 *	idle blocks are coalesced during space search
*/
/*	all these defines must be powers of 2 */
#define WORD sizeof(struct store)
#define BLOCK 1024
#define BUSY 1
#define NULL 0
#define testbusy(p) ((int)(p)&BUSY)
#define setbusy(p) (struct store *)((int)(p)+BUSY)
#define clearbusy(p) (struct store *)((int)(p)&~BUSY)

struct store { struct store *ptr; };

struct store allocs[] = {	/*initial arena*/
	setbusy(&allocs[1].ptr),
	setbusy(&allocs[0].ptr)
};
struct store *allocp = &allocs[1];	/*search ptr*/
struct store *alloct = &allocs[1];	/*arena top*/
struct store *allocx = 0;		/*for benefit of realloc*/
struct store *sbrk();

struct store *
malloc(nbytes)
unsigned nbytes;
{
	struct store *p, *q;
	register nw;
	static temp;	/*coroutines assume no auto*/

#ifdef verbose
	printf("malloc(%d) ",nbytes);
#endif
	nw = (nbytes+2*WORD-1)/WORD;
	ASSERT(allocp>allocs && allocp<=alloct);
	for(p=allocp; ; ) {
		for(temp=0; ; ) {
			if(!testbusy(p->ptr)) {
				while(!testbusy((q=p->ptr)->ptr)) {
					ASSERT(q>p&&q<alloct);
					p->ptr = q->ptr;
				}
				if(q>=p+nw && p+nw>=p)
					goto found;
			}
			q = p;
			p = clearbusy(p->ptr);
			if(p>q)
				ASSERT(p<=alloct);
			else if(q!=alloct || p!=allocs) {
				write(2,"corrupt arena\n",14);
#ifdef debug
				abort();
#endif
				exit(0175);
			} else if(++temp>1)
				break;
		}
		temp = (nw+BLOCK/WORD)&~(BLOCK/WORD-1);
		q = sbrk(temp*WORD); /*SYSDEP*/
		if((int)q == -1)
			return(NULL);
		ASSERT(q>alloct);
		alloct->ptr = q;
		if(q!=alloct+1)
			alloct->ptr = setbusy(alloct->ptr);
		alloct = q->ptr = q+temp-1;
		alloct->ptr = setbusy(allocs);
	}
found:
	allocp = p + nw;
	ASSERT(allocp<=alloct);
	if(q>allocp) {
		allocx = allocp->ptr;
		allocp->ptr = p->ptr;
	}
	p->ptr = setbusy(allocp);
#ifdef verbose
	printf("= %o\n",p+1);
#endif
	return(p+1);
}
/*	freeing strategy tuned for LIFO allocation
*/
free(p)
 struct store *p;
{
	struct store *savep=p;
#ifdef verbose
	printf("free(%o)\n",p);
#endif
	ASSERT(p>clearbusy(allocs[1].ptr)&&p<=alloct);
	allocp = --p;
	ASSERT(testbusy(p->ptr));
	p->ptr = clearbusy(p->ptr);
	ASSERT(p->ptr > allocp && p->ptr <= alloct);
}
char *calloc(nbytes,count)
{	char *c;
	c=(char *)malloc(nbytes*count);
	return(c);
}
/*
ahist(s) char *s;
{	char **ap;
	printf("%s allocp %o alloct %o\n",s,allocp,alloct);
	for(ap= allocs;ap<alloct;ap= *ap&~BUSY)
		if(*ap&BUSY) printf("%o ",ap);
	printf("\n");
}
*/
struct store *
realloc(p, nbytes)
register struct store *p;
unsigned nbytes;
{
	register struct store *q;
	struct store *s, *t;
	register unsigned nw;
	unsigned onw;

	onw = p[-1].ptr - p;
	q = malloc(nbytes);
	if(q==NULL || q==p)
		return(q);
	s = p;
	t = q;
	nw = (nbytes+WORD-1)/WORD;
	if(nw<onw)
		onw = nw;
	while(onw--!=0)
		(t++)->ptr = (s++)->ptr;
	if(q<p && q+nw>=p)
		(q+(q+nw-p))->ptr = allocx;
	return(q);
}
