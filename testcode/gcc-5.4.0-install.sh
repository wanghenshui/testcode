echo "Downloading gcc source files..."
curl https://ftp.gnu.org/gnu/gcc/gcc-5.4.0/gcc-5.4.0.tar.bz2 -O

echo "extracting files..."
tar xvfj gcc-5.4.0.tar.bz2

echo "Installing dependencies..."
yum install gmp-devel mpfr-devel libmpc-devel -y

echo "Configure and install..."
mkdir gcc-5.4.0-build
cd gcc-5.4.0-build
../gcc-5.4.0/configure --enable-languages=c,c++ --disable-multilib
make -j$(nproc) && make install
source /etc/profile #update
