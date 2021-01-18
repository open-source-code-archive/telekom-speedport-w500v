ifeq ($(CC),gcc)
	GENKEY = $(HOST_GENKEY)
else
	GENKEY = $(MIPS_GENKEY)			
endif

CRYPTO_DIR=$(SSHD_DIR)/libtomcrypt
MATH_DIR=$(SSHD_DIR)/libtommath
	
CFLAGS=-Wall -W -O2 -DSSHD_GENKEY -I$(CRYPTO_DIR)
LIBS= -lcrypt -lutil

HEADERS=options.h util.h session.h packet.h algo.h ssh.h buffer.h kex.h \
    dss.h bignum.h signkey.h rsa.h random.h service.h auth.h authpasswd.h \
    debug.h channel.h chansession.h debug.h config.h queue.h sshpty.h \
    termcodes.h gendss.h genrsa.h authpubkey.h runopts.h includes.h \
    loginrec.h atomicio.h x11fwd.h agentfwd.h localtcpfwd.h

OBJS=util.o session.o algo.o buffer.o kex.o dss.o bignum.o \
	signkey.o random.o service.o auth.o authpasswd.o channel.o \
	queue.o sshpty.o termcodes.o authpubkey.o runopts.o \
	loginrec.o atomicio.o x11fwd.o agentfwd.o localtcpfwd.o \
	dropbearkey.o gendss.o genrsa.o chansession.o

CRYPTO_OBJS= keyring.o gf.o mem.o sprng.o ecc.o base64.o dh.o rsa.o \
	bits.o yarrow.o cfb.o ofb.o ecb.o ctr.o cbc.o hash.o tiger.o sha1.o \
	md5.o md4.o md2.o sha256.o sha512.o xtea.o aes.o des.o \
	safer_tab.o safer.o safer+.o rc4.o rc2.o rc6.o rc5.o cast5.o noekeon.o blowfish.o crypt.o \
	ampi.o prime.o twofish.o packet.o hmac.o strings.o

MATH_OBJS=bncore.o bn_mp_init.o bn_mp_clear.o bn_mp_exch.o bn_mp_grow.o bn_mp_shrink.o \
	bn_mp_clamp.o bn_mp_zero.o  bn_mp_set.o bn_mp_set_int.o bn_mp_init_size.o bn_mp_copy.o \
	bn_mp_init_copy.o bn_mp_abs.o bn_mp_neg.o bn_mp_cmp_mag.o bn_mp_cmp.o bn_mp_cmp_d.o \
	bn_mp_rshd.o bn_mp_lshd.o bn_mp_mod_2d.o bn_mp_div_2d.o bn_mp_mul_2d.o bn_mp_div_2.o \
	bn_mp_mul_2.o bn_s_mp_add.o bn_s_mp_sub.o bn_fast_s_mp_mul_digs.o bn_s_mp_mul_digs.o \
	bn_fast_s_mp_mul_high_digs.o bn_s_mp_mul_high_digs.o bn_fast_s_mp_sqr.o bn_s_mp_sqr.o \
	bn_mp_add.o bn_mp_sub.o bn_mp_karatsuba_mul.o bn_mp_mul.o bn_mp_karatsuba_sqr.o \
	bn_mp_sqr.o bn_mp_div.o bn_mp_mod.o bn_mp_add_d.o bn_mp_sub_d.o bn_mp_mul_d.o \
	bn_mp_div_d.o bn_mp_mod_d.o bn_mp_expt_d.o bn_mp_addmod.o bn_mp_submod.o \
	bn_mp_mulmod.o bn_mp_sqrmod.o bn_mp_gcd.o bn_mp_lcm.o bn_fast_mp_invmod.o bn_mp_invmod.o \
	bn_mp_reduce.o bn_mp_montgomery_setup.o bn_fast_mp_montgomery_reduce.o bn_mp_montgomery_reduce.o \
	bn_mp_exptmod_fast.o bn_mp_exptmod.o bn_mp_2expt.o bn_mp_n_root.o bn_mp_jacobi.o bn_reverse.o \
	bn_mp_count_bits.o bn_mp_read_unsigned_bin.o bn_mp_read_signed_bin.o bn_mp_to_unsigned_bin.o \
	bn_mp_to_signed_bin.o bn_mp_unsigned_bin_size.o bn_mp_signed_bin_size.o bn_radix.o \
	bn_mp_xor.o bn_mp_and.o bn_mp_or.o bn_mp_rand.o bn_mp_montgomery_calc_normalization.o \
	bn_mp_prime_is_divisible.o bn_prime_tab.o bn_mp_prime_fermat.o bn_mp_prime_miller_rabin.o \
	bn_mp_prime_is_prime.o bn_mp_prime_next_prime.o bn_mp_dr_reduce.o bn_mp_multi.o \
	bn_mp_dr_is_modulus.o bn_mp_dr_setup.o bn_mp_reduce_setup.o \
	bn_mp_toom_mul.o bn_mp_toom_sqr.o bn_mp_div_3.o bn_s_mp_exptmod.o \
	bn_mp_reduce_2k.o bn_mp_reduce_is_2k.o bn_mp_reduce_2k_setup.o

vpath %.h $(SSHD_DIR):$(CRYPTO_DIR):$(MATH_DIR)
vpath %.c $(SSHD_DIR):$(CRYPTO_DIR):$(MATH_DIR)

$(GENKEY): $(OBJS) $(CRYPTO_OBJS) $(MATH_OBJS) $(HEADERS) 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(GENKEY) $(OBJS) $(CRYPTO_OBJS) $(MATH_OBJS) $(LIBS)	
	$(STRIP) $(GENKEY)
	  
clean: 
	-rm -f $(GENKEY) *.o
