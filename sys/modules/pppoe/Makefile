# $FreeBSD$

.PATH: ${.CURDIR}/../../net

KMOD=	pppoe
SRCS=	if_pppoe.c

EXPORT_SYMS=	ppoediscinq \
		ppoeinq \
		pppoe_softintr \
		pppoe_softintr_handler

.include <bsd.kmod.mk>
