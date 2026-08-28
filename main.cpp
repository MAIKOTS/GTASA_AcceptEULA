#include "mod/amlmod.h"
#include "mod/config.h"

MYMODCFG(net.rusjj.gtasa.eula, Accept EULA, 1.0, RusJJ)
NEEDGAME(com.rockstargames.gtasa)

uintptr_t pSCAndLib = 0;
ConfigEntry* pEULAAccepted;

extern "C" void OnModLoad()
{
    pSCAndLib = aml->GetLib("libSCAnd.so");
    if(pSCAndLib)
    {
        // Vincula ou cria a entrada na config
        pEULAAccepted = cfg->Bind("AcceptEULA", true);

        // Aplica a modificação na memória do libSCAnd.so
        aml->Unprot(pSCAndLib + 0x31C149, 1);
        *(bool*)(pSCAndLib + 0x31C149) = true;

        // Salva o estado atualizado da config
        cfg->Save();
    }
}
