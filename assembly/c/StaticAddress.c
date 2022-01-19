#include "SaveFile.h"
#include "StaticAddress.h"

StaticAddressConfig gStaticAddressConfig = {
    .magic = STATIC_ADDRESS_CONFIG_MAGIC,
    .version = 0,
    .externalEffectsConfig = &gExternalEffects,
    .questItemStorage = &SAVE_FILE_CONFIG.questStorage,
};

/**
 * Write config structure pointer to tail end of payload RDRAM for access by external software (Crowd Control, ModLoader64).
 **/
static void WritePointer(void) {
    // Cannot share G_PAYLOAD_END constant from asm, so re-define it here.
    const u32 payloadEnd = 0x80780000;
    void **const pointer = (void **const)(payloadEnd - 4);
    *pointer = &gStaticAddressConfig;
}

void StaticAddress_Init(void) {
    WritePointer();
}
