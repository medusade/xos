########################################################################
# Copyright (c) 1988-2015 $organization$
#
# This software is provided by the author and contributors ``as is''
# and any express or implied warranties, including, but not limited to,
# the implied warranties of merchantability and fitness for a particular
# purpose are disclaimed. In no event shall the author or contributors
# be liable for any direct, indirect, incidental, special, exemplary,
# or consequential damages (including, but not limited to, procurement
# of substitute goods or services; loss of use, data, or profits; or
# business interruption) however caused and on any theory of liability,
# whether in contract, strict liability, or tort (including negligence
# or otherwise) arising in any way out of the use of this software,
# even if advised of the possibility of such damage.
#
#   File: libmpz.pri
#
# Author: $author$
#   Date: 4/23/2015
########################################################################

libmpz_INCLUDEPATH += \
$${mp_INCLUDEPATH} \

libmpz_DEFINES += \
$${mp_DEFINES} \
_NO_INLINES \

libmpz_HEADERS += \

libmpz_SOURCES += \
$${mp_SRC}/mpz/abs.c \
$${mp_SRC}/mpz/add.c \
$${mp_SRC}/mpz/add_ui.c \
$${mp_SRC}/mpz/and.c \
$${mp_SRC}/mpz/array_init.c \
$${mp_SRC}/mpz/cdiv_q.c \
$${mp_SRC}/mpz/cdiv_q_ui.c \
$${mp_SRC}/mpz/cdiv_qr.c \
$${mp_SRC}/mpz/cdiv_qr_ui.c \
$${mp_SRC}/mpz/cdiv_r.c \
$${mp_SRC}/mpz/cdiv_r_ui.c \
$${mp_SRC}/mpz/cdiv_ui.c \
$${mp_SRC}/mpz/clear.c \
$${mp_SRC}/mpz/clrbit.c \
$${mp_SRC}/mpz/cmp.c \
$${mp_SRC}/mpz/cmp_si.c \
$${mp_SRC}/mpz/cmp_ui.c \
$${mp_SRC}/mpz/com.c \
$${mp_SRC}/mpz/divexact.c \
$${mp_SRC}/mpz/fac_ui.c \
$${mp_SRC}/mpz/fdiv_q.c \
$${mp_SRC}/mpz/fdiv_q_2exp.c \
$${mp_SRC}/mpz/fdiv_q_ui.c \
$${mp_SRC}/mpz/fdiv_qr.c \
$${mp_SRC}/mpz/fdiv_qr_ui.c \
$${mp_SRC}/mpz/fdiv_r.c \
$${mp_SRC}/mpz/fdiv_r_2exp.c \
$${mp_SRC}/mpz/fdiv_r_ui.c \
$${mp_SRC}/mpz/fdiv_ui.c \
$${mp_SRC}/mpz/gcd.c \
$${mp_SRC}/mpz/gcd_ui.c \
$${mp_SRC}/mpz/gcdext.c \
$${mp_SRC}/mpz/get_d.c \
$${mp_SRC}/mpz/get_si.c \
$${mp_SRC}/mpz/get_str.c \
$${mp_SRC}/mpz/get_ui.c \
$${mp_SRC}/mpz/getbit.c \
$${mp_SRC}/mpz/getlimbn.c \
$${mp_SRC}/mpz/hamdist.c \
$${mp_SRC}/mpz/init.c \
$${mp_SRC}/mpz/inp_raw.c \
$${mp_SRC}/mpz/inp_str.c \
$${mp_SRC}/mpz/invert.c \
$${mp_SRC}/mpz/ior.c \
$${mp_SRC}/mpz/iset.c \
$${mp_SRC}/mpz/iset_d.c \
$${mp_SRC}/mpz/iset_si.c \
$${mp_SRC}/mpz/iset_str.c \
$${mp_SRC}/mpz/iset_ui.c \
$${mp_SRC}/mpz/jacobi.c \
$${mp_SRC}/mpz/legendre.c \
$${mp_SRC}/mpz/mod.c \
$${mp_SRC}/mpz/mod_inverse.c \
$${mp_SRC}/mpz_msb.c \
$${mp_SRC}/mpz/mul.c \
$${mp_SRC}/mpz/mul_2exp.c \
$${mp_SRC}/mpz/mul_ui.c \
$${mp_SRC}/mpz/neg.c \
$${mp_SRC}/mpz/out_raw.c \
$${mp_SRC}/mpz/out_str.c \
$${mp_SRC}/mpz/perfsqr.c \
$${mp_SRC}/mpz/popcount.c \
$${mp_SRC}/mpz/pow_ui.c \
$${mp_SRC}/mpz/powm.c \
$${mp_SRC}/mpz/powm_ui.c \
$${mp_SRC}/mpz/pprime_p.c \
$${mp_SRC}/mpz/random.c \
$${mp_SRC}/mpz/random2.c \
$${mp_SRC}/mpz/realloc.c \
$${mp_SRC}/mpz/scan0.c \
$${mp_SRC}/mpz/scan1.c \
$${mp_SRC}/mpz/set.c \
$${mp_SRC}/mpz/set_d.c \
$${mp_SRC}/mpz/set_f.c \
$${mp_SRC}/mpz/set_q.c \
$${mp_SRC}/mpz/set_si.c \
$${mp_SRC}/mpz/set_str.c \
$${mp_SRC}/mpz/set_ui.c \
$${mp_SRC}/mpz/setbit.c \
$${mp_SRC}/mpz/size.c \
$${mp_SRC}/mpz/sizeinbase.c \
$${mp_SRC}/mpz/sqrt.c \
$${mp_SRC}/mpz/sqrtrem.c \
$${mp_SRC}/mpz/sub.c \
$${mp_SRC}/mpz/sub_ui.c \
$${mp_SRC}/mpz/tdiv_q.c \
$${mp_SRC}/mpz/tdiv_q_2exp.c \
$${mp_SRC}/mpz/tdiv_q_ui.c \
$${mp_SRC}/mpz/tdiv_qr.c \
$${mp_SRC}/mpz/tdiv_qr_ui.c \
$${mp_SRC}/mpz/tdiv_r.c \
$${mp_SRC}/mpz/tdiv_r_2exp.c \
$${mp_SRC}/mpz/tdiv_r_ui.c \
$${mp_SRC}/mpz/ui_pow_ui.c \

libmpz_LIBS += \
