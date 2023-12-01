[Defines]
    PLATFORM_NAME   = neoboot
    PLATFORM_GUID   = 08A0AABE-BCBA-4679-B3E8-4FB75E95E00E
    PLATFORM_VERSION = 0.01
    DSC_SPECIFICATION = 0x00010005
    OUTPUT_DIRECTORY = Build/neoboot$(ARCH)
    SUPPORTED_ARCHITECTURES = X64
    BUILD_TARGETS = DEBUG|RELEASE|NOOPT

[LibraryClasses]
    # Entry point
    UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
    # common
    BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
    BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
    PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
    UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
    # debug
    !if $(DEBUG_ENABLE_OUTPUT)
    DebugLib|MdePkg/Library/UefiDebugLibConOut/UefiDebugLibConOut.inf
    DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
    !else   
    DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
    !endif 
    # uefi
    UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
    PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
    MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
    UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
    DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
    # edk2の最新にも対応
    RegisterFilterLib|MdePkg/Library/RegisterFilterLibNull/RegisterFilterLibNull.inf

[Components]
    neoboot/loader.inf