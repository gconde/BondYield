FROM centos:7

RUN yum -y group install "Development Tools"
RUN yum -y install qt5-qtbase-devel.x86_64
COPY * ./
RUN qmake-qt5 -o Makefile BondYield.pro
RUN make compiler_moc_predefs_make_all mocables all
ENV QT_XKB_CONFIG_ROOT=/usr/share/X11/xkb
CMD ["./BondYield"]
