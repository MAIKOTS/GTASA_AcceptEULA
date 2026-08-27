#include "mod/amlmod.h"
#include "mod/config.h"

MYMODCFG(net.rusjj.gtasa.eula, Accept EULA, 1.0, RusJJ)
NEEDGAME(com.rockstargames.gtasa)

uintptr_t pSCAndLib = 0;
ConfigEntry* pEULAAccepted;

extern "C" void OnModLoad()
{
    // Usando o log padrão do aml
    aml->Log("=== AcceptEULA Mod Carregado ===");

    pSCAndLib = aml->GetLib("libSCAnd.so");
    if(pSCAndLib)
    {
        aml->Log("Biblioteca libSCAnd.so encontrada com sucesso!");

        pEULAAccepted = cfg->Bind("AcceptEULA", true);
        if(pEULAAccepted->GetBool())
        {
            aml->Log("Aplicando patch para aceitar a EULA automaticamente...");
            
            aml->Unprot(pSCAndLib + 0x31C149, 1);
            *(bool*)(pSCAndLib + 0x31C149) = true;
            
            aml->Log("Patch aplicado com sucesso!");
            return;
        }
    }
    else
    {
        aml->Log("Erro: libSCAnd.so não foi encontrada!");
    }
}
        logger->Error("Erro: libSCAnd.so não foi encontrada!");
    }
}
