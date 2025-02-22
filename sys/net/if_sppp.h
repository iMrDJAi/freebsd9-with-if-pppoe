/*
 * Defines for synchronous PPP/Cisco/Frame Relay link level subroutines.
 */
/*-
 * Copyright (C) 1994-2000 Cronyx Engineering.
 * Author: Serge Vakulenko, <vak@cronyx.ru>
 *
 * Heavily revamped to conform to RFC 1661.
 * Copyright (C) 1997, Joerg Wunsch.
 *
 * This software is distributed with NO WARRANTIES, not even the implied
 * warranties for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Authors grant any other persons or organizations permission to use
 * or modify this software as long as this message is kept with the software,
 * all derivative works or modified versions.
 *
 * From: Version 2.0, Fri Oct  6 20:39:21 MSK 1995
 *
 * $FreeBSD$
 */

#ifndef _NET_IF_SPPP_H_
#define _NET_IF_SPPP_H_ 1

/* ioctls used by the if_spppsubr.c driver */

#define	SPPP_AUTHPROTO_NONE	0
#define SPPP_AUTHPROTO_PAP	1
#define SPPP_AUTHPROTO_CHAP	2

#define SPPP_AUTHFLAG_NOCALLOUT		1	/* do not require authentication on */
						/* callouts */
#define SPPP_AUTHFLAG_NORECHALLENGE	2	/* do not re-challenge CHAP */

struct spppauthcfg {
	char	ifname[IFNAMSIZ];	/* pppoe interface name */
	u_int	hisauth;		/* one of SPPP_AUTHPROTO_* above */
	u_int	myauth;			/* one of SPPP_AUTHPROTO_* above */
	u_int	myname_length;		/* includes terminating 0 */
	u_int	mysecret_length;	/* includes terminating 0 */
	u_int	hisname_length;		/* includes terminating 0 */
	u_int	hissecret_length;	/* includes terminating 0 */
	u_int	myauthflags;
	u_int	hisauthflags;
	char	*myname;
	char	*mysecret;
	char	*hisname;
	char	*hissecret;
};

#define	SPPPGETAUTHCFG	_IOWR('i', 120, struct spppauthcfg)
#define	SPPPSETAUTHCFG	_IOW('i', 121, struct spppauthcfg)

struct sppplcpcfg {
	char	ifname[IFNAMSIZ];	/* pppoe interface name */
	int	lcp_timeout;		/* LCP timeout, in ticks */
};

#define	SPPPGETLCPCFG	_IOWR('i', 122, struct sppplcpcfg)
#define	SPPPSETLCPCFG	_IOW('i', 123, struct sppplcpcfg)

/*
 * Don't change the order of this.  Ordering the phases this way allows
 * for a comparision of ``pp_phase >= PHASE_AUTHENTICATE'' in order to
 * know whether LCP is up.
 */
#define	SPPP_PHASE_DEAD		0
#define	SPPP_PHASE_ESTABLISH	1
#define	SPPP_PHASE_TERMINATE	2
#define	SPPP_PHASE_AUTHENTICATE	3
#define	SPPP_PHASE_NETWORK	4

struct spppstatus {
	char	ifname[IFNAMSIZ];	/* pppoe interface name */
	int	phase;			/* one of SPPP_PHASE_* above */
};

#define	SPPPGETSTATUS	_IOWR('i', 124, struct spppstatus)

struct spppstatusncp {
	char	ifname[IFNAMSIZ];	/* pppoe interface name */
	int	phase;			/* one of SPPP_PHASE_* above */
	int	ncpup;			/* != 0 if at least on NCP is up */
};

#define	SPPPGETSTATUSNCP	_IOWR('i', 134, struct spppstatusncp)

struct spppidletimeout {
	char	ifname[IFNAMSIZ];	/* pppoe interface name */
	time_t	idle_seconds;		/* number of seconds idle before
					 * disconnect, 0 to disable idle-timeout */
};

struct spppidletimeout50 {
	char	ifname[IFNAMSIZ];	/* pppoe interface name */
	uint32_t idle_seconds;		/* number of seconds idle before
					 * disconnect, 0 to disable idle-timeout */
};

#define	SPPPGETIDLETO	_IOWR('i', 125, struct spppidletimeout)
#define	SPPPSETIDLETO	_IOW('i', 126, struct spppidletimeout)
#define	__SPPPGETIDLETO50	_IOWR('i', 125, struct spppidletimeout50)
#define	__SPPPSETIDLETO50	_IOW('i', 126, struct spppidletimeout50)

struct spppauthfailurestats {
	char	ifname[IFNAMSIZ];	/* pppoe interface name */
	int	auth_failures;		/* number of LCP failures since last successful TLU */
	int	max_failures;		/* max. allowed authorization failures */
};

#define	SPPPGETAUTHFAILURES	_IOWR('i', 127, struct spppauthfailurestats)

struct spppauthfailuresettings {
	char	ifname[IFNAMSIZ];	/* pppoe interface name */
	int	max_failures;		/* max. allowed authorization failures */
};
#define	SPPPSETAUTHFAILURE	_IOW('i', 128, struct spppauthfailuresettings)

/* set the DNS options we would like to query during PPP negotiation */
struct spppdnssettings {
	char	ifname[IFNAMSIZ];	/* pppoe interface name */
	int	query_dns;		/* bitmask (bits 0 and 1) for DNS options to query in IPCP */
};
#define	SPPPSETDNSOPTS		_IOW('i', 129, struct spppdnssettings)
#define	SPPPGETDNSOPTS		_IOWR('i', 130, struct spppdnssettings)

/* get the DNS addresses we received from the peer */
struct spppdnsaddrs {
	char	ifname[IFNAMSIZ];	/* pppoe interface name */
	uint32_t dns[2];		/* IP addresses */
};

#define SPPPGETDNSADDRS		_IOWR('i', 131, struct spppdnsaddrs)

/* set LCP keepalive/timeout options */
struct spppkeepalivesettings {
	char	ifname[IFNAMSIZ];	/* pppoe interface name */
	u_int	maxalive;		/* number of LCP echo req. w/o reply */
	time_t	max_noreceive;		/* (sec.) grace period before we start
					   sending LCP echo requests. */
};
struct spppkeepalivesettings50 {
	char	ifname[IFNAMSIZ];	/* pppoe interface name */
	u_int	maxalive;		/* number of LCP echo req. w/o reply */
	uint32_t max_noreceive;		/* (sec.) grace period before we start
					   sending LCP echo requests. */
};
#define	SPPPSETKEEPALIVE	_IOW('i', 132, struct spppkeepalivesettings)
#define	SPPPGETKEEPALIVE	_IOWR('i', 133, struct spppkeepalivesettings)
#define	__SPPPSETKEEPALIVE50	_IOW('i', 132, struct spppkeepalivesettings50)
#define	__SPPPGETKEEPALIVE50	_IOWR('i', 133, struct spppkeepalivesettings50)

/* 134 already used! */

#define IDX_LCP 0		/* idx into state table */

struct slcp {
	u_long	opts;		/* LCP options to send (bitfield) */
	u_long  magic;          /* local magic number */
	u_long	mru;		/* our max receive unit */
	u_long	their_mru;	/* their max receive unit */
	u_long	protos;		/* bitmask of protos that are started */
	u_char  echoid;         /* id of last keepalive echo request */
	/* restart max values, see RFC 1661 */
	int	timeout;
	int	max_terminate;
	int	max_configure;
	int	max_failure;
};

#define IDX_IPCP 1		/* idx into state table */
#define IDX_IPV6CP 2		/* idx into state table */

struct sipcp {
	u_long	opts;		/* IPCP options to send (bitfield) */
	u_int	flags;
#define IPCP_HISADDR_SEEN 1	/* have seen his address already */
#define IPCP_MYADDR_DYN   2	/* my address is dynamically assigned */
#define IPCP_MYADDR_SEEN  4	/* have seen his address already */
#ifdef notdef
#define IPV6CP_MYIFID_DYN 8	/* my ifid is dynamically assigned */
#endif
#define IPV6CP_MYIFID_SEEN 0x10	/* have seen his ifid already */
#define IPCP_VJ		0x20	/* can use VJ compression */
	int	max_state;	/* VJ: Max-Slot-Id */
	int	compress_cid;	/* VJ: Comp-Slot-Id */
};

#define AUTHNAMELEN	64
#define AUTHKEYLEN	16

struct sauth {
	u_short	proto;			/* authentication protocol to use */
	u_short	flags;
#define AUTHFLAG_NOCALLOUT	1	/* do not require authentication on */
					/* callouts */
#define AUTHFLAG_NORECHALLENGE	2	/* do not re-challenge CHAP */
	u_char	name[AUTHNAMELEN];	/* system identification name */
	u_char	secret[AUTHKEYLEN];	/* secret password */
	u_char	challenge[AUTHKEYLEN];	/* random challenge */
};

#define IDX_PAP		3
#define IDX_CHAP	4

#define IDX_COUNT (IDX_CHAP + 1) /* bump this when adding cp's! */

/*
 * Don't change the order of this.  Ordering the phases this way allows
 * for a comparision of ``pp_phase >= PHASE_AUTHENTICATE'' in order to
 * know whether LCP is up.
 */
enum ppp_phase {
	PHASE_DEAD, PHASE_ESTABLISH, PHASE_TERMINATE,
	PHASE_AUTHENTICATE, PHASE_NETWORK
};

#define PP_MTU          1500    /* default/minimal MRU */
#define PP_MAX_MRU	2048	/* maximal MRU we want to negotiate */

/*
 * This is a cut down struct sppp (see below) that can easily be
 * exported to/ imported from userland without the need to include
 * dozens of kernel-internal header files.  It is used by the
 * SPPPIO[GS]DEFS ioctl commands below.
 */
struct sppp_parms {
	enum ppp_phase pp_phase;	/* phase we're currently in */
	int	enable_vj;		/* VJ header compression enabled */
	int	enable_ipv6;		/*
					 * Enable IPv6 negotiations -- only
					 * needed since each IPv4 i/f auto-
					 * matically gets an IPv6 address
					 * assigned, so we can't use this as
					 * a decision.
					 */
	struct slcp lcp;		/* LCP params */
	struct sipcp ipcp;		/* IPCP params */
	struct sipcp ipv6cp;		/* IPv6CP params */
	struct sauth myauth;		/* auth params, i'm peer */
	struct sauth hisauth;		/* auth params, i'm authenticator */
};

/*
 * Definitions to pass struct sppp_parms data down into the kernel
 * using the SIOC[SG]IFGENERIC ioctl interface.
 *
 * In order to use this, create a struct spppreq, fill in the cmd
 * field with SPPPIOGDEFS, and put the address of this structure into
 * the ifr_data portion of a struct ifreq.  Pass this struct to a
 * SIOCGIFGENERIC ioctl.  Then replace the cmd field by SPPPIOSDEFS,
 * modify the defs field as desired, and pass the struct ifreq now
 * to a SIOCSIFGENERIC ioctl.
 */

#define SPPPIOGDEFS  ((caddr_t)(('S' << 24) + (1 << 16) +\
	sizeof(struct sppp_parms)))
#define SPPPIOSDEFS  ((caddr_t)(('S' << 24) + (2 << 16) +\
	sizeof(struct sppp_parms)))

struct spppreq {
	int	cmd;
	struct sppp_parms defs;
};

#ifdef _KERNEL
struct sppp {
	struct  ifnet *pp_ifp;    /* network interface data */
	struct  ifqueue pp_fastq; /* fast output queue */
	struct	ifqueue pp_cpq;	/* PPP control protocol queue */
	struct  sppp *pp_next;  /* next interface in keepalive list */
	u_int   pp_mode;        /* major protocol modes (cisco/ppp/...) */
	u_int	pp_framebytes;	/* number of bytes added by (hardware) framing */
	u_int   pp_flags;       /* sub modes */
	u_short pp_alivecnt;    /* keepalive packets counter */
	u_short pp_loopcnt;     /* loopback detection counter */
	u_long  pp_seq[IDX_COUNT];	/* local sequence number */
	u_long  pp_rseq[IDX_COUNT];	/* remote sequence number */
	uint64_t	pp_saved_mtu;	/* saved MTU value */
	time_t	pp_last_receive;	/* peer's last "sign of life" XXX pp_last_recv */
	time_t	pp_max_noreceive;	/* seconds since last receive before
					   we start to worry and send echo
					   requests */
	time_t	pp_last_activity;	/* second of last payload data s/r */
	time_t	pp_idle_timeout;	/* idle seconds before auto-disconnect,
					 * 0 = disabled */
	int	pp_auth_failures;	/* authorization failures */
	int	pp_max_auth_fail;	/* max. allowed authorization failures */
	enum ppp_phase pp_phase;	/* phase we're currently in */
	int	query_dns;	/* 1 if we want to know the dns addresses */
	uint32_t	dns_addrs[2];
	int	state[IDX_COUNT];	/* state machine */
	u_char  confid[IDX_COUNT];	/* id of last configuration request */
	int	rst_counter[IDX_COUNT];	/* restart counter */
	int	fail_counter[IDX_COUNT]; /* negotiation failure counter */
	int	confflags;	/* administrative configuration flags */
#define CONF_ENABLE_VJ    0x01	/* VJ header compression enabled */
#define CONF_ENABLE_IPV6  0x02	/* IPv6 administratively enabled */
	time_t	pp_last_recv;	/* time last packet has been received */
	time_t	pp_last_sent;	/* time last packet has been sent */
	struct callout ch[IDX_COUNT];	/* per-proto and if callouts */
	struct callout pap_my_to_ch;	/* PAP needs one more... */
	struct callout keepalive_callout; /* keepalive callout */
	struct slcp lcp;		/* LCP params */
	struct sipcp ipcp;		/* IPCP params */
	struct sipcp ipv6cp;		/* IPv6CP params */
	struct sauth myauth;		/* auth params, i'm peer */
	struct sauth hisauth;		/* auth params, i'm authenticator */
	struct slcompress *pp_comp;	/* for VJ compression */
	u_short fr_dlci;		/* Frame Relay DLCI number, 16..1023 */
	u_char fr_status;		/* PVC status, active/new/delete */
	/*
	 * These functions are filled in by sppp_attach(), and are
	 * expected to be used by the lower layer (hardware) drivers
	 * in order to communicate the (un)availability of the
	 * communication link.  Lower layer drivers that are always
	 * ready to communicate (like hardware HDLC) can shortcut
	 * pp_up from pp_tls, and pp_down from pp_tlf.
	 */
	void	(*pp_up)(struct sppp *sp);
	void	(*pp_down)(struct sppp *sp);
	/*
	 * These functions need to be filled in by the lower layer
	 * (hardware) drivers if they request notification from the
	 * PPP layer whether the link is actually required.  They
	 * correspond to the tls and tlf actions.
	 */
	void	(*pp_tls)(struct sppp *sp);
	void	(*pp_tlf)(struct sppp *sp);
	/*
	 * These (optional) functions may be filled by the hardware
	 * driver if any notification of established connections
	 * (currently: IPCP up) is desired (pp_con) or any internal
	 * state change of the interface state machine should be
	 * signaled for monitoring purposes (pp_chg).
	 */
	void	(*pp_con)(struct sppp *sp);
	void	(*pp_chg)(struct sppp *sp, int new_state);
	/* These two fields are for use by the lower layer */
	void    *pp_lowerp;
	int     pp_loweri;
	/* Lock */
	struct mtx	mtx;
	/* if_start () wrapper */
	void	(*if_start) (struct ifnet *);
	struct callout ifstart_callout; /* if_start () scheduler */
};
#define IFP2SP(ifp)	((struct sppp *)(ifp)->if_l2com)
#define SP2IFP(sp)	((sp)->pp_ifp)

/* bits for pp_flags */
#define PP_KEEPALIVE    0x01    /* use keepalive protocol */
#define PP_FR		0x04	/* use Frame Relay protocol instead of PPP */
				/* 0x04 was PP_TIMO */
#define PP_CALLIN	0x08	/* we are being called */
#define PP_NEEDAUTH	0x10	/* remote requested authentication */
#define PP_NOFRAMING		0x20	/* do not add/expect encapsulation
					   around PPP frames (i.e. the serial
					   HDLC like encapsulation, RFC1662) */
#define PP_LOOPBACK		0x40	/* in line loopback mode */
#define PP_LOOPBACK_IFDOWN	0x80	/* if_down() when loopback detected */
#define PP_KEEPALIVE_IFDOWN	0x100	/* if_down() when no ECHO_REPLY received */
#define PP_ADMIN_UP		0x200	/* the interface is up */

void sppp_attach (struct ifnet *ifp);
void sppp_detach (struct ifnet *ifp);
void sppp_input (struct ifnet *ifp, struct mbuf *m);
int sppp_ioctl (struct ifnet *ifp, u_long cmd, void *data);
struct mbuf *sppp_dequeue (struct ifnet *ifp);
struct mbuf *sppp_pick(struct ifnet *ifp);
int sppp_isempty (struct ifnet *ifp);
void sppp_flush (struct ifnet *ifp);

/* Internal functions */
void sppp_fr_input (struct sppp *sp, struct mbuf *m);
struct mbuf *sppp_fr_header (struct sppp *sp, struct mbuf *m, int fam);
void sppp_fr_keepalive (struct sppp *sp);
void sppp_get_ip_addrs(struct sppp *sp, u_long *src, u_long *dst,
		       u_long *srcmask);

#endif

#endif /* _NET_IF_SPPP_H_ */
