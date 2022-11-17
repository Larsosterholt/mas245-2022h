Buildroot må lastes ned fra buildroot.org og pakkes ut i buildroot-katalogen!

Alternativt kan git benyttes for å klone buildroot inn i buildroot-katalogen:

Eks.:
cd buildroot-project
git clone https://github.com/buildroot/buildroot.git buildroot
git checkout VERSJON_GITT_I_OPPGAVETEKST

.. følg deretter instruksjoner i oppgaveteksten.


make O=${PWD}/buildroot-output/BR2_EXTERNAL=${PWD}/external -C ${PWD}/buildroot menuconfig
