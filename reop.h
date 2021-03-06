/*
 * Copyright (c) 2014 Ted Unangst <tedu@tedunangst.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

struct reop_seckey;
struct reop_pubkey;
struct reop_sig;

struct reop_keypair {
	const struct reop_pubkey *pubkey;
	const struct reop_seckey *seckey;
};

typedef struct { int v; } kdf_allowstdin;
typedef struct { int v; } kdf_confirm;
typedef struct { int v; } opt_binary;

/* generate a keypair */
struct reop_keypair reop_generate(int rounds, const char *ident);

/* pubkey functions */
const struct reop_pubkey *reop_getpubkey(const char *pubkeyfile, const char *ident);
const struct reop_pubkey *reop_parsepubkey(const char *pubkeydata);
const char *reop_encodepubkey(const struct reop_pubkey *pubkey);
void reop_freepubkey(const struct reop_pubkey *reop_pubkey);

/* seckey functions */
const struct reop_seckey *reop_getseckey(const char *seckeyfile, kdf_allowstdin allowstdin);
const struct reop_seckey *reop_parseseckey(const char *seckeydata);
const char *reop_encodeseckey(const struct reop_seckey *seckey);
void reop_freeseckey(const struct reop_seckey *reop_seckey);

/* sign and verify */
const struct reop_sig *reop_sign(const struct reop_seckey *seckey, const uint8_t *msg,
    uint64_t msglen);
void reop_verify(const struct reop_pubkey *reop_pubkey, const uint8_t *msg, uint64_t msglen,
    const struct reop_sig *reop_sig);

/* sig functions */
const struct reop_sig *reop_parsesig(const char *sigdata);
const char *reop_encodesig(const struct reop_sig *sig);
void reop_freesig(const struct reop_sig *sig);

void reop_freestr(const char *str);

/* application code; yet to be converted */
struct pubkey;
struct symmsg;
struct encmsg;

void verifysimple(const char *pubkeyfile, const char *msgfile, const char *sigfile,
    int quiet);
void verifyembedded(const char *pubkeyfile, const char *sigfile, int quiet);

void pubencrypt(const char *pubkeyfile, const char *ident, const char *seckeyfile,
    const char *msgfile, const char *encfile, opt_binary binary);
void v1pubencrypt(const char *pubkeyfile, const char *ident, const char *seckeyfile,
    const char *msgfile, const char *encfile, opt_binary binary);
void symencrypt(const char *msgfile, const char *encfile, int rounds, opt_binary binary);
void decrypt(const char *pubkeyfile, const char *seckeyfile, const char *msgfile,
    const char *encfile);
void generate(const char *pubkeyfile, const char *seckeyfile, int rounds, const char *ident);

void signfile(const char *seckeyfile, const char *msgfile, const char *sigfile,
    int embedded);
