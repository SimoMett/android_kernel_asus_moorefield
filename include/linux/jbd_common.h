#ifndef _LINUX_JBD_STATE_H
#define _LINUX_JBD_STATE_H

#include <linux/bit_spinlock.h>

enum jbd_state_bits {
    BH_JBD			/* Has an attached ext3 journal_head */
    = BH_PrivateStart,
    BH_JWrite,		/* Being written to log (@@@ DEBUGGING) */
    BH_Freed,		/* Has been freed (truncated) */
    BH_Revoked,		/* Has been revoked from the log */
    BH_RevokeValid,		/* Revoked flag is valid */
    BH_JBDDirty,		/* Is dirty but journaled */
    BH_State,		/* Pins most journal_head state */
    BH_JournalHead,		/* Pins bh->b_private and jh->b_bh */
    BH_Unshadow,		/* IO on shadow buffer is running */
    BH_Verified,		/* Metadata block has been verified ok */
    BH_JBDPrivateStart,	/* First bit available for private use by FS */
};
#define BH_Shadow BH_Unshadow

static inline struct buffer_head *jh2bh(struct journal_head *jh)
{
	return jh->b_bh;
}

static inline struct journal_head *bh2jh(struct buffer_head *bh)
{
	return bh->b_private;
}

static inline void jbd_lock_bh_state(struct buffer_head *bh)
{
	bit_spin_lock(BH_State, &bh->b_state);
}

static inline int jbd_trylock_bh_state(struct buffer_head *bh)
{
	return bit_spin_trylock(BH_State, &bh->b_state);
}

static inline int jbd_is_locked_bh_state(struct buffer_head *bh)
{
	return bit_spin_is_locked(BH_State, &bh->b_state);
}

static inline void jbd_unlock_bh_state(struct buffer_head *bh)
{
	bit_spin_unlock(BH_State, &bh->b_state);
}

static inline void jbd_lock_bh_journal_head(struct buffer_head *bh)
{
	bit_spin_lock(BH_JournalHead, &bh->b_state);
}

static inline void jbd_unlock_bh_journal_head(struct buffer_head *bh)
{
	bit_spin_unlock(BH_JournalHead, &bh->b_state);
}

#endif
