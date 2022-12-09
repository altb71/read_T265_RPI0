/* mbed Microcontroller Library
THis is a small demo/sample to read intel realsense data from RPI0
R. Altenburger Dez 2022
 */
#include "mbed.h"
#include "data_structs.h"
#include "RST265_thread.h"
BufferedSerial rpi0_Uart(PC_6,PC_7,115200);

int main()
{
    ThisThread::sleep_for(chrono::milliseconds(100));
    //------------samping rates
    float Ts25 = .04;
    rpi0_Uart.set_format(8,BufferedSerial::None,1);
    rpi0_Uart.set_blocking(false);
    //----------------------------------
    DATA_Xchange *data = new DATA_Xchange;
    printf("Start Program\r\n");
    RST265_thread t265(&rpi0_Uart,data,Ts25);
    ThisThread::sleep_for(chrono::milliseconds(200));
    t265.start_RST265();
    while(true) {
        ThisThread::sleep_for(500ms);
        printf("xyz: %f %f %f\r\n",data->sens_RS(0),data->sens_RS(1),data->sens_RS(2));
    }
}
