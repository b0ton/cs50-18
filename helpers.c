// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "helpers.h"


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int res = atoi(&fraction[0]) * (8 / atoi(&fraction[strlen(fraction) - 1]));
    return res;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    double A4 = 440;
    int final = 0;
    double hz = 0;
    int len = 0;
    len = strlen(note);

    switch(note[0])
    {
    case 'C' :
        hz = A4 / pow( 2.0, 9.0 / 12.0 );
        break;
    case 'D' :
        hz = A4 / pow( 2.0, 7.0 / 12.0 );
        break;
    case 'E' :
        hz = A4 / pow( 2.0, 5.0 / 12.0 );
        break;
    case 'F' :
        hz = A4 / pow( 2.0, 4.0 / 12.0 );
        break;
    case 'G' :
        hz = A4 / pow( 2.0, 2.0 / 12.0 );
        break;
    case 'A' :
        hz = A4;
        break;
    case 'B' :
        hz = A4 * pow( 2.0, 2.0 / 12.0 );
        break;
    default :
        return 0;
    }

    if (note[1] == 'b')
    {
        hz /= pow( 2.0, 1.0 / 12.0 );
    }
    else if (note[1] == '#')
    {
        hz *= pow( 2.0, 1.0 / 12.0 );
    }

    hz *= pow( 2.0, atoi(&note[len - 1]) - 4);
    final = round (hz);
    return final;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp( s, "") == 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

