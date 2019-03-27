// Helper functions for music
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include<ctype.h>
#include<math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    /*
    int x = fraction[0] - '0';
    int y = fraction[2] - '0';

    return ((16 / y) * x/2;

    */
//Return everything to 1/8

    if(fraction[0] == '1')
    {
        if(fraction[2] == '8')
        {
            return 1;
        }
        else if(fraction[2] == '4')
        {
            return 2;
        }
        else if(fraction[2] == '2')
        {
            return 4;
        }
        else if(fraction[2] == '1')
        {
            return 8;
        }
    }

    else if(fraction[0] == '3' && fraction[2] == '8')
    {
        return 3;
    }

    else
    {
        return 0;
    }


    return 0;

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // Parse the String into its Note and Octave
    int octave = note[strlen(note) - 1];
    octave -= 48; // Adjust Ascii to int value

    // Determine Frequency of note in the given octive
    double freq = 0.0;

    // Determine note letter
    switch(note[0])
    {
        case 'C' :
            freq = 440.0 / (pow(2.0, (9.0 / 12.0)));
            break;
        case 'D' :
            freq = 440.0 / (pow(2.0, (7.0 / 12.0)));
            break;
        case 'E' :
            freq = 440.0 / (pow(2.0, (5.0 / 12.0)));
            break;
        case 'F' :
            freq = 440.0 / (pow(2.0, (4.0 / 12.0)));
            break;
        case 'G' :
            freq = 440.0 / (pow(2.0, (2.0 / 12.0)));
            break;
        case 'A' :
            freq = 440.0;
            break;
        case 'B' :
            freq = 440.0 * (pow(2.0, (2.0 / 12.0)));
            break;
        default :
            return 0;
    }

    // Loop to shift octave
    if(octave > 4)
    {
        for(int i = 0; i < octave - 4; i++)
        {
            freq *= 2.0;
        }
    }
    else if(octave < 4)
    {
        for(int i = 0; i < 4 - octave; i++)
        {
            freq /= 2.0;
        }
    }

    // Final adjustment or flat or sharp
    if(note[1] == 'b')
    {
        freq /= (pow(2.0, (1.0 / 12.0)));
    }
    else if(note[1] == '#')
    {
        freq *= (pow(2.0, (1.0 / 12.0)));
    }


    // Return frequency value as an int
    int whole = round(freq);

    return whole;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == '0')
    {
        return true;
    }
    return false;
}
