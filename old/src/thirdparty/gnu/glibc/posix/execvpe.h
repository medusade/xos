/**
 **********************************************************************
 * Copyright (c) 1988-2014 $organization$
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
 *   File: execvpe.h
 *
 * Author: $author$
 *   Date: 9/18/2014
 **********************************************************************
 */
#ifndef _EXECVPE_H
#define _EXECVPE_H

#if defined(PLATFORM_HAS_NO_EXECVPE)
#if !defined(execvpe)
#define execvpe __execvpe
#endif /* !defined(execvpe) */
#endif /* defined(PLATFORM_HAS_NO_EXECVPE) */

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

int __execvpe (const char* file, char*const argv[], char*const envp[]);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* _EXECVPE_H */
        

