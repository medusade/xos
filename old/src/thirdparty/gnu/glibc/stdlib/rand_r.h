/**
 **********************************************************************
 * Copyright (c) 1988-2015 $organization$
 *
 * This software is provided by the author and contributors ``as is'' 
 * and any express or implied warranties, including, but not limited to, 
 * the implied warranties of merchantability and fitness for a particular 
 * purpose are disclaimed. In no event shall the author or contributors 
 * be liable for any direct, indirect, incidental, special, exemplary, 
 * or consequential damages (including, but not limited to, procurement 
 * of substitute goods or services; loss of use, data, or profits; or 
 * business interruption) however caused and on any theory of liability, 
 * whether in contract, strict liability, or tort (including negligence 
 * or otherwise) arising in any way out of the use of this software, 
 * even if advised of the possibility of such damage.
 *
 *   File: rand_r.h
 *
 * Author: $author$
 *   Date: 4/21/2015
 **********************************************************************
 */
#ifndef _RAND_R_H
#define _RAND_R_H

#if defined(PLATFORM_HAS_NO_RAND_R)
#if !defined(rand_r)
#define rand_r __rand_r
#endif /* !defined(rand_r) */
#endif /* defined(PLATFORM_HAS_NO_RAND_R) */

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

int __rand_r (unsigned int *seed);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* _RAND_R_H */
        

