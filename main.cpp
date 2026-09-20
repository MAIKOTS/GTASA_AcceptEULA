#include "mod/amlmod.h"

MYMOD(net.rusjj.gtasa.eula, Accept EULA, 1.0, RusJJ)
NEEDGAME(com.rockstargames.gtasa)

extern "C" void OnModLoad()
{
    uintptr_t pSCAndLib = aml->GetLib("libSCAnd.so");

    if (!pSCAndLib)
        return;

    constexpr uintptr_t EULA_OFFSET = 0x31C149;

    // Libera a proteção da memória e ativa a aceitação da EULA.
    aml->Unprot(pSCAndLib + EULA_OFFSET, sizeof(bool));
    *reinterpret_cast<bool*>(pSCAndLib + EULA_OFFSET) = true;
}
