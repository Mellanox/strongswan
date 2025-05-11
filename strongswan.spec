Name: strongswan
Version: 5.9.10
Release: 2.bf%{?dist}
Summary: BlueField Strongswan Package

License: BSD and GPLv2+ and MIT and Expat
Url: https://github.com/Mellanox/strongswan.git
Source: %{name}-%{version}.tgz

BuildRequires: binutils
BuildRequires: openssl-devel
BuildRequires: gmp-devel
BuildRequires: gettext-devel
BuildRequires: pkgconfig
BuildRequires: perl
BuildRequires: gperf
BuildRequires: bison
BuildRequires: flex
BuildRequires: libtool
BuildRequires: gcc >= 3

%package -n strongswan-swanctl
Summary: Placeholder package for strongswan-swanctl for dependency resolution
%description -n strongswan-swanctl
This package contains the swanctl interface, used to configure a running
charon daemon

%description
The strongSwan IPsec implementation supports both IKEv1 IKEv2 key
exchange protocols in conjunction with the native NETKEY IPsec stack of the
Linux Kernel.

%files -n strongswan-swanctl

%global debug_package %{nil}

%prep
rm -rf build/* || rm -rf strongswan-5.9.10 || true

%setup -q
cp -f systemd-conf/strongswan-starter.service.in.centos init/systemd-starter/strongswan-starter.service.in
cp -f systemd-conf/strongswan.service.in.centos init/systemd/strongswan.service.in
./autogen.sh

%build
export CFLAGS="$CFLAGS -Wformat -Wno-error -Wno-error=format -Wno-error=format-extra-args -fPIC"
%configure \
	--enable-openssl \
	--disable-random \
	--prefix=%{_prefix} \
	--sysconfdir=%{_sysconfdir} \
	--enable-systemd \
	--enable-doca
%make_build

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

mkdir -p $RPM_BUILD_ROOT%{_sysconfdir}/etc/swanctl/conf.d
cp -f mlnx-conf/BFL.swanctl.conf $RPM_BUILD_ROOT%{_sysconfdir}/swanctl/conf.d
cp -f mlnx-conf/BFR.swanctl.conf $RPM_BUILD_ROOT%{_sysconfdir}/swanctl/conf.d

%preun
systemctl stop strongswan-starter.service > /dev/null 2>&1 || true
systemctl disable strongswan-starter.service > /dev/null 2>&1 || true

%post
# Use the strongswan.service instead of the legacy strongswan-starter
# systemctl enable strongswan-starter.service
systemctl enable strongswan.service

%files
%defattr(-, root, root)
/usr/lib64/ipsec
/usr/bin/dh_speed
/usr/bin/pubkey_speed
/usr/bin/pki
/usr/sbin/swanctl
/usr/sbin/ipsec
/usr/libexec/ipsec
%{_sysconfdir}/
%{_datadir}/
/usr/lib/systemd/system/strongswan.service
/usr/sbin/charon-systemd

%doc COPYING TODO NEWS INSTALL HACKING README
%license LICENSE
