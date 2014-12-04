// by Les Hall
// FM3D - Frequency Modulation 3D Printer Controller
// started Tue Nov 18 2014
// 


PulseOsc osc => Gain sum => dac;
1000 => osc.freq;


while(true)
{
    <<< "moving left" >>>;
    0.40 => osc.width;
    1.0 => osc.gain;
    100::ms => now;
    0.0 => osc.gain;
    9.9::second => now;
    
    <<< "moving right" >>>;
    0.60 => osc.width;
    1.0 => osc.gain;
    100::ms => now;
    0.0 => osc.gain;
    9.9::second => now;
}