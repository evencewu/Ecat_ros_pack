#ifndef __ECAT_TYPEDEF__
#define __ECAT_TYPEDEF__

#include <inttypes.h>

#define CAN1 0
#define CAN2 1

#define USE_SSC
//#define USE_SOES

namespace ecat
{
    /// @brief Standard can packet
    typedef struct can_pack
    {
        uint16_t StdId;
        uint8_t ExtId;
        // uint32_t ExtId;
        uint8_t IDE;
        uint8_t RTR;
        uint8_t DLC;

        uint8_t Data[8];
    } __attribute__((packed)) can_pack;

//#if defined(USE_SOES)
//
//    /// @brief ecat pdo send data (master to slv)
//    typedef struct Ecat_Outputs_Pack
//    {
//        can_pack can[2];
//
//        bool LED[8];
//    } __attribute__((packed)) Ecat_Outputs_Pack;
//
//    /// @brief ecat pdo recive data (slv to master)
//    typedef struct Ecat_Inputs_Pack
//    {
//        can_pack can[2];
//    } __attribute__((packed)) Ecat_Inputs_Pack;
//    
//#elif defined(USE_SSC)
    /// @brief ecat pdo send data (master to slv)
    typedef struct Ecat_Outputs_Pack
    {
        uint8_t LED;
        struct can_pack can[2];
        uint8_t null;
    } __attribute__((packed)) Ecat_Outputs_Pack;

    /// @brief ecat pdo recive data (slv to master)
    typedef struct Ecat_Inputs_Pack
    {
        uint8_t switch_io;
        uint8_t null[5];

        struct can_pack can[2];
    } __attribute__((packed)) Ecat_Inputs_Pack;
//#endif

}
#endif