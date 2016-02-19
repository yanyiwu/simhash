#ifndef SIMHASH_HASHES_JENKINS_H
#define SIMHASH_HASHES_JENKINS_H

/* This code was taken from http://www.burtleburtle.net/bob/c/lookup3.c, and
 * under a public domain licence on May 25, 2012, reproduced below:
 * -----------------------------------------------------------------------------
 * lookup3.c, by Bob Jenkins, May 2006, Public Domain.
 * 
 * These are functions for producing 32-bit hashes for hash table lookup.
 * hashword(), hashlittle(), hashlittle2(), hashbig(), mix(), and final() 
 * are externally useful functions.  Routines to test the hash are included 
 * if SELF_TEST is defined.  You can use this free for any purpose.  It's in
 * the public domain.  It has no warranty.
 * 
 * You probably want to use hashlittle().  hashlittle() and hashbig()
 * hash byte arrays.  hashlittle() is is faster than hashbig() on
 * little-endian machines.  Intel and AMD are little-endian machines.
 * On second thought, you probably want hashlittle2(), which is identical to
 * hashlittle() except it returns two 32-bit hashes for the price of one.  
 * You could implement hashbig2() if you wanted but I haven't bothered here.
 * 
 * If you want to find a hash of, say, exactly 7 integers, do
 * a = i1;  b = i2;  c = i3;
 * mix(a,b,c);
 * a += i4; b += i5; c += i6;
 * mix(a,b,c);
 * a += i7;
 * final(a,b,c);
 * then use c as the hash value.  If you have a variable length array of
 * 4-byte integers to hash, use hashword().  If you have a byte array (like
 * a character string), use hashlittle().  If you have several byte arrays, or
 * a mix of things, see the comments above hashlittle().  
 * 
 * Why is this so big?  I read 12 bytes at a time into 3 4-byte integers, 
 * then mix those integers.  This is fast (you can do a lot more thorough
 * mixing with 12*3 instructions on 3 integers than you can with 3 instructions
 * on 1 byte), but shoehorning those bytes into integers efficiently is messy.
 * -----------------------------------------------------------------------------
 */

#include <cstring>      /* defined size_t */
#include <stdint.h>     /* defines uint32_t etc */
#include <sys/param.h>  /* attempt to define endianness */
#ifdef linux
# include <endian.h>    /* attempt to define endianness */
#endif

#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))

#define mix(a,b,c) \
{ \
  a -= c;  a ^= rot(c, 4);  c += b; \
  b -= a;  b ^= rot(a, 6);  a += c; \
  c -= b;  c ^= rot(b, 8);  b += a; \
  a -= c;  a ^= rot(c,16);  c += b; \
  b -= a;  b ^= rot(a,19);  a += c; \
  c -= b;  c ^= rot(b, 4);  b += a; \
}

#define final(a,b,c) \
{ \
  c ^= b; c -= rot(b,14); \
  a ^= c; a -= rot(c,11); \
  b ^= a; b -= rot(a,25); \
  c ^= b; c -= rot(b,16); \
  a ^= c; a -= rot(c,4);  \
  b ^= a; b -= rot(a,14); \
  c ^= b; c -= rot(b,24); \
}

/*
 * My best guess at if you are big-endian or little-endian.  This may
 * need adjustment.
 */
#if (defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && \
     __BYTE_ORDER == __LITTLE_ENDIAN) || \
    (defined(i386) || defined(__i386__) || defined(__i486__) || \
     defined(__i586__) || defined(__i686__) || defined(vax) || defined(MIPSEL))
# define HASH_LITTLE_ENDIAN 1
# define HASH_BIG_ENDIAN 0
#elif (defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && \
       __BYTE_ORDER == __BIG_ENDIAN) || \
      (defined(sparc) || defined(POWERPC) || defined(mc68000) || defined(sel))
# define HASH_LITTLE_ENDIAN 0
# define HASH_BIG_ENDIAN 1
#else
# define HASH_LITTLE_ENDIAN 0
# define HASH_BIG_ENDIAN 0
#endif

//#warning "Jenkins"


#include <iostream>

namespace simhash {
	struct jenkins {
		uint64_t operator()(const char* data, size_t len, uint64_t s) const {
			uint32_t a = static_cast<uint32_t>(s >> 32);
			uint32_t b = static_cast<uint32_t>(s & 0xffffffff);
			hashlittle2(static_cast<void*>(const_cast<char*>(data)),
				len, &a, &b);
			return (static_cast<uint64_t>(a) << 32) | static_cast<uint64_t>(b);
		}

		/*
		 * hashlittle2: return 2 32-bit hash values
		 *
		 * This is identical to hashlittle(), except it returns two 32-bit hash
		 * values instead of just one.  This is good enough for hash table
		 * lookup with 2^^64 buckets, or if you want a second hash if you're 
		 * not happy with the first, or if you want a probably-unique 64-bit 
		 * ID for the key.  *pc is better mixed than *pb, so use *pc first.  
		 * If you want a 64-bit value do something like:
		 *     "*pc + (((uint64_t)*pb) <<32)".
		 */
		void hashlittle2(
		    const void *key,         /* the key to hash */
		    size_t      length,      /* length of the key */
		    uint32_t   *pc,          // IN: primary initval, OUT: primary hash 
		    uint32_t   *pb) const {  // IN: secondary initval, OUT: secondary 
			uint32_t a,b,c;      /* internal state */

			union { const void *ptr; size_t i; } u;     /* needed for Mac Powerbook G4 */

			/* Set up the internal state */
			a = b = c = 0xdeadbeef + ((uint32_t)length) + *pc;
			c += *pb;

			u.ptr = key;
			if (HASH_LITTLE_ENDIAN && ((u.i & 0x3) == 0)) {
				const uint32_t *k = (const uint32_t *)key;         /* read 32-bit chunks */
#ifdef VALGRIND
				const uint8_t  *k8;
#endif

				/*------ all but last block: aligned reads and affect 32 bits of (a,b,c) */
				while (length > 12) {
					a += k[0];
					b += k[1];
					c += k[2];
					mix(a,b,c);
					length -= 12;
					k += 3;
				}

			    /*----------------------------- handle the last (probably partial) block */
			    /* 
			     * "k[2]&0xffffff" actually reads beyond the end of the string, but
			     * then masks off the part it's not allowed to read.  Because the
			     * string is aligned, the masked-off tail is in the same word as the
			     * rest of the string.  Every machine with memory protection I've seen
			     * does it on word boundaries, so is OK with this.  But VALGRIND will
			     * still catch it and complain.  The masking trick does make the hash
			     * noticably faster for short strings (like English words).
			     */
#ifndef VALGRIND
			    switch(length) {
				    case 12: c+=k[2]; b+=k[1]; a+=k[0]; break;
				    case 11: c+=k[2]&0xffffff; b+=k[1]; a+=k[0]; break;
				    case 10: c+=k[2]&0xffff; b+=k[1]; a+=k[0]; break;
				    case 9 : c+=k[2]&0xff; b+=k[1]; a+=k[0]; break;
				    case 8 : b+=k[1]; a+=k[0]; break;
				    case 7 : b+=k[1]&0xffffff; a+=k[0]; break;
				    case 6 : b+=k[1]&0xffff; a+=k[0]; break;
				    case 5 : b+=k[1]&0xff; a+=k[0]; break;
				    case 4 : a+=k[0]; break;
				    case 3 : a+=k[0]&0xffffff; break;
				    case 2 : a+=k[0]&0xffff; break;
				    case 1 : a+=k[0]&0xff; break;
				    case 0 : *pc=c; *pb=b; return;  /* zero length strings require no mixing */
			    }
#else /* make valgrind happy */
			    k8 = (const uint8_t *)k;
			    switch(length) {
				    case 12: c+=k[2]; b+=k[1]; a+=k[0]; break;
				    case 11: c+=((uint32_t)k8[10])<<16;  /* fall through */
				    case 10: c+=((uint32_t)k8[9])<<8;    /* fall through */
				    case 9 : c+=k8[8];                   /* fall through */
				    case 8 : b+=k[1]; a+=k[0]; break;
				    case 7 : b+=((uint32_t)k8[6])<<16;   /* fall through */
				    case 6 : b+=((uint32_t)k8[5])<<8;    /* fall through */
				    case 5 : b+=k8[4];                   /* fall through */
				    case 4 : a+=k[0]; break;
				    case 3 : a+=((uint32_t)k8[2])<<16;   /* fall through */
				    case 2 : a+=((uint32_t)k8[1])<<8;    /* fall through */
				    case 1 : a+=k8[0]; break;
				    case 0 : *pc=c; *pb=b; return;  /* zero length strings require no mixing */
			    }
#endif /* !valgrind */
			} else if (HASH_LITTLE_ENDIAN && ((u.i & 0x1) == 0)) {
				const uint16_t *k = (const uint16_t *)key;         /* read 16-bit chunks */
				const uint8_t  *k8;
			    /*--------------- all but last block: aligned reads and different mixing */
			    while (length > 12) {
					a += k[0] + (((uint32_t)k[1])<<16);
					b += k[2] + (((uint32_t)k[3])<<16);
					c += k[4] + (((uint32_t)k[5])<<16);
					mix(a,b,c);
					length -= 12;
					k += 6;
			    }

			    /*----------------------------- handle the last (probably partial) block */
			    k8 = (const uint8_t *)k;
			    switch(length) {
			    case 12: c+=k[4]+(((uint32_t)k[5])<<16);
			             b+=k[2]+(((uint32_t)k[3])<<16);
			             a+=k[0]+(((uint32_t)k[1])<<16);
			             break;
			    case 11: c+=((uint32_t)k8[10])<<16;     /* fall through */
			    case 10: c+=k[4];
			             b+=k[2]+(((uint32_t)k[3])<<16);
			             a+=k[0]+(((uint32_t)k[1])<<16);
			             break;
			    case 9 : c+=k8[8];                      /* fall through */
			    case 8 : b+=k[2]+(((uint32_t)k[3])<<16);
			             a+=k[0]+(((uint32_t)k[1])<<16);
			             break;
			    case 7 : b+=((uint32_t)k8[6])<<16;      /* fall through */
			    case 6 : b+=k[2];
			             a+=k[0]+(((uint32_t)k[1])<<16);
			             break;
			    case 5 : b+=k8[4];                      /* fall through */
			    case 4 : a+=k[0]+(((uint32_t)k[1])<<16);
			             break;
			    case 3 : a+=((uint32_t)k8[2])<<16;      /* fall through */
			    case 2 : a+=k[0];
			             break;
			    case 1 : a+=k8[0];
			             break;
			    case 0 : *pc=c; *pb=b; return;  /* zero length strings require no mixing */
			    }
			} else {                        /* need to read the key one byte at a time */
			    const uint8_t *k = (const uint8_t *)key;
			    /*--------------- all but the last block: affect some 32 bits of (a,b,c) */
			    while (length > 12) {
					a += k[0];
					a += ((uint32_t)k[1])<<8;
					a += ((uint32_t)k[2])<<16;
					a += ((uint32_t)k[3])<<24;
					b += k[4];
					b += ((uint32_t)k[5])<<8;
					b += ((uint32_t)k[6])<<16;
					b += ((uint32_t)k[7])<<24;
					c += k[8];
					c += ((uint32_t)k[9])<<8;
					c += ((uint32_t)k[10])<<16;
					c += ((uint32_t)k[11])<<24;
					mix(a,b,c);
					length -= 12;
					k += 12;
			    }

			    /*-------------------------------- last block: affect all 32 bits of (c) */
			    switch(length) {                 /* all the case statements fall through */
			    case 12: c+=((uint32_t)k[11])<<24;
			    case 11: c+=((uint32_t)k[10])<<16;
			    case 10: c+=((uint32_t)k[9])<<8;
			    case 9 : c+=k[8];
			    case 8 : b+=((uint32_t)k[7])<<24;
			    case 7 : b+=((uint32_t)k[6])<<16;
			    case 6 : b+=((uint32_t)k[5])<<8;
			    case 5 : b+=k[4];
			    case 4 : a+=((uint32_t)k[3])<<24;
			    case 3 : a+=((uint32_t)k[2])<<16;
			    case 2 : a+=((uint32_t)k[1])<<8;
			    case 1 : a+=k[0];
			             break;
			    case 0 : *pc=c; *pb=b; return;  /* zero length strings require no mixing */
			    }
			}

			final(a,b,c);
			*pc=c; *pb=b;
		}
	};
}

#endif
