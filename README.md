# GTASA_AcceptEULA

Um mod Android para GTA: San Andreas que automaticamente aceita a EULA do jogo ao ser carregado, sem exigir interação manual do usuário.

## O que faz

Este projeto injeta a alteração necessária em `libSCAnd.so` quando o mod é carregado pelo AndroidModLoader. O objetivo é evitar a tela de aceite da EULA e permitir que a sessão inicie diretamente.

## Estrutura do projeto

```text
.
├── Android.mk
├── Application.mk
├── CMakeLists.txt
├── LICENSE
├── build.ps1
├── main.cpp
├── ndkpath.txt
├── mod/
│   ├── amlmod.h
│   ├── iaml.h
│   ├── interface.h
│   └── ...
└── README.md
```

## Requisitos

- Android NDK instalado
- Android SDK (para build via CI ou CMake)
- GTA: San Andreas para Android
- AndroidModLoader

## Build

### Windows / PowerShell

Primeiro, configure o caminho do NDK no arquivo `ndkpath.txt`:

```text
D:\android-ndk
```

Depois execute:

```powershell
./build.ps1
```

### Manual via NDK

```bash
ndk-build \
  NDK_PROJECT_PATH=$PWD \
  APP_BUILD_SCRIPT=$PWD/Android.mk \
  NDK_APPLICATION_MK=$PWD/Application.mk \
  NDK_DEBUG=0
```

### CMake

```bash
cmake -B build/armeabi-v7a \
  -DANDROID_ABI=armeabi-v7a \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build/armeabi-v7a --config Release
```

## Observações importantes

- O módulo é compilado como uma biblioteca compartilhada `.so`.
- O alvo usado no projeto é `armeabi-v7a`.
- A modificação principal acontece no offset `0x31C149` dentro de `libSCAnd.so`.
- O código depende do ambiente do AndroidModLoader para obter a referência da biblioteca e aplicar a alteração em memória.

## Licença

Este projeto está licenciado sob a MIT License. Consulte o arquivo `LICENSE` para mais detalhes.

## Autor

- MAIKOTS

## Nota

Este é um mod de engenharia reversa / patch em memória para contornar a EULA de um jogo Android. Use somente em ambientes e contextos permitidos pelo jogo e pela legislação aplicável.
