#ifndef _EFI_MACROS_H
#define _EFI_MACROS_H

/* EFI Macros */

/* _EFI_LOAD_OPTION */
#define LOAD_OPTION_ACTIVE                0x00000001
#define LOAD_OPTION_FORCE_RECONNECT       0x00000002
#define LOAD_OPTION_HIDDEN                0x00000008
#define LOAD_OPTION_CATEGORY              0x00001F00
#define LOAD_OPTION_CATEGORY_BOOT         0x00000000
#define LOAD_OPTION_CATEGORY_APP          0x00000100

/* EFI_BOOT_OPTION_SUPPORT */
#define EFI_BOOT_OPTION_SUPPORT_KEY         0x00000001
#define EFI_BOOT_OPTION_SUPPORT_APP         0x00000002
#define EFI_BOOT_OPTION_SUPPORT_SYSPREP     0x00000010
#define EFI_BOOT_OPTION_SUPPORT_COUNT       0x00000300

/* EFI_SYSTEM_TABLE */
#define EFI_SYSTEM_TABLE_SIGNATURE 0x5453595320494249
#define EFI_2_100_SYSTEM_TABLE_REVISION ((2<<16) | (100))
#define EFI_2_90_SYSTEM_TABLE_REVISION ((2<<16) | (90))
#define EFI_2_80_SYSTEM_TABLE_REVISION ((2<<16) | (80))
#define EFI_2_70_SYSTEM_TABLE_REVISION ((2<<16) | (70))
#define EFI_2_60_SYSTEM_TABLE_REVISION ((2<<16) | (60))
#define EFI_2_50_SYSTEM_TABLE_REVISION ((2<<16) | (50))
#define EFI_2_40_SYSTEM_TABLE_REVISION ((2<<16) | (40))
#define EFI_2_31_SYSTEM_TABLE_REVISION ((2<<16) | (31))
#define EFI_2_30_SYSTEM_TABLE_REVISION ((2<<16) | (30))
#define EFI_2_20_SYSTEM_TABLE_REVISION ((2<<16) | (20))
#define EFI_2_10_SYSTEM_TABLE_REVISION ((2<<16) | (10))
#define EFI_2_00_SYSTEM_TABLE_REVISION ((2<<16) | (00))
#define EFI_1_10_SYSTEM_TABLE_REVISION ((1<<16) | (10))
#define EFI_1_02_SYSTEM_TABLE_REVISION ((1<<16) | (02))
#define EFI_SPECIFICATION_VERSION    EFI_SYSTEM_TABLE_REVISION
#define EFI_SYSTEM_TABLE_REVISION    EFI_2_100_SYSTEM_TABLE_REVISION

/* EFI_BOOT_SERVICES */
#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

/* EFI_RUNTIME_SERVICES */
#define EFI_RUNTIME_SERVICES_SIGNATURE 0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION EFI_SPECIFICATION_VERSION

/* EFI_RT_SUPPORTED */
#define EFI_RT_SUPPORTED_GET_TIME                        0x0001
#define EFI_RT_SUPPORTED_SET_TIME                        0x0002
#define EFI_RT_SUPPORTED_GET_WAKEUP_TIME                 0x0004
#define EFI_RT_SUPPORTED_SET_WAKEUP_TIME                 0x0008
#define EFI_RT_SUPPORTED_GET_VARIABLE                    0x0010
#define EFI_RT_SUPPORTED_GET_NEXT_VARIABLE_NAME          0x0020
#define EFI_RT_SUPPORTED_SET_VARIABLE                    0x0040
#define EFI_RT_SUPPORTED_SET_VIRTUAL_ADDRESS_MAP         0x0080
#define EFI_RT_SUPPORTED_CONVERT_POINTER                 0x0100
#define EFI_RT_SUPPORTED_GET_NEXT_HIGH_MONOTONIC_COUNT   0x0200
#define EFI_RT_SUPPORTED_RESET_SYSTEM                    0x0400
#define EFI_RT_SUPPORTED_UPDATE_CAPSULE                  0x0800
#define EFI_RT_SUPPORTED_QUERY_CAPSULE_CAPABILITIES      0x1000
#define EFI_RT_SUPPORTED_QUERY_VARIABLE_INFO             0x2000

/* Event Types */ 
#define EVT_TIMER                            0x80000000
#define EVT_RUNTIME                          0x40000000

#define EVT_NOTIFY_WAIT                      0x00000100
#define EVT_NOTIFY_SIGNAL                    0x00000200

#define EVT_SIGNAL_EXIT_BOOT_SERVICES        0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE    0x60000202
/* EFI_EVENT */
#define EFI_EVENT_GROUP_EXIT_BOOT_SERVICES \
 {0x27abf055, 0xb1b8, 0x4c26, 0x80, 0x48, 0x74, 0x8f, 0x37,\
 0xba, 0xa2, 0xdf}

#define EFI_EVENT_GROUP_BEFORE_EXIT_BOOT_SERVICES \
  { 0x8be0e274, 0x3970, 0x4b44, { 0x80, 0xc5, 0x1a, 0xb9, 0x50, 0x2f, 0x3b, 0xfc } }

#define EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE \
  {0x13fa7698, 0xc831, 0x49c7, 0x87, 0xea, 0x8f, 0x43, 0xfc,\
  0xc2, 0x51, 0x96}

#define EFI_EVENT_GROUP_MEMORY_MAP_CHANGE \
 {0x78bee926, 0x692f, 0x48fd, 0x9e, 0xdb, 0x1, 0x42, 0x2e, \
 0xf0, 0xd7, 0xab}

#define EFI_EVENT_GROUP_READY_TO_BOOT \
 {0x7ce88fb3, 0x4bd7, 0x4679, 0x87, 0xa8, 0xa8, 0xd8, 0xde,\
 0xe5,0xd, 0x2b}

#define EFI_EVENT_GROUP_AFTER_READY_TO_BOOT \
  { 0x3a2a00ad, 0x98b9, 0x4cdf, { 0xa4, 0x78, 0x70, 0x27, 0x77,
0xf1, 0xc1, 0xb } }

#define EFI_EVENT_GROUP_RESET_SYSTEM \
{ 0x62da6a56, 0x13fb, 0x485a, { 0xa8, 0xda, 0xa3, 0xdd, 0x79, 0x12, 0xcb, 0x6b
 } }

#define TPL_APPLICATION    4
#define TPL_CALLBACK       8
#define TPL_NOTIFY         16
#define TPL_HIGH_LEVEL     31

/* MemoryAllocation */
#define EFI_MEMORY_UC              0x0000000000000001
#define EFI_MEMORY_WC              0x0000000000000002
#define EFI_MEMORY_WT              0x0000000000000004
#define EFI_MEMORY_WB              0x0000000000000008
#define EFI_MEMORY_UCE             0x0000000000000010
#define EFI_MEMORY_WP              0x0000000000001000
#define EFI_MEMORY_RP              0x0000000000002000
#define EFI_MEMORY_XP              0x0000000000004000
#define EFI_MEMORY_NV              0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE   0x0000000000010000
#define EFI_MEMORY_RO              0x0000000000020000
#define EFI_MEMORY_SP              0x0000000000040000
#define EFI_MEMORY_CPU_CRYPTO      0x0000000000080000
#define EFI_MEMORY_RUNTIME         0x8000000000000000
#define EFI_MEMORY_ISA_VALID       0x4000000000000000
#define EFI_MEMORY_ISA_MASK        0x0FFFF00000000000

/* EFI_OPEN_PROTOCOL */
#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL   0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL         0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL        0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER  0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER            0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE            0x00000020

/* Variable Attributes */
#define EFI_VARIABLE_NON_VOLATILE                           0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS                     0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS                         0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD                  0x00000008
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS             0x00000010
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS  0x00000020
#define EFI_VARIABLE_APPEND_WRITE                           0x00000040
#define EFI_VARIABLE_ENHANCED_AUTHENTICATED_ACCESS          0x00000080

/* Runtime Services */
#define EFI_VARIABLE_AUTHENTICATION_3_CERT_ID_SHA256 1

#define EFI_VARIABLE_AUTHENTICATION_3_TIMESTAMP_TYPE 1
#define EFI_VARIABLE_AUTHENTICATION_3_NONCE_TYPE 2

#define EFI_HARDWARE_ERROR_VARIABLE\
{0x414E6BDD,0xE47B,0x47cc,{0xB2,0x44,0xBB,0x61,0x02,0x0C,0xF5,0x16}}

#define EFI_OPTIONAL_PTR          0x00000001

/* CASPULE */
#define CAPSULE_FLAGS_PERSIST_ACROSS_RESET 0x00010000
#define CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE 0x00020000
#define CAPSULE_FLAGS_INITIATE_RESET 0x00040000

/* EFI_OS_INDICATIONS */
#define EFI_OS_INDICATIONS_BOOT_TO_FW_UI                           0x0000000000000001
#define EFI_OS_INDICATIONS_TIMESTAMP_REVOCATION                    0x0000000000000002
#define EFI_OS_INDICATIONS_FILE_CAPSULE_DELIVERY_SUPPORTED         0x0000000000000004
#define EFI_OS_INDICATIONS_FMP_CAPSULE_SUPPORTED                   0x0000000000000008
#define EFI_OS_INDICATIONS_CAPSULE_RESULT_VAR_SUPPORTED            0x0000000000000010
#define EFI_OS_INDICATIONS_START_OS_RECOVERY                       0x0000000000000020
#define EFI_OS_INDICATIONS_START_PLATFORM_RECOVERY                 0x0000000000000040
#define EFI_OS_INDICATIONS_JSON_CONFIG_DATA_REFRESH                0x0000000000000080

/* SimpleTextInput */
#define EFI_SHIFT_STATE_VALID          0x80000000
#define EFI_RIGHT_SHIFT_PRESSED        0x00000001
#define EFI_LEFT_SHIFT_PRESSED         0x00000002
#define EFI_RIGHT_CONTROL_PRESSED      0x00000004
#define EFI_LEFT_CONTROL_PRESSED       0x00000008
#define EFI_RIGHT_ALT_PRESSED          0x00000010
#define EFI_LEFT_ALT_PRESSED           0x00000020
#define EFI_RIGHT_LOGO_PRESSED         0x00000040
#define EFI_LEFT_LOGO_PRESSED          0x00000080
#define EFI_MENU_KEY_PRESSED           0x00000100
#define EFI_SYS_REQ_PRESSED            0x00000200
#define EFI_TOGGLE_STATE_VALID 0x80
#define EFI_KEY_STATE_EXPOSED 0x40
#define EFI_SCROLL_LOCK_ACTIVE 0x01
#define EFI_NUM_LOCK_ACTIVE 0x02
#define EFI_CAPS_LOCK_ACTIVE 0x04

/* SimpleTextOutputProtocol */
#define BOXDRAW_HORIZONTAL             0x2500
#define BOXDRAW_VERTICAL               0x2502
#define BOXDRAW_DOWN_RIGHT             0x250c
#define BOXDRAW_DOWN_LEFT              0x2510
#define BOXDRAW_UP_RIGHT               0x2514
#define BOXDRAW_UP_LEFT                0x2518
#define BOXDRAW_VERTICAL_RIGHT         0x251c
#define BOXDRAW_VERTICAL_LEFT          0x2524
#define BOXDRAW_DOWN_HORIZONTAL        0x252c
#define BOXDRAW_UP_HORIZONTAL          0x2534
#define BOXDRAW_VERTICAL_HORIZONTAL    0x253c

#define BOXDRAW_DOUBLE_HORIZONTAL      0x2550
#define BOXDRAW_DOUBLE_VERTICAL        0x2551
#define BOXDRAW_DOWN_RIGHT_DOUBLE      0x2552
#define BOXDRAW_DOWN_DOUBLE_RIGHT      0x2553
#define BOXDRAW_DOUBLE_DOWN_RIGHT      0x2554
#define BOXDRAW_DOWN_LEFT_DOUBLE       0x2555
#define BOXDRAW_DOWN_DOUBLE_LEFT       0x2556
#define BOXDRAW_DOUBLE_DOWN_LEFT       0x2557

#define BOXDRAW_UP_RIGHT_DOUBLE        0x2558
#define BOXDRAW_UP_DOUBLE_RIGHT        0x2559
#define BOXDRAW_DOUBLE_UP_RIGHT        0x255a
#define BOXDRAW_UP_LEFT_DOUBLE         0x255b
#define BOXDRAW_UP_DOUBLE_LEFT         0x255c
#define BOXDRAW_DOUBLE_UP_LEFT         0x255d

#define BOXDRAW_VERTICAL_RIGHT_DOUBLE  0x255e
#define BOXDRAW_VERTICAL_DOUBLE_RIGHT  0x255f
#define BOXDRAW_DOUBLE_VERTICAL_RIGHT  0x2560

#define BOXDRAW_VERTICAL_LEFT_DOUBLE   0x2561
#define BOXDRAW_VERTICAL_DOUBLE_LEFT   0x2562
#define BOXDRAW_DOUBLE_VERTICAL_LEFT   0x2563

#define BOXDRAW_DOWN_HORIZONTAL_DOUBLE 0x2564
#define BOXDRAW_DOWN_DOUBLE_HORIZONTAL 0x2565
#define BOXDRAW_DOUBLE_DOWN_HORIZONTAL 0x2566

#define BOXDRAW_UP_HORIZONTAL_DOUBLE   0x2567
#define BOXDRAW_UP_DOUBLE_HORIZONTAL   0x2568
#define BOXDRAW_DOUBLE_UP_HORIZONTAL   0x2569

#define BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE 0x256a
#define BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL 0x256b
#define BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL 0x256c

#define BLOCKELEMENT_FULL_BLOCK        0x2588
#define BLOCKELEMENT_LIGHT_SHADE       0x2591

#define GEOMETRICSHAPE_UP_TRIANGLE     0x25b2
#define GEOMETRICSHAPE_RIGHT_TRIANGLE  0x25ba
#define GEOMETRICSHAPE_DOWN_TRIANGLE   0x25bc
#define GEOMETRICSHAPE_LEFT_TRIANGLE   0x25c4

#define ARROW_UP                       0x2191
#define ARROW_DOWN                     0x2193
/* SimpleTextOutputColor */

/* TEXT_COLOR */
#define EFI_BLACK                              0x00
#define EFI_BLUE                               0x01
#define EFI_GREEN                              0x02
#define EFI_CYAN                               0x03
#define EFI_RED                                0x04
#define EFI_MAGENTA                            0x05
#define EFI_BROWN                              0x06
#define EFI_LIGHTGRAY                          0x07
#define EFI_BRIGHT                             0x08
#define EFI_DARKGRAY(EFI_BLACK \| EFI_BRIGHT)  0x08
#define EFI_LIGHTBLUE                          0x09
#define EFI_LIGHTGREEN                         0x0A
#define EFI_LIGHTCYAN                          0x0B
#define EFI_LIGHTRED                           0x0C
#define EFI_LIGHTMAGENTA                       0x0D
#define EFI_YELLOW                             0x0E
#define EFI_WHITE                              0x0F
/* BACKGROUND_COLOR */
#define EFI_BACKGROUND_BLACK                   0x00
#define EFI_BACKGROUND_BLUE                    0x10
#define EFI_BACKGROUND_GREEN                   0x20
#define EFI_BACKGROUND_CYAN                    0x30
#define EFI_BACKGROUND_RED                     0x40
#define EFI_BACKGROUND_MAGENTA                 0x50
#define EFI_BACKGROUND_BROWN                   0x60
#define EFI_BACKGROUND_LIGHTGRAY               0x70


#endif