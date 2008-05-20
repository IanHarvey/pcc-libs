# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([pcc-libs], [0.9.9], <pcc-list@ludd.ltu.se>)

AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_CANONICAL_TARGET

version=$PACKAGE_VERSION

case "$target_os" in
	apple)
		targos=apple
		targmach="$target_cpu"
		;;
	darwin*)
		targos=darwin
		targmach="$target_cpu"
		;;
	dragonfly*)
		targos=dragonfly
		targmach="$target_cpu"
		;;
	freebsd*)
		targos=freebsd
		targmach="$target_cpu"
		;;
	linux*)
		targos=linux
		targmach="$target_cpu"
		;;
	minux)
		targos=minix
		targmach="$target_cpu"
		;;
	netbsd*)
		targos=netbsd
		targmach="$target_cpu"
		;;
	openbsd*)
		targos=openbsd
		targmach="$target_cpu"
		;;
	midnightbsd*)
		targos=midnightbsd
		targmach="$target_cpu"
		;;
	mirbsd*)
		targos=mirbsd
		targmach="$target_cpu"
		;;
	window*|pe*)
		target_alias=i386-pe
		targos=win32
		targmach="$target_cpu"
		;;
	*)
		targos="$target_os"
		targmach="$target_cpu"
		;;
esac

if test "X$targos" = X -o "X$targmach" = X; then
	AC_MSG_ERROR(['$target' is not (yet) supported by pcc-libs.])
fi

AC_CHECK_PROG(CC, cc, cc, :)
AC_CHECK_PROG(AR, ar, ar, :)
AC_PROG_RANLIB

AC_SUBST(targos)
AC_SUBST(targmach)
AC_SUBST(version)
AC_SUBST(prefix)
AC_SUBST(libdir)
AC_SUBST(includedir)
AC_SUBST(CPPFLAGS)
AC_SUBST(CFLAGS)

AC_CONFIG_FILES([Makefile
                libsoftfloat/Makefile
		libpcc/Makefile
])
AC_OUTPUT

