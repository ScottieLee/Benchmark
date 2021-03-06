#include <QtCore/QCoreApplication>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "queue_watcher_thread.h"
#include "top_block_simulation.h"
#include <gr_realtime.h>
#include <time.h>

#include "string_functions.h"
#include <time.h>
#include <sys/time.h>
#include <signal.h>

#include "reception_statistics.h"

#include "scrambler.h"
// SW_CLOCK_TICK IS 10us

struct timeval start_time;

unsigned int convert_time_to_time_stamp(timeval start_time, timeval time_in);

void microsleep(long us)
{
    struct timespec wait;
    wait.tv_sec = us / (1000 * 1000);
    wait.tv_nsec = (us % (1000 * 1000)) * 1000;
    nanosleep(&wait, NULL);
}


void callback1(bool ok, std::string mpdu, timeval lt_timeval)
{
    std::cout << "Ok = " << ok << "\t" << string_to_hex(mpdu) << std::endl;
}

int main(int argc, char *argv[])
{

    top_block_simulation_sptr tb = make_top_block_simulation_sptr();
    gr_rt_status_t r = gr_enable_realtime_scheduling(); //FIXME
    //----------------------Start USRP----------------------//
    tb->start();
    char a = 0x00;
    while (1) {

        char tmp[1] = {a};
        a++;
        std::string payload = std::string(tmp, sizeof(char));
        payload = repeat(payload, 10);
        tb->send_pkt(payload, 0);
    }
 //   QCoreApplication a(argc, argv);
 //   return a.exec();
}
