#include "mod/amlmod.h"
#include "mod/config.h"

MYMODCFG(net.rusjj.gtasa.eula, Accept EULA, 1.0, RusJJ)
NEEDGAME(com.rockstargames.gtasa)

uintptr_t pSCAndLib = 0;
ConfigEntry* pEULAAccepted;

extern "C" void OnModLoad()
{
    // Mensagem inicial nos logs do AML para sabermos que o mod iniciou
    logger->Info("=== AcceptEULA Mod Carregado ===");

    pSCAndLib = aml->GetLib("libSCAnd.so");
    if(pSCAndLib)
    {
        logger->Info("Biblioteca libSCAnd.so encontrada com sucesso!");

        // Vincula a opção no arquivo .ini gerado pelo mod
        pEULAAccepted = cfg->Bind("AcceptEULA", true); // Deixamos true por padrão ou false dependendo da sua preferência

        if(pEULAAccepted->GetBool())
        {
            logger->Info("Aplicando patch para aceitar a EULA automaticamente...");
            
            // Desprotege a memória e altera o valor para true
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
