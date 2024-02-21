#include "ethercat_to_can/ecat_can_base/ecat_base.hpp"
#include "ethercat_to_can/ecat_can_base/ecat_typedef.hpp"
#include "ethercat_to_can/ecat_motor_dlc/ecat_DM4310.hpp"
#include "ethercat_to_can/ecat_motor_dlc/ecat_GM6020.hpp"

#include <array>
#include <signal.h>
#include <unistd.h>

bool app_stopped = false;

void sigint_handler(int sig);
void safe_stop();

ecat::EcatBase Ethercat(2);

std::array<ecat::GM6020dlc, 2> Motor6020 = {
    ecat::GM6020dlc(CAN2, 2),
    ecat::GM6020dlc(CAN1, 7)};

int main()
{
    signal(SIGINT, sigint_handler);

    char phy[] = "enp5s0";
    Ethercat.EcatStart(phy);

    printf("start\n");

    float kp = 5;
    float kd = 10;
    float I_1 = 0;

    for (int i = 0; i < 10000000; i++)
    {

        Motor6020[0].GM6020_can_set(&Ethercat.packet_tx[0], I_1);
        Motor6020[1].GM6020_can_set(&Ethercat.packet_tx[0], 0);
        Ethercat.EcatSyncMsg();
        Motor6020[0].GM6020_can_analyze(&Ethercat.packet_rx[0]);
        Motor6020[1].GM6020_can_analyze(&Ethercat.packet_rx[0]);

        I_1 = (Motor6020[0].pos - Motor6020[1].pos) * kp - (Motor6020[0].pos - Motor6020[1].pos) * kd;

        printf("%f\n", I_1);
        printf("%d\n", Motor6020[0].pos);

        printf("--------------------------------\n");

        if (app_stopped)
        {
            break;
        }
    }

    safe_stop();
    Ethercat.EcatStop();

    printf("stop");

    return 0;
}

void sigint_handler(int sig)
{
    if (sig == SIGINT)
    {
        app_stopped = true;
    }
}

void safe_stop()
{
    Motor6020[0].GM6020_can_set(&Ethercat.packet_tx[0], 0);
    Motor6020[1].GM6020_can_set(&Ethercat.packet_tx[0], 0);
    // Repeat 3 times to prevent packet loss
    Ethercat.EcatSyncMsg();
    Ethercat.EcatSyncMsg();
    Ethercat.EcatSyncMsg();
    printf("stop motor!");
}