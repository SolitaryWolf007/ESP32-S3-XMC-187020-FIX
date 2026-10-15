# Correção de boot do ESP32-S3 com flash XMC `0x187020`

[English version](README.md)

Correção mínima e reproduzível para ESP32-S3 N16R8 que entra em loop de reset com a flash XMC identificada como:

```text
Manufacturer: 20
Device: 7018
JEDEC ID: 0x187020
```

O problema foi reproduzido no ESP-IDF 5.5.5 e corresponde ao comportamento descrito no [issue espressif/esp-idf#18947](https://github.com/espressif/esp-idf/issues/18947). O bootloader reconhece o fabricante XMC (`0x20`), mas a validação estrita não aceitava o MFID `0x70`. O patch adiciona `0x70` ao mesmo intervalo de capacidade já usado para `0x41`:

```diff
-    } else if (mfid == 0x41) {
+    // Community modification: support XMC MFID 0x70 (JEDEC 20 70 18).
+    } else if (mfid == 0x41 || mfid == 0x70) {
```

## Estado

Validado em hardware real:

- ESP32-S3 revisão 0.2;
- módulo N16R8;
- flash XMC de 16 MB, JEDEC `20 70 18`;
- flash quad a 3,3 V;
- Arduino-ESP32 3.3.12, baseado no ESP-IDF 5.5.5;
- modo DIO, 40 MHz no cabeçalho do bootloader;
- PSRAM desabilitada no firmware de teste para reduzir variáveis.

Após a gravação, a placa saiu do loop de reset e executou o sketch normalmente.

## Uso rápido com Arduino IDE

O Arduino-ESP32 dá prioridade a um arquivo chamado `bootloader.bin` colocado na pasta do sketch. Não substitua arquivos globais dentro de `Arduino15`.

1. Abra [`examples/arduino/XMCBootTest/XMCBootTest.ino`](examples/arduino/XMCBootTest/XMCBootTest.ino).
2. Selecione **ESP32S3 Dev Module**.
3. Configure **Flash Size: 16MB**, **Flash Mode: DIO**, **PSRAM: Disabled** e **Upload Speed: 115200**.
4. Mantenha **Erase All Flash Before Sketch Upload: Disabled**.
5. Compile e grave normalmente.

O exemplo já contém seu próprio [`bootloader.bin`](examples/arduino/XMCBootTest/bootloader.bin). Para usar a correção em outro sketch, copie [`prebuilt/bootloader.bin`](prebuilt/bootloader.bin) para a mesma pasta do arquivo `.ino`, preservando exatamente o nome `bootloader.bin`.

## Recompilar a partir do código-fonte

Use a versão completa do [ESP-IDF v5.5.5](https://github.com/espressif/esp-idf/releases/tag/v5.5.5), incluindo os submódulos:

```powershell
git clone --recursive --branch v5.5.5 https://github.com/espressif/esp-idf.git
cd esp-idf
git apply ..\esp32s3-xmc-0x187020-fix\patches\esp-idf-v5.5.5-xmc-mfid-0x70.patch
install.bat esp32s3
export.bat
cd ..\esp32s3-xmc-0x187020-fix\examples\esp-idf
idf.py set-target esp32s3
idf.py build
```

Consulte também o [guia oficial do ESP-IDF 5.5.5 para ESP32-S3](https://docs.espressif.com/projects/esp-idf/en/v5.5.5/esp32s3/get-started/index.html).

O bootloader recompilado ficará em `examples/esp-idf/build/bootloader/bootloader.bin`.

## Binário pré-compilado

Arquivo: [`prebuilt/bootloader.bin`](prebuilt/bootloader.bin)

```text
Tamanho: 20848 bytes
SHA-256: F37CF7872A0CE2A9B1DA847EA79A5FFAEF8961CBA48CD99F493ACB117F470BF4
Endereço: 0x0
```

Os hashes também estão em [`SHA256SUMS.txt`](SHA256SUMS.txt).

## Segurança e limitações

- Faça backup da flash antes de alterar uma placa com dados importantes.
- Não use o binário pré-compilado em placas com Secure Boot ou Flash Encryption sem analisar a configuração original.
- O patch é deliberadamente restrito ao fabricante XMC, MFID `0x70` e capacidades `0x17` a `0x20`.
- Para outras versões do ESP-IDF, reaplique e revise o patch no código-fonte correspondente.
- Esta é uma correção comunitária validada no hardware descrito, não uma correção oficial da Espressif.

## Estrutura

```text
patches/                 patch mínimo para ESP-IDF 5.5.5
prebuilt/                bootloader validado e pronto para uso
examples/arduino/        sketch Arduino com bootloader local
examples/esp-idf/        projeto mínimo para recompilar e testar
```

## Licença

O código original deste repositório e a modificação são disponibilizados sob a Apache License 2.0. O binário pré-compilado contém componentes derivados do ESP-IDF, Newlib e do runtime GCC sob suas respectivas licenças e exceções. Veja [`NOTICE`](NOTICE), [`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md) e [`licenses/`](licenses/).
