#ifndef _EFI_GUID_H
#define _EFI_GUID_H

/* EFI_LOADED_IMAGE_PROTOCOL */
#define EFI_LOADED_IMAGE_PROTOCOL_GUID               \
  {                                                  \
    0x5B1B31A1, 0x9562, 0x11d2,                      \
    {                                                \
      0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B \
    }                                                \
  }

#define EFI_LOADED_IMAGE_PROTOCOL_REVISION 0x1000

#define EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL_GUID   \
  {                                                  \
    0xbc62157e, 0x3e33, 0x4fec,                      \
    {                                                \
      0x99, 0x20, 0x2d, 0x3b, 0x36, 0xd7, 0x50, 0xdf \
    }                                                \
  }

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID                                      \
  {                                                                               \
    0x964e5b22, 0x6459, 0x11d2, { 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
  }

/* Device Path Protocol */
#define EFI_DEVICE_PATH_PROTOCOL_GUID                \
  {                                                  \
    0x09576e91, 0x6d3f, 0x11d2,                      \
    {                                                \
      0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b \
    }                                                \
  }

#endif