#include <iostream>
#include <math.h>

using namespace std;

enum HVACMode {
    Auto = 0,
    Cool = 1,
    Dehumidify = 2,
    Fan = 3,
    Heat = 4
};

enum HVACFanSpeed {
    AutoSpeed = 0,
    Speed1 = 1,
    Speed2 = 2,
    Speed3 = 3
};

struct HVACState {
    HVACMode Mode;
    bool Power;
    HVACFanSpeed FanSpeed;
    bool Swing;
    bool Sleep;
    uint8_t Temperature;
    float Timer;
    bool Humid;
    bool Light;
    bool Ionizer;
    bool Save;
};

struct Frame {
    uint16_t Address;
    uint8_t  Command;
};

void PrintByte(char value)
{
    for(int n = 0; n < 8; n++)
    {
        printf((value & 0x80) == 0 ? "0" : "1");
        value = value << 1;
    }
    printf(" ");
}

void PrintFrame(Frame frame) {
    PrintByte((frame.Address >> 8) & 0xFF);PrintByte(frame.Address & 0xFF);PrintByte(frame.Command);printf("\n");
}

Frame CreateFrame(HVACState state) {
    int h = state.Timer;                // Get whole hours from timer
    int t = ((h / 10) << 4) | (h % 10); // Calculate BCD value for timer

    Frame f;

    f.Address = 0;
    f.Command = 0;

    f.Address |= state.Mode & 0x07;
    f.Address |= state.Power << 3;
    f.Address |= (state.FanSpeed & 0x03) << 4;
    f.Address |= state.Swing << 6;
    f.Address |= state.Sleep << 7;
    f.Address |= ((state.Temperature - 16) & 0xF) << 8;
    f.Address |= (round(state.Timer - h) > 0) << 12;  // Half hour indicator
    f.Address |= (t >> 4) << 13;                      // Tens from BCD value
    f.Address |= (state.Timer > 0) << 15;             // Timer enabled?

    f.Command |= (t & 0X0F);                          // Ones from BCD value
    f.Command |= state.Humid << 4;
    f.Command |= state.Light << 5;
    f.Command |= state.Ionizer << 6;
    f.Command |= state.Sleep << 7;

    return f;
}

HVACState ParseFrame(Frame frame) {
    HVACState s;

    s.Mode = (HVACMode)(frame.Address & 0x07);
    s.Power = (frame.Address >> 3) & 0x01;
    s.FanSpeed = (HVACFanSpeed)((frame.Address >> 4) & 0x03);
    s.Swing = (frame.Address >> 6) & 0x01;
    s.Sleep = (frame.Address >> 7) & 0x01;
    s.Temperature = 16 + (frame.Address >> 8) & 0x0F;
    
    s.Humid = (frame.Command >> 4) & 0x01;
    s.Light = (frame.Command >> 5) & 0x01;
    s.Ionizer = (frame.Command >> 6) & 0x01;
    s.Sleep = (frame.Command >> 7) & 0x01;

    s.Timer = (((frame.Address >> 13) & 0x03) * 10) + (frame.Command & 0x0F)    // Decode BCD
            + (((frame.Address >> 12) & 0x01) > 0 ? .5 : 0);                    // Add half hour?

    return s;
}

int main()
{
    struct HVACState state;

    state.Mode = Cool;
    state.Power = true;
    state.FanSpeed = AutoSpeed;
    state.Swing = true;
    state.Sleep = false;
    state.Temperature = 20;
    state.Timer = 0;
    state.Humid = false;
    state.Light = false;
    state.Ionizer = false;
    state.Save = false;
    
    Frame f = CreateFrame(state);
    printf("A\t");PrintFrame(f);

    HVACState s = ParseFrame(f);
    printf("B\t");PrintFrame(CreateFrame(s));
}