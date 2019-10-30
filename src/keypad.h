byte key = 0;

byte getKey()
{
    int val = 0;
    byte button = 0;
    val = analogRead(KEYPAD_PIN);
    //Serial.println(val);

    button = NONE; // use NONE as the default value
    if (val <= 45)
    {
        button = LEFT;
    } // left
    else if ((val >= 60) && (val <= 70))
    {
        button = DOWN;
    } // up
    else if ((val >= 85) && (val <= 95))
    {
        button = UP;
    } // down
    else if ((val >= 105) && (val <= 115))
    {
        button = RIGHT;
    } // right
    else if ((val >= 130) && (val <= 140))
    {
        button = ESC;
    } // select
    else if ((val >= 150) && (val <= 160))
    {
        button = ENTER;
    } // select
    return button;
}

// String checkKeypad()
// {
//     key = getKey();
//     if (key == LEFT)
//     {
//         Serial.println("LEFT");
//         return "LEFT";
//     }
//     if (key == RIGHT)
//     {
//         Serial.println("RIGHT");
//         return "RIGHT";
//     }
//     if (key == UP)
//     {
//         Serial.println("UP");
//         return "UP";
//     }
//     if (key == DOWN)
//     {
//         Serial.println("DOWN");
//         return "DOWN";
//     }
//     if (key == ESC)
//     {
//         Serial.println("ESC");
//         return "ESC";
//     }
//     if (key == ENTER)
//     {
//         Serial.println("ENTER");
//         return "ENTER";
//     }
//     if (key == NONE)
//     {
//         return "NONE";
//     }

// }