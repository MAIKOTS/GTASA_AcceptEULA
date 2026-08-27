#include "mod/amlmod.h"
#include "mod/config.h"
#include "mod/logger.h"

MYMODCFG(net.rusjj.gtasa.eula, Accept EULA, 1.0, RusJJ)
NEEDGAME(com.rockstargames.gtasa)

uintptr_t pSCAndLib = 0;
ConfigEntry* pEULAAccepted;

extern "C" void OnModLoad()
{
    // Usando o logger do mod
    logger->Info("=== AcceptEULA Mod Carregado ===");

    pSCAndLib = aml->GetLib("libSCAnd.so");
    if(pSCAndLib)
    {
        logger->Info("Biblioteca libSCAnd.so encontrada com sucesso!");

        pEULAAccepted = cfg->Bind("AcceptEULA", true);
        if(pEULAAccepted->GetBool())
        {
            logger->Info("Aplicando patch para aceitar a EULA automaticamente...");
            
            aml->Unprot(pSCAndLib + 0x31C149, 1);
            *(bool*)(pSCAndLib + 0x31C149) = true;
            
            logger->Info("Patch aplicado com sucesso!");
            return;
        }
    }
    else
    {
        logger->Error("Erro: libSCAnd.so não foi encontrada!");
    }
}
